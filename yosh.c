#include "yosh.h"
#include <stddef.h>
#include "builtin/help.h"
#include "builtin/about.h"
#include "builtin/exit.h"

yosh_app_t* yosh_builtin_apps[] = { &yosh_builtin_help,
                                    &yosh_builtin_about,
                                    &yosh_builtin_exit   };

/** \brief this type is used for argument passing into command functions */
typedef struct
{ yosh_list_t list;
  char*       arg;
} yosh_arg_list_t;

/** \brief this type is a part of string container */
typedef struct //yosh_string_t
{ char*  s;    ///< pointer to the string
  size_t len;  ///< length of the string
  char*  iter; ///< iterator which represent next symbol for reading
} yosh_string_t;

/** \brief this type is used by parser */
typedef struct //yosh_data_t
{ yosh_string_t*     input;        ///< string of a user input
  char*              cur_char;     /* TODO: write description */
  char*              greet_string; /**< string which will be  printed at start
                                        of new line */
  int                esc_flag;     ///< escape-symbol flag (backslash)
  int                exit_req;     /**< request for exit from shell
                                        TODO: this is deprecated field. Now
                                              shell use state machine for
                                              control itself */
  yosh_env_t         env;          /**< environment for commands and partionally
                                        for parser */
} yosh_data_t;

/** \brief   prints raw string in output buffer 
 *  \details as replacement to printf but without dependencies of any type
 *  \arg     e environment
 *  \arg     s string to pront */
void yosh_puts(yosh_env_t* e, const char* s)
{ while (*s != 0) { e->calls.putchar(*s); s++; } }

/** \brief   initialize linked list root node structure
 *  \arg     list       pointer to a root node of list
 *  \arg     payload_id identifier of payloaded data type
 *                      \note this field is not necessary for linkde list
 *                            mechanisms theirselves but useful for a user
 *                            TODO: maybe deprecate?
 *  \return  pointer to a root node of list */
void* yosh_list_init(void* list, unsigned int payload_id)
{ yosh_list_t* l = (yosh_list_t*)list;

  l->next = NULL; l->prev = NULL; l->payload_id = payload_id;

  return l; }

void* yosh_list_detach(void* list)
{ yosh_list_t* l = (yosh_list_t*)list;
  
  if (l->prev) { l->prev->next = l->next; }
  if (l->next) { l->next->prev = l->prev; }

  return l; }

void* yosh_list_first(void* list)
{ yosh_list_t* l = (yosh_list_t*)list;

  while (l->prev != NULL) { l = l->prev; }

  return l; }

void* yosh_list_last(void* list)
{ yosh_list_t* l = (yosh_list_t*)list;

  while (l->next != NULL) { l = l->next; }

  return l; }

void* yosh_list_insert_before(void* list, void* item)
{ yosh_list_t* prev = ((yosh_list_t*)list)->prev;
  yosh_list_t* next = (yosh_list_t*)list;
  yosh_list_t* i    = (yosh_list_t*)item;

  i->prev = prev; i->next = next;
  if (prev) { prev->next = i; }
  if (next) { next->prev = i; }

  return i; }

void* yosh_list_insert_after(void* list, void* item)
{ yosh_list_t* prev = (yosh_list_t*)list;
  yosh_list_t* next = ((yosh_list_t*)list)->next;
  yosh_list_t* i    = (yosh_list_t*)item;

  i->prev = prev; i->next = next;
  if (prev) { prev->next = i; }
  if (next) { next->prev = i; }

  return i; }

void* yosh_list_append(void* list, void* item)
{ return yosh_list_insert_after(yosh_list_last(list), item); }

void* yosh_list_prepend(void* list, void* item)
{ return yosh_list_insert_before(yosh_list_first(list), item); } 

void yosh_memcpy_dumb(void* dst, void* src, size_t n)
{ char* d = dst; char* s = src; while (n > 0) { d[n - 1] = s[n - 1]; n--; } }
void yosh_memset_dumb(void* dst, char val, size_t n)
{ char* d = (char*)dst; for (int i = 0; i < n; i++) { *d++ = val; } }

int yosh_strcmp_dumb(const char* str1, const char* str2)
{ if (str1 == NULL) { return -1; }
  if (str2 == NULL) { return -1; }

  while(*str1 != 0 && *str2 != 0)
  { if (*str1 != *str2) { return 0; } str1++; str2++; }
  if (*str1 != *str2) { return 0; } //if one string is shorter another

  return 1; }

yosh_string_t* yosh_new_string(yosh_data_t* d, size_t n)
{ yosh_string_t* ret = d->env.calls.malloc(sizeof(yosh_string_t));
  ret->s = d->env.calls.malloc(n);
  yosh_memset_dumb(ret->s, 0, n);
  ret->len = n; ret->iter = ret->s;
  return ret; }

void yosh_del_string(yosh_data_t* d, yosh_string_t* s)
{ d->env.calls.free(s->s); d->env.calls.free(s); }

yosh_string_t* yosh_ext_string(yosh_data_t* d, yosh_string_t* s, size_t n)
{ if (n == 0) { n = YOSH_STANDARD_STRING_EXT_VAL; }
  yosh_string_t* ret = yosh_new_string(d, s->len + n);
  yosh_memcpy_dumb(ret->s, s->s, s->len);
  ret->len = s->len + n;
  ret->iter = ret->s + (s->iter - s->s);
  yosh_del_string(d, s);
  return ret; }

void yosh_string_add_char(yosh_data_t* d, yosh_string_t** s, char ch)
{ *(*s)->iter = ch; (*s)->iter++;

  if ((*s)->iter >= (*s)->s + (*s)->len) 
  { *s = yosh_ext_string(d, *s, 0); } }

void yosh_del_input(yosh_data_t* desc)
{ if (!desc) { return; }
  if (desc->input == NULL) { return; }

  yosh_del_string(desc, desc->input);

  desc->input = NULL; }

void yosh_new_input(yosh_data_t* desc)
{ if (!desc) { return; }

  desc->input = yosh_new_string(desc, YOSH_STANDARD_INPUT_LEN); }

void yosh_ext_input(yosh_data_t* desc)
{ if (!desc) { return; }
  if (desc->input == NULL) { return; }

  desc->input = yosh_ext_string(desc, desc->input, YOSH_STANDARD_INPUT_LEN); }

int yosh_quit_flag = 0;

void yosh_greet(yosh_data_t* desc);

void* yosh_start(const yosh_init_struct_t* init_struct)
{ if (!init_struct)                { return NULL; }
  if (!init_struct->calls.putchar) { return NULL; }
  if (!init_struct->calls.getchar) { return NULL; }
  if (!init_struct->calls.malloc)  { return NULL; }
  if (!init_struct->calls.free)    { return NULL; }

  yosh_data_t* shell_desc = 
    (yosh_data_t*)init_struct->calls.malloc(sizeof(yosh_data_t));
  if (!shell_desc) { return NULL; }
  shell_desc->env.calls            = init_struct->calls;
  shell_desc->greet_string         = init_struct->greet_string;
  shell_desc->env.user_apps        = (yosh_list_t*)init_struct->user_apps;
  shell_desc->env.builtin_apps     = yosh_builtin_apps;
  shell_desc->env.builtin_apps_len = sizeof(yosh_builtin_apps) /
                                     sizeof(yosh_builtin_apps[0]);
  
  yosh_new_input(shell_desc);

  yosh_greet(shell_desc);

  return (void*)shell_desc; }

int yosh_try_run(yosh_data_t* d, yosh_arg_t* args)
{ for (unsigned int i = 0; i < d->env.builtin_apps_len; i++)
  { if (yosh_strcmp_dumb(args->str, d->env.builtin_apps[i]->name))
    { ((yosh_func_t)d->env.builtin_apps[i]->ptr)(&d->env, args);
      return 1; } }
  
  yosh_app_list_t* usr = (yosh_app_list_t*)d->env.user_apps;
  while (usr != NULL)
  { if (yosh_strcmp_dumb(args->str, usr->app->name)) 
    { ((yosh_func_t)usr->app->ptr)(&d->env, args); return 1; } 
    usr = (yosh_app_list_t*)usr->l.next; }

  return 0; }

int yosh_parser(yosh_data_t* desc)
{ if (!desc) { return -1; }
  
  yosh_arg_t* arg_list = NULL;
  
  char* cur = desc->input->s;
  int arg_flag = 0;
  while (*cur != 0)
  { if (*cur == ' ') 
    { while (*cur == ' ') { *cur = 0; cur++; } arg_flag = 0; continue; }

    if (arg_flag == 0) 
    { arg_flag = 1;

      if (arg_list == NULL) 
      { arg_list = desc->env.calls.malloc(sizeof(yosh_arg_t));
        yosh_list_init(arg_list, 0); }
      else 
      { yosh_arg_t* tmp_arg = desc->env.calls.malloc(sizeof(yosh_arg_t));
        yosh_list_init(tmp_arg, 0);
        arg_list = yosh_list_append(arg_list, tmp_arg); }

      arg_list->str = cur; }

    cur++; }

  if (arg_list != NULL)
  { arg_list = yosh_list_first(arg_list);
    
    if (yosh_try_run(desc, arg_list) == 0)
    { yosh_puts(&desc->env, "unknown command: ");
      yosh_puts(&desc->env, arg_list->str);
      desc->env.calls.putchar('\n'); }

    while (arg_list->l.next != NULL) 
    { arg_list = (yosh_arg_t*)arg_list->l.next;
      desc->env.calls.free(arg_list->l.prev); }
    desc->env.calls.free(arg_list);
  }
  return 0; }

int yosh_input(char ch, void* shell_desc)
{ if (!shell_desc) { return -1; }
  yosh_data_t* d = (yosh_data_t*)shell_desc;

  if (d->esc_flag) { d->esc_flag = 0; return 0; }
  else if (ch == '\\') { d->esc_flag = 1; return 0; }

  switch(ch)
  { case '\n':
    case '\r':  
    { if (yosh_parser(d) == -1) { d->env.calls.free(d); return -1; }

      yosh_del_input(d); 
      if (d->env.state == YOSH_STATE__HALT) { d->env.calls.free(d);
                                              return 1; }
      yosh_new_input(d);
      
      yosh_greet((yosh_data_t*)shell_desc);
    } break;
    default: yosh_string_add_char(d, &d->input, ch); break; }

  return 0; }

void yosh_greet(yosh_data_t* desc) 
{ if (!desc) { return; }

  if (desc->greet_string) { yosh_puts(&desc->env, desc->greet_string); }

  desc->env.calls.putchar('>'); }

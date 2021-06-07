#include "yosh.h"
#include "yosh_app_api.h"
#include <stddef.h>
#include "containers/lists.h"
#include "containers/strings.h"
#include "builtin/help.h"
#include "builtin/about.h"
#include "builtin/exit.h"

yosh_app_t* yosh_builtin_apps[] = { &yosh_builtin_help,
                                    &yosh_builtin_about,
                                    &yosh_builtin_exit   };

/** \brief this type is used for argument passing into command functions */
typedef struct
{ cont_list_t list;
  char*       arg;
} yosh_arg_list_t;

/** \brief this type is used by parser */
typedef struct //yosh_data_t
{ cont_string_t*     input;        ///< string of a user input
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

/** \brief   deletes data of user input
 *  \details actually it's just adapter for a string container part
 *  \arg     desc shell descriptor */
void yosh_del_input(yosh_data_t* desc)
{ if (!desc) { return; }
  if (desc->input == NULL) { return; }

  cont_del_string(&desc->env.strcalls, desc->input);

  desc->input = NULL; }

/** \brief   creates buffer for user input data
 *  \details actually it's just adapter for a string container part
 *  \arg     desc shell descriptor */
void yosh_new_input(yosh_data_t* desc)
{ if (!desc) { return; }

  desc->input = cont_new_string(&desc->env.strcalls, YOSH_STANDARD_INPUT_LEN); }

/** \brief   manually extends buffer for user input data
 *  \details actually it's just adapter for a string container part
 *  \arg     desc shell descriptor */
void yosh_ext_input(yosh_data_t* desc)
{ if (!desc) { return; }
  if (desc->input == NULL) { return; }

  desc->input = cont_ext_string(&desc->env.strcalls, desc->input, 
                                YOSH_STANDARD_INPUT_LEN); }

int yosh_quit_flag = 0;

/** \brief   prints greet string before user be able to input
 *  \details will be deprecated soon
 *  \arg     desc descriptor of the shell */
void yosh_greet(yosh_data_t* desc);

void* yosh_start(const yosh_init_struct_t* init_struct)
{ if (!init_struct)                { return NULL; }
  if (!init_struct->calls.putchar) { return NULL; }
  if (!init_struct->calls.getchar) { return NULL; }
  if (!init_struct->calls.malloc)  { return NULL; }
  if (!init_struct->calls.free)    { return NULL; }
  if (!init_struct->calls.memcpy)  { return NULL; }
  if (!init_struct->calls.memset)  { return NULL; }
  if (!init_struct->calls.strcmp)  { return NULL; }

  yosh_data_t* shell_desc = 
    (yosh_data_t*)init_struct->calls.malloc(sizeof(yosh_data_t));
  if (!shell_desc) { return NULL; }

  shell_desc->env.calls            = init_struct->calls;
  shell_desc->greet_string         = init_struct->greet_string;
  shell_desc->env.user_apps        = (cont_list_t*)init_struct->user_apps;
  shell_desc->env.builtin_apps     = yosh_builtin_apps;
  shell_desc->env.builtin_apps_len = sizeof(yosh_builtin_apps) /
                                     sizeof(yosh_app_t*);

  shell_desc->env.strcalls.free   = init_struct->calls.free;
  shell_desc->env.strcalls.malloc = init_struct->calls.malloc;
  shell_desc->env.strcalls.memcpy = init_struct->calls.memcpy;
  shell_desc->env.strcalls.memset = init_struct->calls.memset;
  shell_desc->env.strcalls.strcmp = init_struct->calls.strcmp;
  
  yosh_new_input(shell_desc);

  yosh_greet(shell_desc);

  return (void*)shell_desc; }

/** \brief   runs user and builtin functions
 *  \details search for function name in builtin and user functions lists. first
 *           argument is a function name as in *nix shells so it is data for
 *           search.
 *           \note this code soon be obsoleted because planned displaying result
 *                 to user
 *  \arg     d    shell descriptor
 *  \arg     args argumen for call
 *  \return  result of run
 *  \retval  0 nothing to run
 *  \retval  1 function runs normally */
int yosh_try_run(yosh_data_t* d, yosh_arg_t* args)
{ for (unsigned int i = 0; i < d->env.builtin_apps_len; i++)
  { if (d->env.calls.strcmp(args->str, d->env.builtin_apps[i]->name))
    { ((yosh_func_t)d->env.builtin_apps[i]->ptr)(&d->env, args);
      return 1; } }
  
  yosh_app_list_t* usr = (yosh_app_list_t*)d->env.user_apps;
  while (usr != NULL)
  { if (d->env.calls.strcmp(args->str, usr->app->name)) 
    { ((yosh_func_t)usr->app->ptr)(&d->env, args); return 1; } 
    usr = (yosh_app_list_t*)usr->l.next; }

  return 0; }

/** \brief   user input parser
 *  \details one pass parser. it changes any non-literal symbols of input string
 *           to zeros, also it creates linked list of pointers to first literal
 *           of any word which after will be passed to user functions as
 *           argument. literal means any symbol exclude whitespace for all
 *           input string width. after that it runs builtin and user functions
 *           and clean-up used memory
 *           \note TODO: it contains manual operations on containers. replace
 *                       if possible
 *  \arg     desc shell desccriptor
 *  \return  error sequence
 *  \retval  0  all ok
 *  \retval  -1 error occure while parsing */
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
        cont_list_init(arg_list, 0); }
      else 
      { yosh_arg_t* tmp_arg = desc->env.calls.malloc(sizeof(yosh_arg_t));
        cont_list_init(tmp_arg, 0);
        arg_list = cont_list_append(arg_list, tmp_arg); }

      arg_list->str = cur; }

    cur++; }

  if (arg_list != NULL)
  { arg_list = cont_list_first(arg_list);
    
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
    default: cont_string_add_char(&d->env.strcalls, &d->input, ch); break; }

  return 0; }

void yosh_greet(yosh_data_t* desc) 
{ if (!desc) { return; }

  if (desc->greet_string) { yosh_puts(&desc->env, desc->greet_string); }

  desc->env.calls.putchar('>'); }

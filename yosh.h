#ifndef YOSH_H
#define YOSH_H

#include <stddef.h>

#define YOSH_STANDARD_INPUT_LEN      40
#define YOSH_STANDARD_ARG_LEN        10
#define YOSH_STANDARD_STRING_EXT_VAL 10

typedef enum //yosh_list_id_t
{ YOSH_LIST_ID__ARG     = 0,
  YOSH_LIST_ID__APP     = 1,
  YOSH_LIST_ID__ENV_VAR = 2
} yosh_list_id_t;

typedef struct yosh_list
{ struct yosh_list* next;
  struct yosh_list* prev;
  unsigned int      payload_id;
} yosh_list_t;

void* yosh_list_init(void* list, unsigned int payload_id);
void* yosh_list_detach(void* list);
void* yosh_list_first(void* list);
void* yosh_list_last(void* list);
void* yosh_list_insert_before(void* list, void* item);
void* yosh_list_insert_after(void* list, void* item);
void* yosh_list_append(void* list, void* item);
void* yosh_list_prepend(void* list, void* item);

typedef struct //yosh_arg_t
{ yosh_list_t l;
  char*       str;
} yosh_arg_t;

typedef struct //yosh_var_t
{ yosh_list_t l;
  char* name;
  char* value;
} yosh_var_t;

typedef struct //yosh_calls_t
{ int              (*putchar)(int ch);
  int              (*getchar)(void);
  void*            (*malloc)(size_t size);
  void             (*free)(void* ptr); 
} yosh_calls_t;

typedef struct //yosh_app_t
{ const char* name;
  void (*ptr)(void);
  const char* help; //may be NULL
} yosh_app_t;

typedef enum //yosh_state_t
{ YOSH_STATE__WAITING_LOGIN = 0,
  YOSH_STATE__RUNNING       = 1,
  YOSH_STATE__HALT          = 3
} yosh_state_t;

typedef struct //yosh_env_t
{ yosh_calls_t calls;
  yosh_list_t* user_apps;
  yosh_app_t** builtin_apps;
  unsigned int builtin_apps_len;
  yosh_var_t*  vars;
  yosh_state_t state;
} yosh_env_t;

typedef int (*yosh_func_t)(yosh_env_t* env, yosh_arg_t* args);

typedef struct //yosh_app_list_t
{ yosh_list_t l;
  yosh_app_t* app;
} yosh_app_list_t;

typedef struct //yosh_init_struct_t
{ yosh_calls_t     calls;
  yosh_app_list_t* user_apps;
  char*            greet_string;
} yosh_init_struct_t;

void yosh_puts(yosh_env_t* e, const char* s);
int yosh_strcmp_dumb(const char* str1, const char* str2);
void* yosh_start(const yosh_init_struct_t* init_struct);
int yosh_input(char ch, void* shell_desc);

#endif//YOSH_H

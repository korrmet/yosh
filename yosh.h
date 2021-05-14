#ifndef YOSH_H
#define YOSH_H

#include <stddef.h>
#include "containers/lists.h"

#define YOSH_STANDARD_INPUT_LEN      40 /**< length of standard input in chars
                                             \note automatically extended, not
                                                   maximum value */
#define YOSH_STANDARD_ARG_LEN        10 /**< TODO: what is it and why? */
#define YOSH_STANDARD_STRING_EXT_VAL 10 /**< length in symbols of string extend
                                             increment */

/** \brief identifiers of linked list payload 
 *         \note TODO: check for unused */
typedef enum //cont_list_id_t
{ cont_list_ID__ARG     = 0,
  cont_list_ID__APP     = 1,
  cont_list_ID__ENV_VAR = 2
} cont_list_id_t;


/** \brief   type of argument
 *  \details set of strings inside linked list container */
typedef struct //yosh_arg_t
{ cont_list_t l;
  char*       str;
} yosh_arg_t;

/** \brief   shell environment variable
 *  \details pair of strings name-value packed in linked list container */
typedef struct //yosh_var_t
{ cont_list_t l;
  char* name;
  char* value;
} yosh_var_t;

/** \brief   syscalls which shell use in it's work */
typedef struct //yosh_calls_t
{ int              (*putchar)(int ch);     /**< send one char to io device  */
  int              (*getchar)(void);       /**< get one char from io device */
  void*            (*malloc)(size_t size); /**< allocate memory */
  void             (*free)(void* ptr);     /**< free allocated memory */
} yosh_calls_t;

/** \brief   application descriptor */
typedef struct //yosh_app_t
{ const char* name;  /**< name of your app
                          \note used for calls from shell */
  void (*ptr)(void); /**< pointer to a handler of your app */
  const char* help;  /**< help of your app. 
                          \note shell command "help" prints this string
                          \note may be NULL */
} yosh_app_t;

/** \brief possible states of shell */
typedef enum //yosh_state_t
{ YOSH_STATE__WAITING_LOGIN = 0,
  YOSH_STATE__RUNNING       = 1,
  YOSH_STATE__HALT          = 3
} yosh_state_t;

/** \brief   shell environment descriptor
 *  \details you can run multiple shells in your system. all you need is create
 *           multiple descriptors 
 *           \note every shell application take this descriptor */
typedef struct //yosh_env_t
{ yosh_calls_t calls;            /**< syscalls */
  cont_list_t* user_apps;        /**< list of your apps. 
                                      \note add it using container api */
  yosh_app_t** builtin_apps;     /**< list of built-in apps. 
                                      \note don't modify it */
  unsigned int builtin_apps_len; /**< length of list of builtin apps
                                      \note don't modify it */
  yosh_var_t*  vars;             /**< shell vars
                                      \note add it using container api */
  yosh_state_t state;            /**< state of shell */
} yosh_env_t;

typedef int (*yosh_func_t)(yosh_env_t* env, yosh_arg_t* args);

typedef struct //yosh_app_list_t
{ cont_list_t l;
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

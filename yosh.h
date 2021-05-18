#ifndef YOSH_H
#define YOSH_H

#include <stddef.h>
#include "containers/lists.h"
#include "containers/strings.h"

#define YOSH_STANDARD_INPUT_LEN      40 /**< length of standard input in chars
                                             \note automatically extended, not
                                                   maximum value */
#define YOSH_STANDARD_ARG_LEN        10 /**< TODO: what is it and why? */

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
{ cont_list_t l;   /**< linked list container part */
  char*       str; /**< word of input string without separating symbol (space) */
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
{ yosh_calls_t        calls;            /**< syscalls for shell */
  cont_list_t*        user_apps;        /**< list of your apps. 
                                             \note add it using container api */
  yosh_var_t*         vars;             /**< shell vars
                                             \note add it using container api */
  yosh_app_t**        builtin_apps;     /**< list of built-in apps. 
                                             \note don't modify it */
  unsigned int        builtin_apps_len; /**< length of list of builtin apps
                                             \note don't modify it */
  yosh_state_t        state;            /**< state of shell 
                                             \note don't modify it */
  cont_string_calls_t strcalls;         /**< syscalls for strings
                                             \note don't modify it */
} yosh_env_t;

/** \brief   describes the type of shell function
 *  \details user functions and builtin are similar by their interface 
 *  \arg     env  environment of the shell, e.g. io interface, shell variables,
 *                etc...
 *  \arg     args list of arguments passed. first argument is name of function,
 *                others - all ords after it separated space. packed in list
 *                container.
 *                \note use container api to access it */
typedef int (*yosh_func_t)(yosh_env_t* env, yosh_arg_t* args);

/** \brief   list of apps that user want to run
 *  \details may be changed in runtime */
typedef struct //yosh_app_list_t
{ cont_list_t l;   /**< list container part
  yosh_app_t* app; /**< application pointer */
} yosh_app_list_t;

/** \brief   initializing data set
 *  \details needs for hide fields which user shouldn't fill */
typedef struct //yosh_init_struct_t
{ yosh_calls_t     calls;        /**< system calls for shell */
  yosh_app_list_t* user_apps;    /**< list of user applications */
  char*            greet_string; /**< this string will be printed before
                                      input is reached
                                      \note deprecated field */
} yosh_init_struct_t;

void yosh_puts(yosh_env_t* e, const char* s);
void* yosh_start(const yosh_init_struct_t* init_struct);
int yosh_input(char ch, void* shell_desc);

#endif//YOSH_H

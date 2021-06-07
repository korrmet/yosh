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
{ /** \brief   allocate memory
   *  \details signature is similar to standard malloc
   *  \arg     size size of memory you going to allocate
   *  \return  pointer to allocated memory or error sequence
   *  \retval  NULL  error
   *  \retval  !NULL valid pointer */
  void* (*malloc)(size_t size);

  /** \brief   free memory
   *  \details signature is similar to standard free
   *  \arg     ptr pointer to memory you going to free */
  void  (*free)(void* ptr);

  /** \brief   send one char to io device
   *  \details signature is similar to standard putchar
   *  \arg     ch char to be sended from shell to io device (e.g. uart) or
   *              data exchange protocol
   *  \return  result of sending
   *  \retval  0 ok
   *  \retval  <0 error occured */
  int              (*putchar)(int ch);

  /** \brief   get one char from io device. this function shall block thread
   *           while char is getting.
   *  \details signature is similar to standard getchar
   *           \noote TODO: check it
   *  \return  character or error sequence
   *           \note TODO: inspect maybe retval <0 should be deprecated or
   *                       this function must be non-blocking
   *  \retval  0-255 valid ascii character
   *  \retval  <0 error occured */
  int              (*getchar)(void);       /**< get one char from io device */

  /** \brief   copy memory
   *  \details signature is similar to standard memcpy
   *  \arg     dst pointer to destination memory area
   *  \arg     src pointer to source memory area
   *  \arg     n   size in bytes of memory which will be copied 
   *  \return  pointer to copied data or error sequence
   *           \note check it in original memcpy 
   *  \retval  NULL  error
   *  \retval  !NULL valid pointer to copied data */
  void* (*memcpy)(void* dst, const void* src, size_t n);

  /** \brief   fill memory by specific character
   *  \details signature is similar to standard memset
   *  \arg     dst pointer to destination memory area
   *  \arg     val character to fill memosy
   *  \arg     n   size in bytes of memory shich you going to fill 
   *  \return  pointer to setted data or error sequence
   *           \note check it in original memset
   *  \retval  NULL  error
   *  \retval  !NULL valid pointer */
  void* (*memset)(void* dst, int val, size_t n);

  /** \brief   compare to strings
   *  \details signature is similar to standard strcmp
   *           \note TODO: maybe memcmp will be better?
   *  \arg     str1 pointer to first string to compare
   *  \arg     str2 pointer to second string to compare
   *  \return  result of comparsion or error sequence
   *  \retval  <0 error occured/can't compare
   *  \retval  0  strings are equal
   *  \retval  >0 number of char where strings start to differ */
  int   (*strcmp)(const char* str1, const char* str2);
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
{ cont_list_t l;   /**< list container part */
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

/** \brief   start shell
 *  \details initialize variables of shell object. dynamically allocates memory
 *           for it, validates init structure and fill object fields. after
 *           this action your shell is ready to use
 *  \arg     init_struct initialization structure
 *  \return  shell object descriptor or error sequence
 *  \retval  NULL  error occured
 *  \retval  !NULL valid pointer to shell object descriptor */
void* yosh_start(const yosh_init_struct_t* init_struct);

/** \brief   input point of your shell
 *  \details place every new symbol here. this may block your thread.
 *           accumulate data what user types into terminal and start parsing it
 *           after passing new line or return carriage symbol. also in this
 *           thread user functions are called so this is a reason why it can
 *           block current thread
 *  \arg     ch         ASCII character
 *  \arg     shell_desc descriptor of the shell
 *                      \note only one method of getting it valid - using
 *                            yosh_start
 *  \return  result of shell execution
 *           \note shell result and shell functio n result are diffirent things.
 *                 shell function result remains only in shell and you can't
 *                 capture this moment outside. also shell function result
 *                 can't directly make effect on shell behavor.
 *  \retval  0  ok
 *  \retval  1  shell halted normally
 *  \retval  -1 error occured. e.g. function descriptor corrupted  */
int yosh_input(char ch, void* shell_desc);

#endif//YOSH_H

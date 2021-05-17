#ifndef STRINGS_H
#define STRINGS_H
#include <stddef.h>

#define CONT_STANDARD_STRING_EXT_VAL 10 /**< length in symbols of string extend
                                             increment */
typedef struct //yosh_string_t
{ char*  s;    ///< pointer to the string
  size_t len;  ///< length of the string
  char*  iter; ///< iterator which represent next symbol for reading
} cont_string_t;

/** \brief   malloc and free functions pointers
 *  \details needed to provide string container with multiple API's in one
 *           project. this featue may be imposrtant for embedded systems which
 *           may contain multiple components developed for baremetal systems and
 *           each contains it's own implementation of malloc and requires you
 *           to use it only. */
typedef struct //cont_string_calls_t
{ void* (*malloc)(size_t size); /**< allocate memory */
  void  (*free)(void* ptr);     /**< free allocated memory */
  void  (*memcpy)(void* dst, void* src, size_t n);
  void  (*memset)(void* dst, char val, size_t n);
  int   (*strcmp)(const char* str1, const char* str2);
} cont_string_calls_t;

/** \brief   part of string container. creates a new string
 *  \details dynamically allocates memory
 *  \arg     c memory system calls descriptor
 *  \arg     n size of string
 *  \return  poi nter to created string or error sequence
 *  \retval  null  error sequence
 *  \retval  !null valid pointer */
cont_string_t* cont_new_string(cont_string_calls_t* c, size_t n);

/** \brief   part of string container. deletes an existing string
 *  \details dynamically free memory
 *  \arg     d yosh descriptor. need to take free function
 *  \arg     s pointer to a string container */
void cont_del_string(cont_string_calls_t* c, cont_string_t* s);

#endif//STRINGS_H

#ifndef STRINGS_H
#define STRINGS_H
#include <stddef.h>

//TODO: decide about pack it in object and choose object packing model
/** \page string_container String Container
 *
 *  \section description Description
 *
 *  This code provide cpp stl style of a string in common c program. It is very
 *  flexible and can be used in any project i can imagine.
 *
 *  \section usage Usage
 *
 *  Basically usage is:
 *  * create string
 *  * manipulate it
 *  * delete string */
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

/** \brief   part of string container. extends string to larger size
 *  \details allocates ne memory and free old
 *  \arg     c string calls descriptor
 *  \arg     s pointer to a string
 *  \arg     n number of bytes to increase string volume
 *  \return  pointer to extended string */
cont_string_t* cont_ext_string(cont_string_calls_t* c, cont_string_t* s, 
                               size_t n);

/** \brief   part of string container. adds character to the end of string
 *  \details automatically extends string if neede
 *  \arg     c  string calls descriptor
 *  \arg     s  pointer to string container
 *              \note TODO: why double pointer?
 *  \arg     ch character to be added to string */
void cont_string_add_char(cont_string_calls_t* c, cont_string_t** s, char ch);

#endif//STRINGS_H

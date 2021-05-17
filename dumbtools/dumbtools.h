#ifndef DUMBTOOLS_H
#define DUMBTOOLS_H

#include <stddef.h>
/** \brief   memcpyy replacement. copy n bytes of data from source to 
 *           destination
 *  \details pretty lightweight, but dumb and slow
 *  \arg     dst pointer to destination memory
 *  \arg     src pointer to source memory
 *  \arg     n   number of bytes to copy */
void dumbtools_memcpy(void* dst, void* src, size_t n);

/** \brief   memset replacement. fill specified memory area to value
 *  \details pretty lightweight, but dumb and slow
 *  \arg     dst pointer to destination memory
 *  \arg     val value to be set in specified memory
 *  \arg     n   number of bytes to set */
void dumbtools_memset(void* dst, char val, size_t n);

/** \brief   strcmp replacement. compare two strings
 *  \details pretty lightweight but dumb and slow
 *  \arg     str1 pointer to string
 *  \arg     str2 pointer to string
 *  \return  result of comparsion or error sequence
 *  \retval  0  strings are not equal
 *  \retval  1  strings are equal
 *  \retval  -1 error occured */
int dumbtools_strcmp(const char* str1, const char* str2);
#endif//DUMBTOOLS_H

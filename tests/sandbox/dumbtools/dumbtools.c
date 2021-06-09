#include <stddef.h>
#include "dumbtools.h"

/** \brief   memcpyy replacement. copy n bytes of data from source to 
 *           destination
 *  \details needs for reduce dependencies. pretty lightweight, but dumb and 
 *           slow
 *  \arg     dst pointer to destination memory
 *  \arg     src pointer to source memory
 *  \arg     n   number of bytes to copy */
void yosh_memcpy_dumb(void* dst, void* src, size_t n)
{ char* d = dst; char* s = src; while (n > 0) { d[n - 1] = s[n - 1]; n--; } }

/** \brief   memset replacement. fill specified memory area to value
 *  \details needs to reduce depe ndencies. pretty lightweight, but dumb and
 *           slow
 *  \arg     dst pointer to destination memory
 *  \arg     val value to be set in specified memory
 *  \arg     n   number of bytes to set */
void yosh_memset_dumb(void* dst, char val, size_t n)
{ char* d = (char*)dst; for (int i = 0; i < n; i++) { *d++ = val; } }

/** \brief   strcmp replacement. compare two strings
 *  \details needs for reduce dependencies. pretty lightweight but dumb and
 *           slow
 *  \arg     str1 pointer to string
 *  \arg     str2 pointer to string
 *  \return  result of comparsion or error sequence
 *  \retval  >0 strings are not equal, it is a number of char where they starts
 *              to differ
 *  \retval  0  strings are equal
 *  \retval  -1 error occured */
int yosh_strcmp_dumb(const char* str1, const char* str2)
{ if (str1 == NULL) { return -1; }
  if (str2 == NULL) { return -1; }

  const char* str1_saved = str1; //need to calc diff position

  while(*str1 != 0 && *str2 != 0)
  { if (*str1 != *str2) { return str1 - str1_saved; } str1++; str2++; }
  if (*str1 != *str2) { return str1 - str1_saved; } //if one string is shorter

  return 0; }

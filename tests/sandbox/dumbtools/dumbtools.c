#include <stddef.h>
#include "dumbtools.h"

void dumbtools_memcpy(void* dst, void* src, size_t n)
{ char* d = dst; char* s = src; while (n > 0) { d[n - 1] = s[n - 1]; n--; } }

void dumbtools_memset(void* dst, char val, size_t n)
{ char* d = (char*)dst; for (int i = 0; i < n; i++) { *d++ = val; } }

int dumbtools_strcmp(const char* str1, const char* str2)
{ const char* str1_saved = str1; //need to calc diff position

  while(*str1 != 0 && *str2 != 0)
  { if (*str1 != *str2) { return str1 - str1_saved + 1; } str1++; str2++; }
                                                   //^ diff pos correction
  //one string may be shorter
  if (*str1 != *str2) { return str1 - str1_saved + 1; }

  return 0; }

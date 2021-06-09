#ifndef YOSH_APP_API_H
#define YOSH_APP_API_H
#include <stddef.h>
#include "yosh.h"

  /** \brief   print string in io device
   *  \details cyclic calls putchar
   *  \arg     s pointer to c-string
   *  \return  error sequence or sended chars
   *  \retval  <0  error
   *  \retval  >=0 chars sended */
static inline int yosh_puts(yosh_env_t* e, const char* ch)
{ if (e  == NULL) { return -1; } 
  if (ch == NULL) { return -1; }

  int count = 0;
  while (*ch != 0) { e->calls.putchar(*ch); ch++; count++; } 
  
  return count; }

#endif//YOSH_APP_API_H

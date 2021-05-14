#include "strings.h"

cont_string_t* cont_new_string(cont_string_calls_t* c, size_t n)
{ cont_string_t* ret = c->malloc(sizeof(cont_string_t));
  ret->s = c->malloc(n);
  yosh_memset_dumb(ret->s, 0, n);
  ret->len = n; ret->iter = ret->s;
  return ret; }

void cont_del_string(cont_string_calls_t* c, cont_string_t* s)
{ c->free(s->s); c->free(s); }

cont_string_t* cont_ext_string(cont_string_calls_t* c, cont_string_t* s, size_t n)
{ if (n == 0) { n = YOSH_STANDARD_STRING_EXT_VAL; }
  cont_string_t* ret = cont_new_string(c, s->len + n);
  yosh_memcpy_dumb(ret->s, s->s, s->len);
  ret->len = s->len + n;
  ret->iter = ret->s + (s->iter - s->s);
  cont_del_string(c, s);
  return ret; }

void cont_string_add_char(yosh_data_t* d, cont_string_t** s, char ch)
{ *(*s)->iter = ch; (*s)->iter++;

  if ((*s)->iter >= (*s)->s + (*s)->len) 
  { *s = cont_ext_string(d, *s, 0); } }

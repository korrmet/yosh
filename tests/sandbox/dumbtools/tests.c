#include <stdio.h>
#include "dumbtools.h"

#define TST_INIT() \
unsigned int passed = 0; \
unsigned int total  = 0

#define TST_START(name, func, ...) \
{ unsigned int err_flag = 0; \
  total++

#define TST_ASS(assert) \
  if (!(assert)) { printf("%s assert failed\n"); }

#define TST_END() \
  if (!err_flag) { passed++; } }

#define TST_CHECK() \
  printf("%d/%d tests passed\n", passed, total); \
  if (passed == total) { return 0; } else { return -1; }

int main(int argc, char** argv)
{ TST_INIT();
  TST_CHECK(); }

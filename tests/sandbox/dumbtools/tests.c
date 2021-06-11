#include <stdio.h>
#include <string.h>
#include "dumbtools.c"

#define TST_INIT() \
unsigned int passed = 0; \
unsigned int total  = 0

#define TST_START(func, ...) \
{ unsigned int err_flag = 0; \
  total++;\
  printf("[%s] ", #func); \
  printf(__VA_ARGS__); \
  printf("\n")

#define TST_ASS(assert) \
  if (!(assert)) { printf("%s assert failed\n", #assert); }

#define TST_END() \
  if (!err_flag) { passed++; } }

#define TST_CHECK() \
  printf("%d/%d tests passed\n", passed, total); \
  if (passed == total) { return 0; } else { return -1; }

int main(int argc, char** argv)
{ TST_INIT();

  TST_START(dumbtools_memcpy, "simple call");
    char destination[sizeof("source") + 2] =
    { 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55 };
    char check_array[sizeof("source") + 2] =
    { 0xaa, 's', 'o', 'u', 'r', 'c', 'e', 0x00, 0x55 };
    dumbtools_memcpy(&destination[1], "source", sizeof("source"));
    TST_ASS(memcmp(destination, check_array, sizeof(destination)) == 0);
  TST_END();

  TST_START(dumbtools_memset, "simple call");
    char destination[10] = 
    { 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55 };
    char check_array[10] =
    { 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55 };
    dumbtools_memset(&destination[1], 0x00, 8);
    TST_ASS(memcmp(destination, check_array, sizeof(destination)) == 0);
  TST_END();

  TST_CHECK(); }

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

#define TST_PURE_FUNC(res, func_call) \
  printf("[%s] res must be %s\n", #func_call, #res); total++; \
  if ((func_call) == res) { passed++; } else { printf("fail\n"); }

#define TST_CHECK() \
  printf("%d/%d tests passed\n", passed, total); \
  if (passed == total) { return 0; } else { return -1; }

int main(int argc, char** argv)
{ TST_INIT();

  TST_START(dumbtools_memcpy, "simple call");
    unsigned char destination[sizeof("source") + 2] =
    { 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55 };
    unsigned char check_array[sizeof("source") + 2] =
    { 0xaa, 's', 'o', 'u', 'r', 'c', 'e', 0x00, 0x55 };
    dumbtools_memcpy(&destination[1], "source", sizeof("source"));
    TST_ASS(memcmp(destination, check_array, sizeof(destination)) == 0);
  TST_END();

  TST_START(dumbtools_memset, "simple call");
    unsigned char destination[10] = 
    { 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55 };
    unsigned char check_array[10] =
    { 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55 };
    dumbtools_memset(&destination[1], 0x00, 8);
    TST_ASS(memcmp(destination, check_array, sizeof(destination)) == 0);
  TST_END();

  TST_PURE_FUNC(0, dumbtools_strcmp("foo", "foo"));
  TST_PURE_FUNC(1, dumbtools_strcmp("foo", "bar"));
  TST_PURE_FUNC(2, dumbtools_strcmp("123", "132"));
  TST_PURE_FUNC(3, dumbtools_strcmp("12",  "123"));

  TST_CHECK(); }

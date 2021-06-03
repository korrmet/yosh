#include "yosh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

yosh_init_struct_t shell = { .calls = { .putchar = putchar,
                                        .getchar = getchar,
                                        .malloc  = malloc,
                                        .free    = free,
                                        .strcmp  = strcmp },
                             .greet_string = "sandbox",
                             .user_apps = NULL };

int main(int argc, char** argv)
{ void* shell_desc = yosh_start(&shell);
  if (!shell_desc) { printf("unable to start shell\n"); return -1; }
  while (yosh_input(getchar(), shell_desc) == 0) { }
  return 0; }

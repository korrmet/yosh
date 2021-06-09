#include <stddef.h>
#include "yosh.h"
#include "yosh_app_api.h"
#include "builtin/exit.h"

int yosh_exit(yosh_env_t* env, yosh_arg_t* args);

yosh_app_t yosh_builtin_exit = { .ptr  = (void (*)(void))yosh_exit,
                                 .name = "exit",
                                 .help = "shut down console" };

int yosh_exit(yosh_env_t* env, yosh_arg_t* args) 
{ env->state = YOSH_STATE__HALT; return 0; }

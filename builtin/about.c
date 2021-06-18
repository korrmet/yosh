#include <stddef.h>
#include "yosh.h"
#include "yosh_app_api.h"
#include "builtin/about.h"

int yosh_about(yosh_env_t* env, yosh_arg_list_t* args);

yosh_app_t yosh_builtin_about = { .ptr = (void (*)(void))yosh_about,
                                  .name = "about",
                                  .help = "info about this shell" };

char* yosh_about_string =
"\
 .::::::.     + +       \n\
.::::::::.   +---- | | |\n\
:::::::: .\\  +---- | | |\n\
::::::::_,_o +---- +-+-|\n\
\n\
Licenced by APL:\n\
Asshole Public Licension:\n\
If you use this code without telling your buddies what you got it on \n\
github.com/Korrmet - you're an asshole. Come on, don't be an asshole! \n\
\n\
This shell is made for microcontrollers at first, but may be used everywhere.\n\
It's whitten on pure C and doesn't contain any platform-specific code.\n\
";

int yosh_about(yosh_env_t* env, yosh_arg_list_t* args)
{ yosh_puts(env, "YOctoSHell ");
  yosh_puts(env, env->version);
  yosh_puts(env, "\n");
  yosh_puts(env, yosh_about_string);
  return 0; }

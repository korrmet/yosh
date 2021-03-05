#include <stddef.h>
#include "yosh.h"
#include "builtin/about.h"

int yosh_about(yosh_env_t* env, yosh_arg_t* args);

yosh_app_t yosh_builtin_about = { .ptr = (void (*)(void))yosh_about,
                                  .name = "about",
                                  .help = "info about this shell" };

char* yosh_about_string =
"\
YOctoSHell v0.0a\n\
 .::::::.     + +       \n\
.::::::::.   +---- | | |\n\
:::::::: .\\  +---- | | |\n\
::::::::_,_o +---- +-+-|\n\
\n\
Licenced by APL:\n\
Asshole Public Licension:\n\
If you use this code without telling your buddies what you got it on \n\
github.com/Korrmet - you're an asshole.\n\
\n\
This shell is made for microcontrollers at first, but may be used everywhere.\n\
It's whitten on pure C and doesn't contain any platform-specific code.\n\
\n\
Motivation:\n\
I'm often think doing my job if i can do somethig after firmware is loaded\n\
inside microcontroller. In example what if i can dynamically change some\n\
variable or reinitialize interface. Ofcourse i can do it when i debugging but\n\
often we needs some extra features. If you try to google something about\n\
shell for microcontrollers you will see what it's rare thing. In my opinion\n\
authors of these shells has aim to implement standard unix/posix shell on\n\
hardware and it's is large job. I try to implement very basic and tiny shell\n\
but useful. I'm don't shure what so basic console needs to be full unix clone\n\
and i can't realize any task for it. But tasks such as turning stepper motor\n\
to an angle from uart input or get log of errors are usual. In my opinion\n\
it's enough for develop own shell which i can use in my job.\n\
\n\
Plans about next versions:\n\
- implement output redirect to another command\n\
- implement braces for manual argument borders\n\
- implement retval handling\n\
- implement shell variables extraction\n\
- implement shell login\n\
- implement adding user commands in running shell\n\
- make tests, readme and doxygen comments in code\n\
- white documentation and guidelines about using this shell\n\
";

int yosh_about(yosh_env_t* env, yosh_arg_t* args)
{ yosh_puts(env, yosh_about_string);
  return 0; }

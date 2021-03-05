#include <stddef.h>
#include "yosh.h"

int yosh_help(yosh_env_t* env, yosh_arg_t* args);

yosh_app_t yosh_builtin_help = { .ptr  = (void (*)(void))yosh_help,
                                 .name = "help",
                                 .help = "this help" };

char* yosh_help_default =
"\
usage:\n\
>help 'topic1' 'topic2' ...\n\
\n\
'topicX' - may be name of command or builtin_topic\n\
";

typedef struct //yosh_builtin_help_topic_t
{ char* name;
  char* short_description;
  char* description;
  void (*action)(yosh_env_t* env);
} yosh_builtin_help_topic_t;

void yosh_builtin_command_list(yosh_env_t* e)
{ yosh_puts(e, "built-in commands:\n");
  for (unsigned int i = 0; i < e->builtin_apps_len; i++)
  { yosh_puts(e, "  ");
    yosh_puts(e, e->builtin_apps[i]->name);
    if (e->builtin_apps[i]->help)
    { yosh_puts(e, " - ");
      yosh_puts(e, e->builtin_apps[i]->help); } 
    e->calls.putchar('\n'); } 

  yosh_puts(e, "user commands:\n");
  yosh_app_list_t* usr = (yosh_app_list_t*)e->user_apps; 
  while (usr != NULL)
  { yosh_puts(e, "  ");
    yosh_puts(e, usr->app->name);
    if (usr->app->help)
    { yosh_puts(e, " - ");
      yosh_puts(e, usr->app->help); } 
    e->calls.putchar('\n'); } }

yosh_builtin_help_topic_t yosh_builtin_topic_array[] =
{ { .name = "cli", 
    .short_description = "how to use console",
    .description =
"\
Generally you type in terminal commands and see theirs output. Commands start\n\
execution after you hit [Enter]. After that yosh get new line character.\n\
Command string may be any length but if you type too long string you can use \n\
\"\\\" symbol and hit [Enter] after that.\n\
",
    .action = NULL },
  { .name = "commands", 
    .short_description = "returns a list of commands available now",
    .description = NULL,
    .action = yosh_builtin_command_list }
};

typedef struct //yosh_builtin_help_data_t
{ yosh_builtin_help_topic_t* topic_array;
  size_t                     topic_array_size;
} yosh_builtin_help_data_t;

yosh_builtin_help_data_t yosh_builtin_help_data =
{ .topic_array = yosh_builtin_topic_array,
  .topic_array_size = sizeof(yosh_builtin_topic_array) / 
                      sizeof(yosh_builtin_help_topic_t)
};

int yosh_help(yosh_env_t* env, yosh_arg_t* args) 
{ args = (yosh_arg_t*)args->l.next; //first just a name of function

  if (!args) 
  { yosh_puts(env, yosh_help_default);
    yosh_puts(env, "available topics:\n");
    
    for (unsigned int i = 0; i < yosh_builtin_help_data.topic_array_size; i++)
    { yosh_puts(env, "  ");
      yosh_puts(env, yosh_builtin_help_data.topic_array[i].name);
      if (yosh_builtin_help_data.topic_array[i].short_description)
      { yosh_puts(env, " - ");
        yosh_puts(env, 
                  yosh_builtin_help_data.topic_array[i].short_description); }
      env->calls.putchar('\n'); } 
    return 0; }
  else 
  { while (args)
    { for (unsigned int i = 0; i < yosh_builtin_help_data.topic_array_size; i++)
      { if (yosh_strcmp_dumb(yosh_builtin_help_data.topic_array[i].name, 
                             args->str))
        { if (yosh_builtin_help_data.topic_array[i].description)
          { yosh_puts(env, yosh_builtin_help_data.topic_array[i].description); }
          if (yosh_builtin_help_data.topic_array[i].action)
          { yosh_builtin_help_data.topic_array[i].action(env); }
          break; } }

      args = (yosh_arg_t*)args->l.next; } }

  return 0; }

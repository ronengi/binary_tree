#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "error.h"

#define MAX_COMMANDS 20
#define DELIMITERS " \n\t!,."

static struct {
  char name[20];
  enum command_code_en command_code;
}
  command_table[MAX_COMMANDS] = {
    {"add", ADD},
    {"delete", DELETE},
    {"print", PRINT},
    {"clear", CLEAR},
    {"find_minimum", FIND_MINIMUM},
    {"exit", EXIT}
  };


static int get_command(char *input_str);
static int get_arg(char *input_str);
static char *shrink(char *input_str);
static char *shrink_n(char *str, int len);





/* extract commands and aruments from <input_str> and put them in the command stack */
/* return number of commands extracted or -1 if incorrect input  */
int process_input(char *input_str) {
  enum command_code_en command_code;
  int arg, commands = 0;

  while (*input_str) {
    if ((command_code = get_command(shrink(input_str))) == -1)      return -1;
    ++commands;
    switch (command_code) {

    case ADD:
      if ((arg = get_arg(input_str)) == -1)	return -1;
      push(command_code, arg);
      break;

    case DELETE:
      if ((arg = get_arg(input_str)) == -1)	return -1;
      push(command_code, arg);
      break;

    case PRINT:
    case CLEAR:
    case FIND_MINIMUM:
    case EXIT:
      push(command_code, 0);
      break;

    default:
      return -1;
      break;
    }
  }
  return commands;
}


/* searches <input_str> for a command from the command table */
/* returns the command code or -1 if not found */
static int get_command(char *input_str) {
  char *command_name;
  int tab_indx, command_length;

  for (tab_indx = 0; *((command_table + tab_indx)->name)  &&  tab_indx < MAX_COMMANDS; ++tab_indx) {
    command_name = (command_table + tab_indx)->name;
    command_length = strlen(command_name);
    if (strncmp(input_str, command_name, command_length) == 0) {
      shrink_n(input_str, command_length);
      return tab_indx;
    }
  }
  return -1;
}


/* gets a number from beginning of <input_str> */
/* returns the number or -1 if not found */
static int get_arg(char *input_str) {
  int arg = 0;
  if (!isdigit((int)input_str[0]))
    return -1;
  while (isdigit((int)input_str[0])) {
    arg *= 10;
    arg += (input_str[0] - '0');
    shrink_n(input_str, 1);
  }
  return arg;
}


/* shrinks <str> on the <len> chars in the beginning  */
static char *shrink_n(char *str, int len) {
  int read, write;
  for (read = len, write = 0; str[read]; ++read, ++write)
    str[write] = str[read];
  str[write] = '\0';
  return str;
}


/* shrinks <str> on the delimiters  */
static char *shrink(char *input_str) {
  char *delimiters = DELIMITERS;
  int read, write, i2, flag;

  for (read = write = 0; input_str[read]; ++read) {
    flag = 0;

    for (i2 = 0; delimiters[i2]; ++i2)
      flag = flag || (input_str[read] == delimiters[i2]);

    if (!flag)
      input_str[write++] = input_str[read];
  }

  input_str[write] = '\0';

  return input_str;
}

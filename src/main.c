#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "error.h"
#include "stack.h"
#include "process_input.h"


void execute_all();
void exit_program();


int main() {
  FILE *fp = stdin;
  char in_str[100];

  process_input("add 15, add 10, add 20, add 5, add 25, add 12, add 23, add 24, add 3, add 4, add 19, add 14, add 13, add 18, add 17 print");
  execute_all();

  printf("Enter commands:_");
  while (fgets(in_str, 100, fp)) {
    if (process_input(in_str) < 0)
      printf("Error: %s\n", in_str);
    execute_all();
    printf("Enter commands:_");
  }

  exit_program();
  return 0;
}


/* executes all commands in the stack */
void execute_all() {
  struct stack_node_st command;
  while (pop(&command)) {
    switch(command.command_code) {

    case ADD:
      add_to_tree(command.arg);
      break;

    case DELETE:
      delete_from_tree(command.arg);
      break;

    case PRINT:
      binary_tree_print();
      break;

    case CLEAR:
      destruct_tree();
      break;

    case FIND_MINIMUM:
      printf("\nSmallest node is: %d\n", find_minimum());
      break;

    case EXIT:
      exit_program();
      break;

    default:
      break;
    }
  }
}


void exit_program() {
  printf("\nClearing Tree...");
  destruct_tree();
  printf("ok\nClearing Command Stack...");
  clear();
  printf("ok\n\nGoodbye!\n");
  exit(0);
}

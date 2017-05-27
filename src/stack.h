#ifndef STACK_H
#define STACK_H

enum command_code_en { ADD, DELETE, PRINT, CLEAR, FIND_MINIMUM, EXIT };


typedef struct stack_node_st *stack_node_p;
struct stack_node_st {
  enum command_code_en command_code;
  int arg;
  stack_node_p next;
};



stack_node_p pop(stack_node_p out);
stack_node_p push(enum command_code_en command_code, int arg);
void clear();
int is_empty();



#endif

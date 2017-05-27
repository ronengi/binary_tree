#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "error.h"


static stack_node_p head = NULL;


stack_node_p pop(stack_node_p out) {
  stack_node_p tmp;

  if (!head)
    return NULL;

  out->command_code = head->command_code;
  out->arg = head->arg;
  out->next = NULL;

  tmp = head;
  head = head->next;
  free(tmp);

  return out;
}

stack_node_p push(enum command_code_en command_code, int arg) {
  stack_node_p indx, neo;

  neo =(stack_node_p)calloc(1, sizeof(struct stack_node_st));
  neo->command_code = command_code;
  neo->arg = arg;

  for (indx = head; indx && indx->next; indx = indx->next)
    ;
  if (indx)
    indx->next = neo;
  else
    head = neo;

  return neo;
}

void clear() {
  stack_node_p tmp;
  for (tmp = head; tmp; tmp = head) {
    head = head->next;
    free(tmp);
  }
}

int is_empty() {
  return (head == NULL);
}

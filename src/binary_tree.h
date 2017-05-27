#ifndef BINARY_TREE_H
#define BINARY_TREE_H



typedef struct tree_node_st *tree_node_p;
struct tree_node_st {
  int data;
  tree_node_p left;
  tree_node_p right;
};



tree_node_p get_tree_root();
int get_tree_depth();
int find_minimum();
tree_node_p add_to_tree(int data);
void delete_from_tree(int data);
void destruct_tree();

void binary_tree_print();



#endif

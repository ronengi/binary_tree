#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "error.h"

#define MAX(A, B) ( (A) > (B) ? (A) : (B) )


static tree_node_p tree_root = NULL;
static int tree_depth = 0;


static int get_depth(tree_node_p tree_node_indx) {
  int dr, dl;

  if (!tree_node_indx)    return 0;

  dr = get_depth(tree_node_indx->right);
  dl = get_depth(tree_node_indx->left);

  return (1 + MAX(dr, dl) );
}

static void update_tree_depth() {
  tree_depth = get_depth(tree_root);
}

static tree_node_p go_add_to_tree(tree_node_p tree_node, int data) {
  if (tree_node == NULL)
    error("Error in adding new node!\n");

  if (data < tree_node->data) {
    if (tree_node->left)
      return go_add_to_tree(tree_node->left, data);
    else {
      tree_node->left = (tree_node_p)calloc(1, sizeof(struct tree_node_st));
      tree_node->left->data = data;
      update_tree_depth();
      return tree_node->left;
    }
  }
  else if (data > tree_node->data) {
    if (tree_node->right)
      return go_add_to_tree(tree_node->right, data);
    else {
      tree_node->right = (tree_node_p)calloc(1, sizeof(struct tree_node_st));
      tree_node->right->data = data;
      update_tree_depth();
      return tree_node->right;
    }
  }
  return tree_node;
}

static tree_node_p go_find_minimum(tree_node_p tree_node) {
  if (!tree_node)    error("Searching minimum in empty tree!\n");
  if (tree_node->left)    return go_find_minimum(tree_node->left);
  return tree_node;
}

static tree_node_p go_delete_from_tree(tree_node_p tree_node, int data) {
  tree_node_p tmp;

  if (!tree_node)    return NULL;
  if (data < tree_node->data) {    tree_node->left = go_delete_from_tree(tree_node->left, data);    return tree_node;  }
  if (data > tree_node->data) {    tree_node->right = go_delete_from_tree(tree_node->right, data);    return tree_node;  }

  /* found data to be deleted */

  /* two children */
  if (tree_node->left  &&  tree_node->right ) {
    tree_node->data = go_find_minimum(tree_node->right)->data;    /* replace with smallest in right subtree */
    tree_node->right = go_delete_from_tree(tree_node->right, tree_node->data);    /* delete smallest in right subtree */
    return tree_node;
  }

  /* One or zero children - free this node and return the one existing chile (or NULL) */
  tmp = tree_node;

  if (!tree_node->left)    /* Also handles 0 children */
    tree_node = tree_node->right;
  else if (!tree_node->right)
    tree_node = tree_node->left;

  free(tmp);

  return tree_node;
}

static void go_destruct_tree(tree_node_p tree_node) {
  if (!tree_node)
    return;
  go_destruct_tree(tree_node->left);
  go_destruct_tree(tree_node->right);
  free(tree_node);
}




/************ exposed functions *************/


tree_node_p get_tree_root() {
  return tree_root;
}

int get_tree_depth() {
  return tree_depth;
}


int find_minimum() {
  if (!tree_root)
    error("Searching minimum in empty tree!\n");
  return go_find_minimum(tree_root)->data;
}


tree_node_p add_to_tree(int data) {
  if (!tree_root) {
    tree_root = (tree_node_p)calloc(1, sizeof(struct tree_node_st));
    tree_root->data = data;
    update_tree_depth();
    return tree_root;
  }

  return go_add_to_tree(tree_root, data);
}


void delete_from_tree(int data) {
  tree_root = go_delete_from_tree(tree_root, data);
    update_tree_depth();
}


void destruct_tree() {
  go_destruct_tree(tree_root);
  tree_root = NULL;
}

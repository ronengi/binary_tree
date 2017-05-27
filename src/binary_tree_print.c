#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "error.h"

typedef struct print_node_st *print_node_p;
struct print_node_st {
  tree_node_p tree_node;
  print_node_p next;
};


typedef struct level_node_st *level_node_p;
struct level_node_st {
  print_node_p print_node;
  level_node_p next;
};


static level_node_p level_one = NULL;


static void scan_tree();
static void go_print();
static void destruct();

static void go_scan_tree(tree_node_p, int);
static void create_print_node(tree_node_p, int);

static void destruct_level_nodes(level_node_p);
static void destruct_print_nodes(print_node_p);




void binary_tree_print() {
  if (!get_tree_root()) {
    printf("Empty tree!\n");
    return;
  }

  scan_tree();
  go_print();
  destruct();
}



static void scan_tree() {
  level_one = (level_node_p)calloc(1,sizeof(struct level_node_st));
  go_scan_tree(get_tree_root(), 0);
}

static void go_scan_tree(tree_node_p tree_node, int tree_node_level) {
  /* end of tree */
  if (tree_node_level >= get_tree_depth())
    return;

  create_print_node(tree_node, tree_node_level++);

  if(tree_node) {
    go_scan_tree(tree_node->left, tree_node_level);
    go_scan_tree(tree_node->right, tree_node_level);
  }
  else {
    go_scan_tree(NULL, tree_node_level);
    go_scan_tree(NULL, tree_node_level);
  }
}

static void create_print_node(tree_node_p tree_node, int tree_node_level) {
  level_node_p level_node_indx;
  print_node_p print_node_indx;

  /* get to the correct level, or create a new one */
  for (level_node_indx = level_one; level_node_indx->next && tree_node_level; level_node_indx = level_node_indx->next, --tree_node_level)
    ;

  if (tree_node_level == 1)
    level_node_indx = level_node_indx->next = (level_node_p)calloc(1, sizeof(struct level_node_st));      /* need to create one more level_node */
  else if (tree_node_level > 1)
    error("Jumping too many levels in printing tree node %d!\n", tree_node->data);                        /* incorrect printing structure */

  /* go to the last print_node in this level_node: create and connect new print_node */
  if (level_node_indx->print_node) {
    for (print_node_indx = level_node_indx->print_node; print_node_indx->next; print_node_indx = print_node_indx->next)
      ;
    print_node_indx = print_node_indx->next = (print_node_p)calloc(1, sizeof(struct print_node_st));
  }
  else
    print_node_indx = level_node_indx->print_node = (print_node_p)calloc(1, sizeof(struct print_node_st));


  /* connect new print_node to the actual tree_node */
  print_node_indx->tree_node = tree_node;
}

int pow2(int n) {
  int p;
  if (n < 0)    return 0;
  for (p = 1; n > 0; --n, p *= 2)    ;
  return p;
}

static void print_node_space(int cur_l, int max_l) {
  int diff, space;
  for (diff = 0, space = 0; diff <= (max_l - cur_l); ++diff, space += pow2(diff-1))
    ;
  /* printf("ml=%d, cl=%d, space=%d  ", max_l, cur_l, space); */
  while (space--)
    printf("  ");
}

static void print_level_space(int cur_l, int max_l) {
  /*  
node width = 2
 ( 0 +  0) * 2 =  0
 ( 0 +  1) * 2 =  2
 ( 1 +  2) * 2 =  6
 ( 3 +  4) * 2 = 14
 ( 7 +  8) * 2 = 30
 (15 + 16) * 2 = 62
  */

  int diff, space;
  for (diff = 0, space = 0; diff <= (max_l - cur_l); ++diff, space += pow2(diff-2))
    ;
  /* printf("ml=%d, cl=%d, space=%d  ", max_l, cur_l, space); */
  while (space--)
    printf("  ");
}


static void go_print() {
  level_node_p level_node_indx;
  print_node_p print_node_indx;
  int tree_node_level;

  printf("\nBinary Tree\n-----------\n");
  for (level_node_indx = level_one, tree_node_level = 1; level_node_indx; level_node_indx = level_node_indx->next, ++tree_node_level) {
    print_level_space(tree_node_level, get_tree_depth());
    for (print_node_indx = level_node_indx->print_node; print_node_indx; print_node_indx = print_node_indx->next) {
      if (print_node_indx->tree_node)
	printf("%2d", print_node_indx->tree_node->data);
      else
	printf("[]");

      print_node_space(tree_node_level, get_tree_depth());

    }
    printf("\n");
  }
  printf("-----------\n");
}



static void destruct() {
  destruct_level_nodes(level_one);
  level_one = NULL;
}

static void destruct_level_nodes(level_node_p level_node_indx) {

  if (!level_node_indx)
    return;

  destruct_level_nodes(level_node_indx->next);

  destruct_print_nodes(level_node_indx->print_node);

  free(level_node_indx);
}

static void destruct_print_nodes(print_node_p print_node_indx) {
  if (!print_node_indx)
    return;

  destruct_print_nodes(print_node_indx->next);

  free(print_node_indx);
}

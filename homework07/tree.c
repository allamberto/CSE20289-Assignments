/* tree.c: Huffman Tree */

#include "queue.h"
#include "tree.h"

#include <string.h>

/* Internal Huffman Tree Prototyes */

void	tree_count(Tree *t, FILE *stream);
Queue *	tree_queue(Tree *t);
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding);

/* External Huffman Tree Functions */

/**
 * Create Tree structure.
 * @return  Newly allocated and initialized Tree structure.
 */
Tree *  tree_create() {
  Tree *t = calloc(1, sizeof(Tree));
  if(t){
    t->root = NULL;
    int64_t countsTemp[TREE_COUNTS_SIZE] = {0};
    memcpy(t->counts, countsTemp, sizeof(countsTemp));
  }
    return t;
}

/**
 * Delete Tree structure.
 * @param   t           Tree structure.
 * @return  NULL.
 */
Tree *  tree_delete(Tree *t) {
  node_delete(t->root);
  free(t);
  return NULL;
}

/**
 * Build internal Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return  Whether or not the operation succeeded.
 */
bool	tree_build(Tree *t, FILE *stream) {
  tree_count(t, stream);
  Queue *q = tree_queue(t);
  if(!q)
    return false;
  while(q->size > 1){
    Node *node1 = queue_pop(q);
    Node *node2 = queue_pop(q);
    Node *newNode = node_create(NODE_NOT_SYMBOL, node1->count + node2->count, node1, node2);
    queue_push(q, newNode);
  }
  t->root = queue_pop(q);
  queue_delete(q);
  return true;
}

/**
 * Walk Tree structure.
 * @param   t           Tree structure.
 * @param   f           Node function.
 * @param   arg         Ndoe function argument.
 * @return  Whether or not the operation succeeded.
 */
void	tree_walk(const Tree *t, NodeFunc f, void *arg) {
  char encoding[BUFSIZ] = "";
  tree_walk_node(t->root, f, arg, encoding);
}

/* Internal Tree Functions */

/**
 * Build internal counts table in Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return
 */
void	tree_count(Tree *t, FILE *stream) {
  char buffer[BUFSIZ];
  while(fgets(buffer, BUFSIZ, stream)){
    for(int i = 0; i < strlen(buffer); i++)
      t->counts[(int)buffer[i]]++;
  }
}

/**
 * Create Priority Queue out of counts table in Tree structure.
 * @param   t           Tree structure.
 * @return  Priority Queue of Nodes corresponding to counts in Tree.
 */
Queue *	tree_queue(Tree *t) {
  Queue *q = queue_create(TREE_COUNTS_SIZE);
  if(q){
    for(int i = 0; i < TREE_COUNTS_SIZE; i++){
      if(t->counts[i]){
        queue_push(q, node_create(i, t->counts[i], NULL, NULL));
      }
    }
  }
  return q;
}

/**
 * Recursively walk Tree nodes.
 * @param   n           Node structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @param   encoding    Node encoding.
 */
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding) {
  if(!n)
    return;
  if(!n->left && !n->right){
    if (strlen(encoding) == 0){
      strcat(encoding, "0");
    }
    f(n, encoding, arg);
  }
  else{
    if(n->left){
      tree_walk_node(n->left, f, arg, strcat(encoding, "0"));
      encoding[strlen(encoding) - 1] = '\0';
    }
    if(n->right){
      tree_walk_node(n->right, f, arg, strcat(encoding, "1"));
      encoding[strlen(encoding) - 1] = '\0';
    }
  }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

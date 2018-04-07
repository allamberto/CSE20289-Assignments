/* node.c: Huffman Node */

#include "node.h"
#include "string.h"

/* Internal Node Functions */

void node_set_symbol(Node *n, int64_t letter);

/* External Node Functions */

/**
 * Create Node structure.
 * @param   symbol      Symbol letter.
 * @param   count       Initial count.
 * @param   left        Left Node child.
 * @param   right       Right Node child.
 * @return  Newly allocated Node structure with specified attributes.
 */
Node *  node_create(int64_t symbol, size_t count, Node *left, Node *right) {
  Node *node = calloc(1, sizeof(Node));
  node_set_symbol(node, symbol);
  node->count = count;
  node->left = left;
  node->right = right;
  if (node == NULL) {
    	free(node);
      return NULL;
  }
  return node;
}

/**
 * Delete Node structure.
 * @param   n           Node structure.
 * @return  NULL.
 */
Node * node_delete(Node *n) {
  if(n){
    node_delete(n->left);
    node_delete(n->right);
    free(n);
  }
  return NULL;
}

/**
 * Dump Node structure.
 * @param   n           Node structure.
 * @param   stream      I/O to write to.
 */
void node_dump(const Node *n, FILE *stream) {
  fprintf(stream, "Node{symbol: %s, count: %zu, left: 0x%zx, right: 0x%zx}\n", n->symbol.string, n->count, (int64_t)n->left, (int64_t)n->right);
}

/* Internal Node Functions */

/**
 * Set symbol attribute of Node structure.
 * @param   n           Node structure.
 * @param   letter      Node symbol letter value.
 */
void node_set_symbol(Node *n, int64_t letter) {
  n->symbol.letter = letter;
  switch(letter){
    case '\"':
      strncpy(n->symbol.string, "\\\"", sizeof(int64_t));
      break;
    case '\\':
      strncpy(n->symbol.string, "\\\\", sizeof(int64_t));
      break;
    case '\b':
      strncpy(n->symbol.string, "\\b", sizeof(int64_t));
      break;
    case '\f':
      strncpy(n->symbol.string, "\\f", sizeof(int64_t));
      break;
    case '\n':
      strncpy(n->symbol.string, "\\n", sizeof(int64_t));
      break;
    case '\r':
      strncpy(n->symbol.string, "\\r", sizeof(int64_t));
      break;
    case '\t':
      strncpy(n->symbol.string, "\\t", sizeof(int64_t));
      break;
  }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

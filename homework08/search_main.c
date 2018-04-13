/* search_main.c: Main Execution */

#include "search.h"

/* Main Execution */

int main(int argc, char *argv[]) {
  Options op = {
    .access = 0,
    .type = 0,
    .empty = false,
    .name = NULL,
    .path = NULL,
    .perm = 0,
    .newer = 0,
    .uid = -1,
    .gid = -1
  };

  char *root;
  root = argv[1];
  if(argc < 2 || (argc >= 2 && argv[1][1] == '-'))
    root = ".";
  else
    root = argv[1];


  options_parse(argc, argv, &root, &op);

  if(!filter(root, &op))
    printf("%s\n", root);

  return walk(root, &op);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

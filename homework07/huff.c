/* huff.c */

#include "tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

typedef enum {
    TSV,
    CSV,
    YAML,
    JSON,
} Format;

/* Globals */

char * PROGRAM_NAME = NULL;
void func(const Node *n, char *encoding, void *arg){
  Format f = (Format)(arg);
  switch(f){
    case TSV:
      printf("%s\t%s\t%zu\n", n->symbol.string, encoding, n->count);
      break;
    case CSV:
      printf("\"%s\",\"%s\",%zu\n", n->symbol.string, encoding, n->count);
      break;
    case YAML:
      printf("\"%s\": {\"encoding\": \"%s\", \"count\": %zu}\n", n->symbol.string, encoding, n->count);
      break;
    case JSON:
      printf("  \"%s\": {\"encoding\": \"%s\", \"count\": %zu},\n", n->symbol.string, encoding, n->count);
      break;
  }
}

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
    fprintf(stderr, "Flags:\n\n");
    fprintf(stderr, "    -f FORMAT    Output format (tsv, csv, yaml, json)\n");

    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
  int argind = 1;
  Format f = TSV;
  char *format = "tsv";

  PROGRAM_NAME = argv[0];
  while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
      char *arg = argv[argind++];
      switch (arg[1]) {
          case 'h':
              usage(0);
              break;
          case 'f':
            format = argv[argind++];
            break;
          default:
              usage(1);
              break;
      }
  }

  if(!strcmp(format, "tsv")) {f = TSV;}
  else if(!strcmp(format, "csv")) {f = CSV;}
  else if(!strcmp(format, "yaml")) {f = YAML;}
  else if(!strcmp(format, "json")) {f = JSON;}

  Tree *t = tree_create();
  if (argind == argc)
    tree_build(t, stdin);
  else{
    while (argind < argc) {
        char *path = argv[argind++];
        FILE *fs = fopen(path, "r");
        if (fs == NULL) {
            fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
            break;
        }
        tree_build(t, fs);
    }
  }
  if(f == JSON){
    puts("{");
    tree_walk(t, func, (void*)f);
    puts("}");
  }
  else
    tree_walk(t, func, (void*)f);
  tree_delete(t);
  return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Modes */
int mode;
enum {
  STRIP = 1<<1,
  REVERSE = 1<<2,
  LOWER = 1<<3,
  UPPER = 1<<4,
  STARTSWITH = 1<<5,
  ENDSWITH = 1<<6,
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s          Strip whitespace\n");
    fprintf(stderr, "   -r          Reverse line\n");
    fprintf(stderr, "   -l          Convert to lowercase\n");
    fprintf(stderr, "   -u          Convert to uppercase\n");
    fprintf(stderr, "   -t FILTER   Only include lines that start with FILTER\n");
    fprintf(stderr, "   -d FILTER   Only include lines that end with FILTER\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, char *filter, int mode) {
  char buffer[BUFSIZ];
  char *result = (char*)&buffer;
  while(fgets(result, BUFSIZ, stream)){
    result = str_chomp(result);
    result = str_translate(result, source, target);
    if (mode&STRIP) {
      result = str_strip(result);
    }
    if (mode&REVERSE) {
      result = str_reverse(result);
    }
    if (mode&LOWER) {
      result = str_lower(result);
    }
    if (mode&UPPER) {
      result = str_upper(result);
    }
    if (mode&STARTSWITH) {
      if(!str_startswith(result, filter))
        continue;
    }
    if (mode&ENDSWITH) {
      if(!str_endswith(result, filter))
        return;
    }
    printf("%s\n", result);
  }
}

/* Main Execution */

int main(int argc, char *argv[]) {
  int argind = 1;
  char *filter = "";
  char *from = "";
  char *to = "";
  PROGRAM_NAME = argv[0];

  while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
    char *arg = argv[argind++];
      switch (arg[1]) {
        case 's':
          mode |= STRIP;
          break;
        case 'r':
          mode |= REVERSE;
          break;
        case 'l':
          mode |= LOWER;
          break;
        case 'u':
          mode |= UPPER;
          break;
        case 't':
          mode |= STARTSWITH;
          filter = argv[argind++];
          break;
        case 'd':
          mode |= ENDSWITH;
          filter = argv[argind++];
          break;
        case 'h':
          usage(0);
          break;
        default:
            usage(1);
        }
    }

    if(argv[argind]){
      from = argv[argind++];
      if(argv[argind]) { to = argv[argind]; }
    }

    translate_stream(stdin, from, to, filter, mode);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

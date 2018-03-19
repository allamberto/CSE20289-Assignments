//collaborated with Sean Michalc
/* grep.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
    exit(status);
}

void grep_stream(FILE *stream, const char *pattern) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stream)) {
      if(strstr(buffer, pattern) != NULL)
        fputs(buffer, stdout);
    }
}

void grep_file(const char *path, const char *pattern) {
    FILE *fs = fopen(path, "r");
    if (fs == NULL) {
        fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
        return;
    }
    grep_stream(fs, pattern);
    fclose(fs);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }
    if(argv[1] == NULL)
      usage(1);

    char *pattern = argv[argind++];

    /* Process each file */
    if (argind == argc) {
        grep_stream(stdin, pattern);
    } else {
        while (argind < argc) {
            char *path = argv[argind++];
            if (strcmp(path, "-") == 0) {                                           /* 9 */
                grep_stream(stdin, pattern);
            } else {
                grep_file(path, pattern);
            }
        }
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

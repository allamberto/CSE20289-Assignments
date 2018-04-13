/* duplicate_options.c: Options Parsing */

#include "duplicate.h"
#include "string.h"


#include <errno.h>
#include <limits.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

/* Options Functions */

/**
 * Display usage message and exit.
 * @param   progname        Name of program.
 * @param   status          Exit status.
 */
void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options]\n\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    if=FILE     Read from FILE instead of stdin\n");
    fprintf(stderr, "    of=FILE     Write to FILE instead of stdout\n");
    fprintf(stderr, "    count=N     Copy only N input blocks\n");
    fprintf(stderr, "    bs=BYTES    Read and write up to BYTES bytes at a time\n");
    fprintf(stderr, "    seek=N      Skip N obs-sized blocks at start of output\n");
    fprintf(stderr, "    skip=N      Skip N ibs-sized blocks at start of input\n");
    exit(status);
}

/**
 * Parse command-line options.
 * @param   argc            Number of command-line arguments.
 * @param   argv            Array of command-line arguments.
 * @param   options         Pointer to Options structure.
 * @return  Whether or not parsing the command-line options was successful.
 */
bool parse_options(int argc, char **argv, Options *options) {
  int argind = 1;
  while (argind < argc && strlen(argv[argind]) > 1) {
    char *arg = argv[argind++];
    char *stop = arg + strlen(arg);
      switch (arg[0]) {
        case 'i':
          options->input_file = strchr(arg, '=') + 1;
          break;
        case 'o':
          options->output_file = strchr(arg, '=') + 1;
          break;
        case 'c':
          options->count = strtol((strchr(arg, '=') + 1), &stop, 10);
          break;
        case 'b':
          options->bytes = strtol(strchr(arg, '=') + 1, &stop, 10);
          if(options->bytes > BUFSIZ*2)
            return false;
          break;
        case 's':
          if(arg[1] == 'e'){
            options->seek = strtol(strchr(arg, '=') + 1, &stop, 10);
          }
          else if(arg[1] == 'k'){
            options->skip = strtol(strchr(arg, '=') + 1, &stop, 10);
          }
          else
            return false;
        break;
        default: usage(argv[0], 1);
      }
  }

  return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

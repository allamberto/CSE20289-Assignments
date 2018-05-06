/* duplicate_main.c: Main Execution */

#include "duplicate.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

/* Main Execution */

int main(int argc, char *argv[]) {
  Options op = {
    op.input_file = "stdin",
    op.output_file = "stdout",
    op.count = INT_MAX,
    op.bytes = DEFAULT_BYTES,
    op.seek = 0,
    op.skip = 0
  };

  if(!parse_options(argc, argv, &op))
    return EXIT_FAILURE;

  char *src = op.input_file;
  char *dst = op.output_file;

  int rfd;
  if(!streq(op.input_file, "stdin")){
    rfd = open(src, O_RDONLY);
    if (rfd < 0) {
      	fprintf(stderr, "Unable to open %s: %s\n", src, strerror(errno));
        close(rfd);
      	return EXIT_FAILURE;
    }
  }
  else
    rfd = 0;

  int wfd;
  if(!streq(op.output_file, "stdout")){
    wfd = open(dst, O_CREAT|O_WRONLY, 0644);
    if (wfd < 0) {
      close(rfd);
      close(wfd);
      fprintf(stderr, "Unable to open %s: %s\n", dst, strerror(errno));
      return EXIT_FAILURE;
    }
  }
  else
    wfd = 1;

  char buffer[op.bytes];
  int  nread;

  lseek(rfd, op.skip*op.bytes, SEEK_SET);
  lseek(wfd, op.seek*op.bytes, SEEK_SET);

  int count = 0;
  while ((nread = read(rfd, buffer, op.bytes)) > 0 && count < op.count) {
        int nwritten = write(wfd, buffer, nread);
        while (nwritten != nread) {
            nwritten += write(wfd, buffer, nread - nwritten);
        }
        count++;
  }

    close(rfd);
    close(wfd);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* walk.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <unistd.h>

/**
 * Run specified program with the bourne shell.
 * @param     command     Command to run.
 * @return    Exit status of child process.
 */
int doit(const char *command) {
  int rc = fork();
  int status;

  if (rc < 0) {
   return EXIT_FAILURE;
  }
  else if (rc == 0) {
    if(execlp(command, command, NULL) < 0){
      return EXIT_FAILURE;
    }
  }

  waitpid(rc, &status, 0);
  return status;
}

int main(int argc, char *argv[]) {
    if(argc < 2){
      printf("Usage: ./doit COMMAND\n");
      return EXIT_SUCCESS;
    }
    else
      return WEXITSTATUS(doit(argv[1]));
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

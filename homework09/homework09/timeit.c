/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0
#define debug(M, ...) \
    if (Verbose) { \
        fprintf(stderr, "%s:%d:%s: " M, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    }

/* Globals */

int  Timeout = 10;
bool Verbose = false;

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] command...\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -t SECONDS  Timeout duration before killing command (default is %d)\n", Timeout);
    fprintf(stderr, "    -v          Display verbose debugging output\n");
    exit(status);
}

/**
 * Parse command line options.
 * @param   argc        Number of command line arguments.
 * @param   argv        Array of command line argument strings.
 * @return  Array of strings representing command to execute.
 */
char ** parse_options(int argc, char **argv) {
  int argind = 1;
  char **strs;
  while (argind < argc && argv[argind][0] == '-') {
    if(streq(argv[argind], "-h")){
        usage(argv[0], 0);
    }
    else if(streq(argv[argind], "-t")){
        Timeout = atoi(argv[++argind]);
    }
    else if(streq(argv[argind], "-v")){
        Verbose = true;
    }
    ++argind;
  }

  strs = malloc((argc-argind) * sizeof(char*));
  for(int i = 0; i < (argc-argind); i++){
    strs[i] = argv[argind++];
  }
  return strs;
}

/**
 * Handle signal.
 * @param   signum      Signal number.
 */
void    handle_signal(int signum) {
    debug("Received interrupt: %d\n", signum);
}

/* Main Execution */

int	main(int argc, char *argv[]) {
  parse_options(argc, argv);
  struct time st, fin;
  long seconds;
  clock_gettime(CLOCK_MONOTONIC, &st);
  int sig = signal(SIGCHLD, handle_signal);
  int f = fork();
  if(f < 0){
    fprintf(stderr, "Can't fork: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  if(f == 0){
    execlp(command, command, NUll);
    _exit(EXIT_FAILURE);
  }else{
    int n = nanosleep(Timeout);
    if(n == 0){ //kill
      kill(child pid, SIGCHLD);
    }
    else{ //interrupted
      while ((pid = wait(&status)) < 0);
      if(pid != -1 && WIFEXITED(status)){
        if(WEXITSTATUS(status) == 0)
           return true;
       else
           return false;
      }
      clock_gettime(CLOCK_MONOTONIC, &fin);
      seconds = fin.tv_sec - st.tv_sec;
    }
  }



  //0 - kill child success
  //<0 - wait don't kill
  //end - start
  //+(" ".sec)
  return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

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
  char **strs = NULL;
  while (argind < argc && argv[argind][0] == '-') {
    if(streq(argv[argind], "-h") || argc < 2){
        usage(argv[0], 0);
    }
    else if(streq(argv[argind], "-t")){
      Timeout = atoi(argv[++argind]);
        ++argind;
    }
    else if(streq(argv[argind], "-v")){
        Verbose = true;
        ++argind;
    }
  }

  debug("Timeout = %i\n", Timeout);
  debug("Verbose = %i\n", Verbose);
  if((argc - argind) > 0){
    strs = malloc((argc-argind + 1) * sizeof(char*));
    if(!strs) //check if malloc fails
      return strs;
    for(int i = 0; i < (argc-argind); i++){
      strs[i] = argv[argind + i];
    }
  strs[argc-argind] = NULL;
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
  char **command = parse_options(argc, argv);
  if(!command){
    free(command);
    return EXIT_FAILURE;
  }
  struct timespec st;
  struct timespec fin;
  struct timespec na = {Timeout, 0};
  int pid;
  int status = EXIT_FAILURE;
  debug("Registering handlers...\n");
  signal(SIGCHLD, handle_signal);
  debug("Grabbing start time...\n");
  clock_gettime(CLOCK_MONOTONIC, &st);
  //alarm(Timeout);
  int f = fork();
  if(f < 0){ //Failure
    fprintf(stderr, "Can't fork: %s\n", strerror(errno));
    free(command);
    return EXIT_FAILURE;
  }
  else if(f == 0){ //Child
    debug("Executing child...\n");
    execvp(command[0], command);
    fprintf(stderr, "Can't exec: %s\n", strerror(errno));
    free(command);
    _exit(EXIT_FAILURE);
  }
  else{ //Parent
    debug("Sleeping for %i seconds\n", Timeout);
    int n = nanosleep(&na, NULL);
    if(n == 0){ //kill
        debug("Killing child ");
        printf("%i\n", f);
        kill(f, SIGKILL);
    }
    debug("Waiting for child\n");
    while ((pid = wait(&status)) < 0);
  }

  if(pid != -1 && WIFEXITED(status))
    status = WEXITSTATUS(status);
  else
    status = WTERMSIG(status);
  debug("Grabbing end time...\n");
  clock_gettime(CLOCK_MONOTONIC, &fin);
  time_t timediff = (fin.tv_sec - st.tv_sec)+(fin.tv_sec - st.tv_sec)/1000000000.0;
  printf("Time Elapsed: %lld.0\n", (long long) timediff);
  free(command);
  return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

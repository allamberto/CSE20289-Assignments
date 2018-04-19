/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s files...\n", progname);
    exit(status);
}

/**
 * Save list of file paths to temporary file.
 * @param   files       Array of path strings.
 * @param   n           Number of path strings.
 * @return  Newly allocated path to temporary file.
 */
char *	save_files(char **files, size_t n) {
    char buffer[] = "XXXXXX"; ///tmp/exXXXXXX/
    int fd = mkstemp(buffer);
    if(fd < 0){
      fprintf(stderr, "1 Error: %s", strerror(errno));
      return NULL;
    }
    FILE *f = fdopen(fd, "w");
    if(!f){
      fprintf(stderr, "2 Error: %s", strerror(errno));
      close(fd);
      return NULL;
    }
    for(int i = 1; i < n; i++){
      fprintf(f, "%s\n", files[i]);
    }
    close(fd);
    return strdup(buffer);
}

/**
 * Run $EDITOR on specified path.
 * @param   path        Path to file to edit.
 * @return  Whether or not the $EDITOR process terminated successfully.
 */
bool	edit_files(const char *path) {
  int status = EXIT_SUCCESS;
  char *search;
  search = getenv("EDITOR");
  if(search == NULL)
    search = "vim";

  int pid = fork();
  sleep(1);
  if (pid < 0) {	    // Error
	   fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	   return false;
  }
  else if (pid == 0) {	    // Child
	   //printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
	   if (execlp(search, path, NULL) < 0) {
	      fprintf(stderr, "Unable to execlp: %s\n", strerror(errno));
	      return false;
	   }
  } else {		    // Parent
	   while ((pid = wait(&status)) < 0);
     if(pid != -1 && WIFEXITED(status)){
       return WEXITSTATUS(status);
     }
  }
  return false;
}

/**
 * Rename files as specified in contents of path.
 * @param   files       Array of old path names.
 * @param   n           Number of old path names.
 * @param   path        Path to file with new names.
 * @return  Whether or not all rename operations were successful.
 */
bool	move_files(char **files, size_t n, const char *path) {
  FILE *fp = NULL;
  char line[BUFSIZ];
  fp = fopen(path, "r");
  if (!fp) {
    fprintf(stderr, "Can't open: %s\n", strerror(errno));
    fclose(fp);
    return false;
  }

  for(int i = 1; i < n; i++){
    if(fgets(line, BUFSIZ, fp)){
    strchomp(line);
    if(!streq(files[i], line)){
      if(rename(files[i], line) < 0){
        fprintf(stderr, "Can't rename: %s\n", strerror(errno));
        fclose(fp);
        return false;
      }
    }
  }
  }
  fclose(fp);
  return true;
}

/* Main Execution */

int	main(int argc, char *argv[]) {
  //printf("1\n");
  if(argc < 2 || streq(argv[1], "-h")){
    //printf("2\n");
    usage(argv[0], 0);
  }
  char **files = argv;
  char* path = save_files(files, argc - 1);
  //printf("3\n");
  if(!edit_files(path)){
    unlink(path);
    free(path);
    return EXIT_FAILURE;
  }
  //printf("4\n");
  if(!move_files(files, argc - 1, path)){
    unlink(path);
    free(path);
    return EXIT_FAILURE;
  }
  //printf("5\n");
  unlink(path);
  free(path);
  return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

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
    char buffer[] = "XXXXXX";
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
    fflush(f);
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
  char *search = getenv("EDITOR");
  if(!search)
    search = "vim";

  int pid = fork();
  if (pid < 0) {	    // Error
	   fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	   return false;
  }
  else if (pid == 0) {	    // Child
	   execlp(search, search, path, NULL);
	   fprintf(stderr, "Unable to execlp: %s\n", strerror(errno));
     unlink(path);
     free((char*)path);
     _exit(EXIT_FAILURE);
  }
  else {		    // Parent
	   while ((pid = wait(&status)) < 0);
     if(pid != -1 && WIFEXITED(status)){
       if(WEXITSTATUS(status) == 0)
          return true;
      else
          return false;
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
  int status = EXIT_FAILURE;
  if(argc < 2 || streq(argv[1], "-h")){
    usage(argv[0], 0);
  }
  char **files = argv;
  char* path = save_files(files, argc);
  if(path == NULL){
    goto end;
  }
  if(!edit_files(path)){
    fprintf(stderr, "Failed Edit: %s\n", strerror(errno));
    goto end;
  }
  if(!move_files(files, argc, path)){
    goto end;
  }

  status = EXIT_SUCCESS;

end:
  unlink(path);
  free(path);
  return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* search_walk.c: Walk */

#include "search.h"

#include <errno.h>
#include <dirent.h>

/* Walk Functions */

/**
 * Recursively walk the root directory with specified options.
 * @param   root        Root directory path.
 * @param   options     User specified filter options.
 * @return  Whether or not walking this directory was successful.
 */
int walk(const char *root, const Options *options) {
  struct stat s;
  DIR *d = opendir(root);
  if(!d){
    fprintf(stderr, "ErrorG: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  errno = 0;
  struct dirent *read = readdir(d);
  if(errno){
    fprintf(stderr, "ErrorP: %s\n", strerror(errno));
    closedir(d);
    return EXIT_FAILURE;
  }

  while(read){
    char path[BUFSIZ];
    if(!streq(read->d_name, ".") && !streq(read->d_name, "..")){
        sprintf(path, "%s/%s", root, read->d_name);
        if(!filter(path, options))
          printf("%s\n", path);

        if(lstat(path, &s)){
          fprintf(stderr, "ErrorG: %s\n", strerror(errno));
          closedir(d);
          return EXIT_FAILURE;
        }

        if(read->d_type == DT_DIR){
          walk(path, options);
    }
  }
    errno = 0;
    read = readdir(d);
    if(errno){
      fprintf(stderr, "ErrorPPP: %s\n", strerror(errno));
      closedir(d);
      return EXIT_FAILURE;
    }

  }

  closedir(d);
  return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

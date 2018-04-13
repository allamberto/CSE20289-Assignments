/* search_utilities.c: Utilities */

#include "search.h"

#include <errno.h>
#include <dirent.h>

/* Utility Functions */

/**
 * Checks whether or not the directory is empty.
 * @param   path    Path to directory.
 * @return  Whether or not the path is an empty directory.
 */
bool is_directory_empty(const char *path) {
  DIR* d = opendir(path);
  if(d == NULL){
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return false;
  }

  int count = 0;
  struct dirent *read;
  while((read = readdir(d))) {
    count++;
  }
  closedir(d);
  return count == 2;
}

/**
 * Retrieves modification time of file.
 * @param   path    Path to file.
 * @return  The modification time of the file.
 */
time_t get_mtime(const char *path) {
  struct stat s;
  if(lstat(path, &s) != 0){
    fprintf(stderr, "Error: Stat of %s failed: %s\n", path, strerror(errno));
  }
  return s.st_mtim.tv_sec;

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

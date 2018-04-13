/* search_filter.c: Filters */

#include "search.h"

#include <errno.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
#include <libgen.h>

/* Internal Filter Functions */

bool filter_access(const char *path, const struct stat *stat, const Options *options) {
    return ((options->access) && (access(path, options->access) != 0));
}

bool filter_type(const char *path, const struct stat *stat, const Options *options) {
    if(options->type){
      if(options->type == 'f' && !S_ISREG(stat->st_mode)){
        return true;
    }
      else if(options->type == 'd' && !S_ISDIR(stat->st_mode)){
        return true;
      }
    }
    return false;

}

bool filter_empty(const char *path, const struct stat *stat, const Options *options) {
  if(options->empty){
    if(S_ISDIR(stat->st_mode) && is_directory_empty(path)){
      return false;
    }
    if(S_ISREG(stat->st_mode) && stat->st_size == 0){
      return false;
    }
    return true;
  }
  return false;
}

bool filter_name(const char *path, const struct stat *stat, const Options *options) {
    if(options->name){
      char base_path[BUFSIZ];
      strcpy(base_path, path);
      if (fnmatch(options->name, basename(base_path), FNM_PATHNAME))
        return true;
    }
    return false;
}

bool filter_path(const char *path, const struct stat *stat, const Options *options) {
    if(options->path){
      if (fnmatch(options->path, path, 0))
        return true;
    }
    return false;
}

bool filter_perm(const char *path, const struct stat *stat, const Options *options) {
    return options->perm && ((stat->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) != options->perm);
}

bool filter_newer(const char *path, const struct stat *stat, const Options *options) {
    return (options->newer) && (options->newer >= stat->st_mtim.tv_sec);
}

bool filter_uid(const char *path, const struct stat *stat, const Options *options) {
    return (options->uid != -1) && (options->uid != stat->st_uid);
}

bool filter_gid(const char *path, const struct stat *stat, const Options *options) {
    return (options->gid != -1) && (options->gid != stat->st_gid);
}

FilterFunc FILTER_FUNCTIONS[] = {   /* Array of function pointers. */
    filter_access,
    filter_type,
    filter_empty,
    filter_name,
    filter_path,
    filter_perm,
    filter_newer,
    filter_uid,
    filter_gid,
    NULL,
};

/* External Filter Functions */

/**
 * Filter path based options.
 * @param   path        Path to file to filter.
 * @param   options     Pointer to Options structure.
 * @return  Whether or not the path should be filtered out (false means include
 * it in output, true means exclude it from output).
 */
bool filter(const char *path, const Options *options) {
  struct stat s;
  if (lstat(path, &s) == -1){
		fprintf(stderr, "Unable to open %s: %s\n", path, strerror(errno));
		return EXIT_FAILURE;
	}

  for(int i = 0; FILTER_FUNCTIONS[i] != NULL; i++){
    if(FILTER_FUNCTIONS[i](path, &s, options))
      return true;
  }
  return false;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

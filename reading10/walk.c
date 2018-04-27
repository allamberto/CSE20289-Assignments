#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  DIR *direc = opendir(".");
  struct dirent *d;
  struct stat fileStat;
  char *file;

  while ((d = readdir(direc)) != NULL){
    file = d->d_name;
    stat(file, &fileStat);
    if(S_ISREG(fileStat.st_mode))
      printf("%s %llu\n", file, (unsigned long long)fileStat.st_size);
  }
  closedir(direc);
  return 0;
}

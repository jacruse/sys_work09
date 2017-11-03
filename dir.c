#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void ls(char path[40]) {
  DIR * dir;
  if (!(dir = opendir(path))) {
    return;
  }
  struct dirent * item = readdir(dir);

  printf("Directories:\n");
  while (item) {
    if (item->d_type == DT_DIR) {
      printf("\t%s\n", item->d_name);
    }
    item = readdir(dir);
  }
  closedir(dir);

  
  if (!(dir = opendir(path))) {
    return;
  }
  item = readdir(dir);

  printf("Files:\n");
  while (item) {
    if (item->d_type == DT_REG) {
      printf("\t%s\n", item->d_name);
    }
    item = readdir(dir);
  }
  closedir(dir);
}

int get_dir_size(char path[64]) {
  int sum = 0;
  DIR * dir;
  struct stat buf;
  char * file_name = (char *) malloc(64);
  strcpy(file_name, path);

  if (!(dir = opendir(path))) {
    return -1;
  }

  struct dirent * item = readdir(dir);

  printf("Getting dir size...\n");
  while (item) {
    if (item->d_type == DT_REG) {
      if (stat(strcat(strcat(file_name,"/"),(item->d_name)), &buf) == -1) {
	printf("Failed to fetch buf\n");	
      }
      //printf("%s\n", file_name);
      //printf("\tsize of %s: %lld\n", item->d_name, buf.st_size);
      sum += buf.st_size;
    }
    item = readdir(dir);
    strcpy(file_name, path);
  }
  closedir(dir);
  return sum;
}

  

int main() {
  int size;
  printf("Statistics for directory: \"folder\"\n");
  size = get_dir_size("folder");
  printf("Size of Directory \"folder\": %d Bytes\n", size);

  ls("folder");

  printf("Statistics for directory: \".\"\n");
  size = get_dir_size(".");
  printf("Size of Directory \".\": %d Bytes\n", size);

  ls(".");
}

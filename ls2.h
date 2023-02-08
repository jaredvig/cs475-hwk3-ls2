#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


#define TRUE 1
#define FALSE 0
#define INDENT "    "
typedef struct filesystementry{
  char* name;
  int depth;
  int bytes;
  char* type;
} filesystementry;


// TODO: Function declarations here for ls2
void ls2arg(char* currentPath,int depth,stack_t* stack,char* name);
int ls2args(char* currentPath, char* targetFile,int depth,stack_t* stack,char* name);
struct stat getPathInfo(char* path);
char** searchDirectory(char* directory, int* validLinks);
#endif

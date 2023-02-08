#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"



// TODO: function definitions here for ls2

void ls2arg(char* currentPath,int depth,stack_t* stack, char* name){
struct stat pathInfo = getPathInfo(currentPath);
if(S_ISDIR(pathInfo.st_mode)){
    int children = 0;
char** directoryContents = searchDirectory(currentPath,&children);
 if(depth>-1){
        
    filesystementry currentDirectory;
    filesystementry* currentDirectoryPtr = (filesystementry*)malloc(sizeof(filesystementry));
    currentDirectoryPtr->name =(char*)malloc(sizeof(char)*strlen(name)+1);
    currentDirectoryPtr->depth =(int)malloc(sizeof(int));
    currentDirectoryPtr->bytes =(int)malloc(sizeof(int));
    currentDirectoryPtr->type =(char*)malloc(sizeof(char)*10);
    strcpy(currentDirectoryPtr->name,name); 
    currentDirectoryPtr->depth=depth;
    strcpy(currentDirectoryPtr->type,"directory");
    currentDirectoryPtr->bytes=0;
   // currentDirectoryPtr = &currentDirectory;
    push(stack,currentDirectoryPtr);
    }
for(int i =0;i<children;i++){
    char *pathCopy = (char*)malloc(sizeof(char)*(strlen(currentPath)+2+strlen(directoryContents[i])));
    strcpy(pathCopy,currentPath);
    //printf("%s\n",directoryContents[i]);
    strcat(pathCopy,"/");
    //printf("%s\n",currentPath);
    ls2arg(strcat(pathCopy,directoryContents[i]),depth+1,stack,directoryContents[i]);
    //free(pathCopy);
    free(pathCopy);
    free(directoryContents[i]);
}
free(directoryContents);
} else if(S_ISREG(pathInfo.st_mode)){
    if(depth>-1){
        filesystementry* currentFilePtr = (filesystementry*)malloc(sizeof(filesystementry));
        currentFilePtr->name =(char*)malloc(sizeof(char)*strlen(name)+1);
        currentFilePtr->depth =(int)malloc(sizeof(int));
        currentFilePtr->bytes =(int)malloc(sizeof(int));
        currentFilePtr->type =(char*)malloc(sizeof(char)*5);
        strcpy(currentFilePtr->name,name); 
        currentFilePtr->depth=depth;
        currentFilePtr->bytes=pathInfo.st_size;
        strcpy(currentFilePtr->type,"file");
        push(stack,currentFilePtr);
    }

}

}
int ls2args(char* currentPath, char* targetFile, int depth,stack_t* stack, char* name){
struct stat pathInfo = getPathInfo(currentPath);
if(S_ISDIR(pathInfo.st_mode)){
    int children = 0;
char** directoryContents = searchDirectory(currentPath,&children);
int foundTarget =0;
for(int i =0;i<children;i++){
    char *pathCopy = (char*)malloc(sizeof(char)*(strlen(currentPath)+2+strlen(directoryContents[i])));
    strcpy(pathCopy,currentPath);
    //printf("%s\n",directoryContents[i]);
    strcat(pathCopy,"/");
    //printf("%s\n",currentPath);
    if(ls2args(strcat(pathCopy,directoryContents[i]),targetFile, depth+1,stack,directoryContents[i])){
        foundTarget=1;
    }
    //free(pathCopy);
    free(pathCopy);
    free(directoryContents[i]);
}
if(depth>-1&&foundTarget){
        
    filesystementry currentDirectory;
    filesystementry* currentDirectoryPtr = (filesystementry*)malloc(sizeof(filesystementry));
    currentDirectoryPtr->name =(char*)malloc(sizeof(char)*strlen(name)+1);
    currentDirectoryPtr->depth =(int)malloc(sizeof(int));
    currentDirectoryPtr->bytes =(int)malloc(sizeof(int));
    currentDirectoryPtr->type =(char*)malloc(sizeof(char)*10);
    strcpy(currentDirectoryPtr->name,name); 
    currentDirectoryPtr->depth=depth;
    strcpy(currentDirectoryPtr->type,"directory");
    currentDirectoryPtr->bytes=0;
   // currentDirectoryPtr = &currentDirectory;
    push(stack,currentDirectoryPtr);
    }
free(directoryContents);
return foundTarget;
} else if(S_ISREG(pathInfo.st_mode)){
    if(depth>-1){
        if(strcmp(targetFile,name)==0){
        filesystementry* currentFilePtr = (filesystementry*)malloc(sizeof(filesystementry));
        currentFilePtr->name =(char*)malloc(sizeof(char)*strlen(name)+1);
        currentFilePtr->depth =(int)malloc(sizeof(int));
        currentFilePtr->bytes =(int)malloc(sizeof(int));
        currentFilePtr->type =(char*)malloc(sizeof(char)*5);
        strcpy(currentFilePtr->name,name); 
        currentFilePtr->depth=depth;
        currentFilePtr->bytes=pathInfo.st_size;
        strcpy(currentFilePtr->type,"file");
        push(stack,currentFilePtr);
        return 1;
        } else{
            return 0;
        }
    }

}
return stack;
}
struct stat getPathInfo(char* path){
    struct stat pathInfo;
    lstat(path,&pathInfo);
    return pathInfo;
}
char** searchDirectory(char* directory, int* validLinks){
    struct dirent *dp;
    DIR *dirp = opendir(directory);
     while((dp = readdir(dirp)) != NULL){
        if(strcmp(dp->d_name,".")!=0&&strcmp(dp->d_name,"..")!=0&&strlen(dp->d_name)>1){
            ++*validLinks;
        }
     }
     //closedir(dirp);
     closedir(dirp);
     dirp = opendir(directory);
    char ** directoryContents =(char**)malloc (sizeof(char*) * *validLinks);
    int i =0;
    while(dirp){
        if ((dp = readdir(dirp)) != NULL) {
            if(strcmp(dp->d_name,".")!=0&&strcmp(dp->d_name,"..")!=0&&strlen(dp->d_name)>1){
            directoryContents[i] =(char*)malloc(sizeof(char)*strlen(dp->d_name)+1);
            strcpy(directoryContents[i],dp->d_name);
            i++;
            }
        } else{
            closedir(dirp);
            return directoryContents;
        }
    }
}

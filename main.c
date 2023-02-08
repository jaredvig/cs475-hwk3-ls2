#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"
#include <string.h>

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
		stack_t *stack = initstack();
		stack_t *reverseStack = initstack();
	if(argc==1){

		printf("You either put too few arguments in the command line (please use 1 or 2)\n");
	}else if(argc>3){
		printf("You put too many arguments in the command line (please use 1 or 2)\n");
	} else{
		char* baseDirectory= argv[1];
		if(argc==2){
			ls2arg(baseDirectory,-1,stack, baseDirectory);
		} else{
			ls2args(baseDirectory,argv[2],-1,stack,baseDirectory);
		}

			// stack stores the lines to print out

	//push(s, "Hello1");
	//push(s, "Hello2");
	//push(s, "Hello3");

	// print stack
	//printstack(stack);

	// free up stack
	//freestack(s);
	while(stack->size){
		if(argc==2){
	push(reverseStack,pop(stack));
		} else{
			filesystementry* currentEntryPtr = pop(stack);
		for(int i =0; i<currentEntryPtr->depth;i++){
			printf("\t");
		}
		printf("%s",currentEntryPtr->name);
		if(strcmp(currentEntryPtr->type,"file")==0){
			printf("(%d Bytes)",currentEntryPtr->bytes);
		}
		printf("\n");
		free(currentEntryPtr->name);
		free(currentEntryPtr->bytes);
		free(currentEntryPtr->type);
		free(currentEntryPtr->depth);
		free(currentEntryPtr);
		currentEntryPtr = NULL;
		}
		
	}
	if(argc==2){
	while(reverseStack->size){
		filesystementry* currentEntryPtr = pop(reverseStack);
		for(int i =0; i<currentEntryPtr->depth;i++){
			printf("\t");
		}
		printf("%s",currentEntryPtr->name);
		if(strcmp(currentEntryPtr->type,"file")==0){
			printf("(%d Bytes)",currentEntryPtr->bytes);
		}
		printf("\n");
		free(currentEntryPtr->name);
		free(currentEntryPtr->bytes);
		free(currentEntryPtr->type);
		free(currentEntryPtr->depth);
		free(currentEntryPtr);
		currentEntryPtr = NULL;
	}
	}
	freestack(stack);
	freestack(reverseStack);

	}
	return 0;
}

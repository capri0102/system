#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: [filename]\n");
		exit(1);
	}
	if(remove(argv[1]) == 0)
		printf("Remove Success!\n");
	else
		printf("Remove Fail!\n");
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: [filename]\n");
		exit(1);
	}
	
	if(access(argv[1], W_OK) == -1){
		fprintf(stderr, "User cannot write file %s\n", argv[1]);
		exit(1);
	}

	printf("%s writable, proceeding\n", argv[1]);
	return 0;
}

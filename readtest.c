#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 512

int main(int argc, char *argv[]){
	char buffer[BUFSIZE];
	int filedes;
	ssize_t nread;
	long int total = 0;

	if(argc != 2){
		printf("ERROR FORMAT <filename>\n");
		exit(1);
	}
	if((filedes = open(argv[1], O_RDONLY)) == -1){
		printf("error in opening af\n");
		exit(1);
	}
	printf("Open File : %s\n", argv[1]);

	while((nread = read(filedes, buffer, BUFSIZE)) > 0){
		printf("Read[%ld]\n", nread);
		total += nread;
	}
	close(filedes);
	printf("total chars in %s file : %ld\n",argv[1], total);

	return 0;
}

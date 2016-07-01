#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 512
#define PERM 0644

int copyfile(const char* name1, const char* name2){
	int infile, outfile;
	ssize_t nread;
	char buffer[BUFSIZE];
	
	if((infile = open(name1, O_RDONLY)) == -1)
		return -1;

	if((outfile = open(name2, O_WRONLY|O_CREAT|O_TRUNC, PERM)) == -1)
		return -2;

	while((nread = read(infile, buffer, BUFSIZE)) > 0){
		if(write(outfile, buffer, nread) < nread){
			close(infile);
			close(outfile);
			return -3;
		}
	}

	close(infile);
	close(outfile);
	

	if(nread == -1)
		return -4;
	else
		return 0;
}


int main(int argc, char* argv[]){
	int temp;
	if(argc != 3){
		printf("Usage : copy  [infile] [outfile]\n");
		exit(1);
	}

	if((temp = copyfile(argv[1],argv[2])) == 0)
		printf("SUCCESS COPYFILE!\n");
	else{
		printf("ERROR COPYFILE!\n");
		switch(temp){
		case -1:
			printf("Infile open ERROR\n");
		break;
		case -2:
			printf("Outfile open ERROR\n");
		break;
		case -3:
			printf("Write ERROR\n");
		break;
		case -4:
			printf("Read ERROR\n");	
		break;
		default:
		break;
		}
	}
	return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int filestatus(int filedes){
	int arg1;
	if((arg1 = fcntl(filedes, F_GETFL)) == -1)	return -1;
	
	switch(arg1 & O_ACCMODE){
		case O_WRONLY	:	printf("write-only");	break;
		case O_RDWR	:	printf("read-write");	break;
		case O_RDONLY	:	printf("read-only");	break;
		default		:	printf("no such mode");	break;
	}

	if(arg1 & O_APPEND)	printf(" - append flag set");
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){
	int filestatus (int);
	int fd;
	int mode, flag;
	if(argc != 4){
		printf("Usage: [Filename] [Mode] [Append]\n");
		printf("Mode: 1-Write, 2-Read&Write, 3-Read\n");
		printf("Append: 0-On 1-OFF\n");
		exit(1);
	}

	mode = atoi(argv[2]);
	flag = atoi(argv[3]);
	if(mode < 1 && mode > 3){
		printf("Mode ERROR!\n");
		exit(1);
	}
	if(flag < 0 && flag > 1){
		printf("Flag ERROR!\n");
		exit(1);
	}
	if(flag == 0){
		switch(mode){
			case 1:	fd = open(argv[1], O_WRONLY|O_APPEND);	break;
			case 2: fd = open(argv[1], O_RDWR|O_APPEND);	break;
			case 3:	fd = open(argv[1], O_RDONLY|O_APPEND);	break;
		}
	}
	else{
		switch(mode){
			case 1:	fd = open(argv[1], O_WRONLY);	break;
			case 2: fd = open(argv[1], O_RDWR);	break;
			case 3:	fd = open(argv[1], O_RDONLY);	break;
		}
	}
	if(fd == -1){
		printf("File open ERROR!\n");
		exit(1);
	}
	filestatus(fd);
	
	return 0;
}

	

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(void){
	int fd;

	if((fd = open("nonesuch", O_RDONLY)) == -1){
		perror("error opening nonesuch");
	}
	return 0;
}

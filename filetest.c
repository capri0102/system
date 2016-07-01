#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
	int fd;
	ssize_t nread;
	char buf[1024];
	

	fd = open("data", O_RDONLY);
	nread = read(fd, buf, 1024);
	

	printf("nread : %ld\n", nread);	
	buf[nread] = '\0';
	printf("%s", buf);

	close(fd);

	return 0;
}

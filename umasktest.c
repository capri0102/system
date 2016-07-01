#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
	int filedes = open("umasktest", O_WRONLY|O_CREAT, 0777);
	close(filedes);
	
	return 0;
}

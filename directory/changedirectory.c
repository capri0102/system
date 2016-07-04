#include <stdio.h>
#include <unistd.h>

#define VERYBIG	200

void my_pwd(void);

int main(void){
	my_pwd();
	return 0;
}

void my_pwd(void){
	char dirname[VERYBIG];
	if(getcwd(dirname, VERYBIG) == NULL)
		perror("getcwd error");
	else
		printf("%s\n", dirname);
}	

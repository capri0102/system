#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0644
/******************** option *********************
 -n : file name if not input default value use
 -s : make file size option if not input default value use
 -o : [required] open file name
 -d : story directory option if ignore directory make directory, if not input
      excution directory
***************************************************/
void print_help();
int main(int argc, char **argv){
	int option[4] = {0};
	int i;
	if(argc < 4 && argc > 9){
		print_help();
		exit(1);
	}	
	return 0;
}

void print_help(){
		fprintf(stderr, "Usage: fslide [OPTION]... FILE...");
		fprintf(stderr, "OPTION");
		fprintf(stderr, " -o\tDestination filename");
}

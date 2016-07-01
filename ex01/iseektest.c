#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>

#define NAMELENGTH 11
#define NROOMS 10


char namebuf[NAMELENGTH];
char roominfo[NROOMS];
int infile = -1;
off_t offset = 0;

char *getoccupier(int roomno){
	ssize_t nread;

	if((infile = open("residents", O_RDONLY)) == -1)
		return NULL;

	if(lseek(infile, offset, SEEK_SET) == -1)
		return NULL;
	if((nread = read (infile, namebuf, NAMELENGTH)) <= 0)
		return NULL;
	if(namebuf[0] == 10){
		roominfo[roomno-1] = 0;
		offset += 1;
		return "EMPTY ROOM";
	}
	else{
		roominfo[roomno-1] = 1;
		offset += 11;
		namebuf[nread -1] = '\0';
	}
	close(infile);
	return namebuf;
}
void printhotel(void){
	int i;
	char *p;
	offset = 0;
	printf("---------- HOTEL ROOM INFO ----------\n");
	for(i=1; i< NROOMS; i++){
		if(p = getoccupier(i))
			printf("\t Room %2d : %s\n", i, p);
		else
			printf("ERROR on room %d\n", i);
	}
	printf("-------------------------------------\n");
}
int emptyroom(void){
	int i;
	int temp = -1;
	for(i=0;i<NROOMS;i++){
		if(roominfo[i] == 0){	
			temp = i;
			break;
		}
	}

	return temp+1;
}
int addguest(int num, char* name){
	int i;
	ssize_t nread;
	if(roominfo[num-1] != 0){
		printf("%d Room Not Free\n", num);
		return -1;
	}
	offset = 0;
	for(i=0;i<num;i++){
		if(roominfo[i] == 1)	offset += 11;
		else	offset += 1;
	}
	name[NAMELENGTH-1] = 10;
	if((infile = open("residents", O_RDONLY)) == -1){
		printf("OPEN ERROR\n");
		return -1;
	}
	if(lseek(infile, offset, SEEK_SET) == -1){
		printf("lseek ERROR\n");
		return -1;
	}
	if(write(infile, namebuf, strlen(name)) == -1)
	{
		printf("write ERROR\n");
		return -1;
	}

	return 0;
}
int main(void){
	int num = -1;
	int guestnum;
	char guestname[NAMELENGTH];
	while(num < 2){
		printhotel();
		printf("Select number[ 0 : Q2.3, 1 : Q.2.4 , 2 : EXIT ] >> ");
		scanf("%d", &num);
		if(num == 0){
			printf("\t * Question 2.9\n");
			printf("\t Free Room min : %d\n\n", emptyroom());
		}
		else if(num == 2){
			printf("\t * Question 2.10\n");
			printf("Inset Guset room number : ");
			scanf("%d", &guestnum);
			printf("Inset Guest Name [MAX 10] : ");
			scanf("%s", guestname);
			if(addguest(guestnum, guestname) == -1)
				printf("Guest Add ERROR\n");
		}
	}



	return 0;
}

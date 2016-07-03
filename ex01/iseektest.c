#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

	offset = roomno * NAMELENGTH;
	if(lseek(infile, offset, SEEK_SET) == -1)
		return NULL;

	if((nread = read (infile, namebuf, NAMELENGTH)) <= 0)
		return NULL;

	if(namebuf[0] == ' '){
		roominfo[roomno] = 0;
		close(infile);
		return "* FREE *";
	}
	else{
		roominfo[roomno] = 1;
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
	for(i=1; i<= NROOMS; i++){
		if(p = getoccupier(i-1))
			printf("\t Room %2d : %s\n", i, p);
		else
			printf("ERROR on room %d\n", i);
	}
	printf("-------------------------------------\n");
}
int minemptyroom(void){
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
int emptyroom(void){
	int i;
	if(minemptyroom() == 0){
		printf("\t     NOT FREE ROOM!\n\n");
		return -1;
	}
	else{
		printf("\t     *** FREE ROOM ***\n");
		for(i=0;i<NROOMS;i++)
			if(roominfo[i] == 0)	printf("\t\tROOM %2d\n", i+1);
		printf("\t     *****************\n");
	}
	return 0;
}

int addguest(int num,char* name){
	int i, m_text_size;
	ssize_t nread;
	char temp_name[10];
	if(roominfo[num-1] != 0){
		printf("\t ***** %d Room Not Free *****\n\n", num);
		return 0;
	}
	offset = (num -1) * NAMELENGTH;
	if((m_text_size = strlen(name)) >= 11)
		for(i=0;i<10;i++)	temp_name[i] = name[i];
	else{
		for(i=0;i<m_text_size-1;i++)	temp_name[i] = name[i];
		for(i=m_text_size-1;i<10;i++)	temp_name[i] = ' ';
	}	

	if((infile = open("residents", O_WRONLY)) == -1)
		return -1;
	
	if(lseek(infile, offset, SEEK_SET) == -1)
		return -1;
	if(write(infile, temp_name, 10) == -1)
		return -1;

	close(infile);
	return 0;
}
int main(void){
	int empty, num = 1;
	int guestnum;
	char guestname[100];
	while(1){
		printhotel();
		printf("Select number[ 1 : Q2.3, 2 : Q.2.4 , 3 : EXIT ] >> ");
		scanf("%d", &num);
		if(num == 1){
			printf("\n\t ***** Question 2.9 *****\n");
			if((empty = minemptyroom()) == 0)	printf("\t     Not Free Room!\n\n");
			else	printf("\t    Free Room min : %d\n\n", empty);
		}
		else if(num == 2){
			printf("\n\t ***** Question 2.10 *****\n");
			if(emptyroom() != -1){
				printf("\t  Inset Guset room number : ");
				scanf("%d", &guestnum);
				getchar();
				printf("\t  Inset Guest Name [MAX 10] : ");
				fgets(guestname, 100, stdin);
				if(addguest(guestnum, guestname) == -1)
					printf("\t ***** Guest Add ERROR ***** \n\n");
			}
		}
		else if(num == 3)	break;
		else	printf("\t Please try again....\n\n");
	}



	return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NAMELENGTH 11	// 예약명 길이 ('\0' 포함)
#define NROOMS 10	// 예약가능 방 갯수

char namebuf[NAMELENGTH];	// 예약자 저장 버퍼
char roominfo[NROOMS];	// 방 예약 확인 변수	0 : 예약가능 1: 예약불가능
int infile = -1;	// file 정보 변수
off_t offset = 0;	// offset 변수

/******* 호텔예약 확인 함수 *******/
char *getoccupier(int roomno){

	ssize_t nread;
	// file open
	if((infile = open("residents", O_RDONLY)) == -1)
		return NULL;
	//offset 설정
	offset = roomno * NAMELENGTH;
	// offset 이동 
	if(lseek(infile, offset, SEEK_SET) == -1)
		return NULL;
	// file read
	if((nread = read (infile, namebuf, NAMELENGTH)) <= 0)
		return NULL;
	// free room 확인
	if(namebuf[0] == ' '){
		roominfo[roomno] = 0;
		// file close
		close(infile);
		return "* FREE *";
	}
	else{
		roominfo[roomno] = 1;
		namebuf[nread -1] = '\0';	// 문자열의 끝
	}
	// file close
	close(infile);
	return namebuf;
}
/******* 방정보 출력 함수 *******/
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
/******* Question 2.9 *******/
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
/******* 빈방 출력 함수 *******/
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
/******* Question 2.10 *******/
int addguest(int num,char* name){
	int i, m_text_size;
	ssize_t nread;
	char temp_name[10];	// write 버퍼

	// 예약가능 체크
	if(roominfo[num-1] != 0){
		printf("\t ***** %d Room Not Free *****\n\n", num);
		return 0;
	}
	// offset 설정
	offset = (num -1) * NAMELENGTH;
	// 최대 길이 만큼 buffer 입력
	// 사용자 입력 시 글자수 10자리 초과 확인
	if((m_text_size = strlen(name)) >= 11)
		for(i=0;i<10;i++)	temp_name[i] = name[i];
	else{
		for(i=0;i<m_text_size-1;i++)	temp_name[i] = name[i];
		for(i=m_text_size-1;i<10;i++)	temp_name[i] = ' ';
	}	
	// file open
	if((infile = open("residents", O_WRONLY)) == -1)
		return -1;
	// offset 이동
	if(lseek(infile, offset, SEEK_SET) == -1)
		return -1;
	// file write
	if(write(infile, temp_name, 10) == -1)
		return -1;
	// file close
	close(infile);
	return 0;
}
int main(void){
	int empty, num = 1;	// 빈방 저장변수, 메뉴 선택 변수
	int guestnum;		// 예약 방번호 저장 변수
	char guestname[100];	// 예약자 저장 버퍼
	while(1){
		// 방정보 출력
		printhotel();
		// 메뉴 선택
		printf("Select number[ 1 : Q2.3, 2 : Q.2.4 , 3 : EXIT ] >> ");
		scanf("%d", &num);
		// Q2.9 실행
		if(num == 1){
			printf("\n\t ***** Question 2.9 *****\n");
			if((empty = minemptyroom()) == 0)	printf("\t     Not Free Room!\n\n");
			else	printf("\t    Free Room min : %d\n\n", empty);
		}
		// Q2.10 실행
		else if(num == 2){
			printf("\n\t ***** Question 2.10 *****\n");
			if(emptyroom() != -1){
				printf("\t  Inset Guset room number : ");
				scanf("%d", &guestnum);		//방 번호 입력
				getchar();			// 버퍼 비우기
				printf("\t  Inset Guest Name [MAX 10] : ");
				fgets(guestname, 100, stdin);	// 예약자 입력
				if(addguest(guestnum, guestname) == -1)
					printf("\t ***** Guest Add ERROR ***** \n\n");
			}
		}
		// 메뉴 나가기
		else if(num == 3)	break;
		else	printf("\t Please try again....\n\n");
	}


	// 프로그램 정상 종료
	return 0;
}

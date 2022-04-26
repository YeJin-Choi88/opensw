#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#pragma warnings(disable: 4996)
#define SIZE 100
int find(char* b_thing);
void borrow();
char tmp[100];

struct Student {
	char number[11];
	char name[100];
	char thing[100];
}STUDENT;

typedef struct _MYTIME
{
	int year;
	int month;
	int day;
}MYTIME;

MYTIME getTime()
{
	struct tm* t;
	time_t base = time(NULL);
	MYTIME ret;

	t = localtime(&base);

	ret.year = t->tm_year + 1900;
	ret.month = t->tm_mon + 1;
	ret.day = t->tm_mday;

	return ret;
}
void borrow() {
	struct Student* s1 = malloc(sizeof(struct Student));
	MYTIME b_date = getTime();
	FILE* fp = fopen("test.txt", "a+");
	if (s1 == NULL) {
		exit(1); //역참조 오류
	}
	while (1) {
		printf("     ============================ 대여 =========================\n\n\n\n\n");
		printf("\t\t     학번: ");
		gets_s(s1->number, 11);
		printf("\n\n\t\t     이름: ");
		gets_s(s1->name, 100);
		printf("\n\n\t\t     물건: ");
		gets_s(s1->thing, 100);
		if (find(s1->thing) == 1) {
			fprintf(fp, "%d/%d/%d\t%s  \t%s  \t%s  \t대여\n", b_date.year, b_date.month, b_date.day, s1->number, s1->name, s1->thing);
			fclose(fp);
			printf("\n\n\n날짜: %d/%d/%d\n학번: %s  \n이름: %s  \n물품: %s  \n\n", b_date.year, b_date.month, b_date.day, s1->number, s1->name, s1->thing);
			while (1) {
				printf("\n\n종료 1\n>>> ");
				int end = 0;
				scanf_s("%d%*c", &end);
				if (end == 1) {
					break;
				}
			}
			break;
		}
		else if (find(s1->thing) == 0) {
			system("cls");
			printf("\n\n물건이 없습니다 다시 입력해주세요.\n\n계속 0 종료 1 >>>");
			int end = 0;
			scanf_s("%d%*c", &end);
			if (end == 1) {
				break;
			}
			else if (end == 0) {
				system("cls");
				continue;
			}
		}
	}
	memset(&s1, 0, sizeof(s1));

}
void borrow_things_list() {
	FILE* fs;
	fs = fopen("list.txt", "r");
	printf("    ============================================================\n\n\n\n\n\n\n");
	while (feof(fs) == 0) {
		char str[100];
		fgets(str, 100, fs);
		printf("\t%s\n", str);
	}
	printf("\n\n\n\n\n\n\n    ===========================================================");
	while (1) {
		printf("\n\n\n\n종료 1\n>>> ");
		int end = 0;
		scanf_s("%d%*c", &end);
		if (end == 1) {
			break;
		}
	}
	fclose(fs);
}
int find(char* b_thing) {
	FILE* fp=fopen("list.txt", "r");
	int line = 0;
	char buffer[256];
	int flag = 0;
	//파일을 못 열었을 때
	if (fp == NULL) //읽기 모드로 해당 파일 열기 
	{
		fprintf(stderr, "파일 %s를 열 수 없습니다.\n", "list.txt"); //파일 관련 에러 출력
		exit(1);
	}

	//파일을 열었을 때, 해당 파일을 모두 읽을 때까지 실행 
	while (fgets(buffer, 256, fp)) //파일을 읽어서 256 길이만큼 버퍼에 담음
	{
		line++; //한 줄씩 읽음
		if (strstr(buffer, b_thing)) //버퍼가 word에 포함되어 있는지를 대비해 봄
		{
			flag = 1;
			fclose(fp);//파일 닫음 
			return flag;
		}
	}
	fclose(fp);//파일 닫음 
	if (flag == 0) {
		return flag;
	}
}

void return_thing() {
	struct Student* s1 = malloc(sizeof(struct Student));
	FILE* fp = fopen("test.txt", "r+t");
	FILE* fp2 = fopen("list.txt", "r+t");
	char buf[256];
	char* p, * p2, * p3;
	unsigned int lineNumber = 0;
	char num[256];
	char borr_thing[256];
	int find_pos=0;
	if (s1 == NULL) {
		exit(1);
	} //역참조 오류

	printf("\n\n학번: ");
	gets_s(num, 256);
	printf("\n대여 물품: ");
	gets_s(borr_thing, 256);
	if (fp == NULL) {
		exit(1);
	}
	if (fp2 == NULL) {
		exit(1);
	}

	while (fgets(buf, 256, fp)!=NULL) {
		p = strstr(buf, num);
		if (p!=NULL) {
			p2 = strstr(buf, borr_thing);
			if (p2 != NULL) {
				p3 = strstr(buf, "대여");
				if(p3 != NULL)
				find_pos = strlen(buf) - (p3 - buf) + 1;
				fseek(fp, (-1) * find_pos, SEEK_CUR);
				fwrite("반납", 4, 1, fp);
				fseek(fp, find_pos - 4, SEEK_CUR);
				printf("%s", buf);
			}

		}
	}
	fclose(fp2);
	fclose(fp);
	while (1) {
		printf("\n종료는 1\n>>> ");
		int end = 0;
		scanf_s("%d%*c", &end);
		if (end == 1) {
			break;
		}
	}
}

void borrow_list() {
	FILE* fp;
	int line = 0;
	char buffer[256];
	int flag = 0;
	//파일을 못 열었을 때
	if ((fp = fopen("test.txt", "r")) == NULL) //읽기 모드로 해당 파일 열기 
	{
		fprintf(stderr, "파일 %s를 열 수 없습니다.\n", "list.txt"); //파일 관련 에러 출력
		exit(1);
	}
	//파일을 열었을 때, 해당 파일을 모두 읽을 때까지 실행 
	printf("==============================대여 명단===============================\n");
	printf("날짜\t\t학번  \t\t이름  \t\t물품  \t\t확인\n\n");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		if (strstr(buffer, "대여")) //버퍼가 word에 포함되어 있는지를 대비해 봄
		{
			printf("%s", buffer);
		}
	}

	fclose(fp); //파일 닫음 
}

int main(void) {


	while (1) {
		system("cls");
		system("mode con cols=70 lines=30 | title 물품 대여 명단");
		printf("     *********************** 물품대여명단 ***********************\n");
		printf("\n\n\n\n\t\t\t   1. 대여\n\n\n\t\t\t   2. 반납\n\n\n\t\t\t   3. 물품 목록\n\n\n\t\t\t   4. 종료\n\n\n\n\n\n\n\n");
		int num = 0;
		printf(">>> ");
		scanf_s("%d%*c", &num);
		if (num == 1) {
			system("cls");
			borrow();
		}
		else if (num == 2) {
			system("cls");
			borrow_list();
			return_thing();

		}
		else if (num == 3) {
			system("cls");
			borrow_things_list();

		}
		else if (num == 4) {
			break;
		}
	}

	return 0;
}
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
		exit(1); //������ ����
	}
	while (1) {
		printf("     ============================ �뿩 =========================\n\n\n\n\n");
		printf("\t\t     �й�: ");
		gets_s(s1->number, 11);
		printf("\n\n\t\t     �̸�: ");
		gets_s(s1->name, 100);
		printf("\n\n\t\t     ����: ");
		gets_s(s1->thing, 100);
		if (find(s1->thing) == 1) {
			fprintf(fp, "%d/%d/%d\t%s  \t%s  \t%s  \t�뿩\n", b_date.year, b_date.month, b_date.day, s1->number, s1->name, s1->thing);
			fclose(fp);
			printf("\n\n\n��¥: %d/%d/%d\n�й�: %s  \n�̸�: %s  \n��ǰ: %s  \n\n", b_date.year, b_date.month, b_date.day, s1->number, s1->name, s1->thing);
			while (1) {
				printf("\n\n���� 1\n>>> ");
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
			printf("\n\n������ �����ϴ� �ٽ� �Է����ּ���.\n\n��� 0 ���� 1 >>>");
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
		printf("\n\n\n\n���� 1\n>>> ");
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
	//������ �� ������ ��
	if (fp == NULL) //�б� ���� �ش� ���� ���� 
	{
		fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", "list.txt"); //���� ���� ���� ���
		exit(1);
	}

	//������ ������ ��, �ش� ������ ��� ���� ������ ���� 
	while (fgets(buffer, 256, fp)) //������ �о 256 ���̸�ŭ ���ۿ� ����
	{
		line++; //�� �پ� ����
		if (strstr(buffer, b_thing)) //���۰� word�� ���ԵǾ� �ִ����� ����� ��
		{
			flag = 1;
			fclose(fp);//���� ���� 
			return flag;
		}
	}
	fclose(fp);//���� ���� 
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
	} //������ ����

	printf("\n\n�й�: ");
	gets_s(num, 256);
	printf("\n�뿩 ��ǰ: ");
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
				p3 = strstr(buf, "�뿩");
				if(p3 != NULL)
				find_pos = strlen(buf) - (p3 - buf) + 1;
				fseek(fp, (-1) * find_pos, SEEK_CUR);
				fwrite("�ݳ�", 4, 1, fp);
				fseek(fp, find_pos - 4, SEEK_CUR);
				printf("%s", buf);
			}

		}
	}
	fclose(fp2);
	fclose(fp);
	while (1) {
		printf("\n����� 1\n>>> ");
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
	//������ �� ������ ��
	if ((fp = fopen("test.txt", "r")) == NULL) //�б� ���� �ش� ���� ���� 
	{
		fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", "list.txt"); //���� ���� ���� ���
		exit(1);
	}
	//������ ������ ��, �ش� ������ ��� ���� ������ ���� 
	printf("==============================�뿩 ���===============================\n");
	printf("��¥\t\t�й�  \t\t�̸�  \t\t��ǰ  \t\tȮ��\n\n");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		if (strstr(buffer, "�뿩")) //���۰� word�� ���ԵǾ� �ִ����� ����� ��
		{
			printf("%s", buffer);
		}
	}

	fclose(fp); //���� ���� 
}

int main(void) {


	while (1) {
		system("cls");
		system("mode con cols=70 lines=30 | title ��ǰ �뿩 ���");
		printf("     *********************** ��ǰ�뿩��� ***********************\n");
		printf("\n\n\n\n\t\t\t   1. �뿩\n\n\n\t\t\t   2. �ݳ�\n\n\n\t\t\t   3. ��ǰ ���\n\n\n\t\t\t   4. ����\n\n\n\n\n\n\n\n");
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
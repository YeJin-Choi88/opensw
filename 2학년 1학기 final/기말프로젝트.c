#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h>

#define SPADE "♠"
#define CLUB "♣"
#define DIA "◆"
#define HEART "♥"

enum shape { spade = 0, heart, club, dia };

int Level;
int finish;

typedef struct Card {
	int shape;
	int num;
}Card;

typedef struct Player {
	int score;
	struct Card player_card[56];
}Player;

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

typedef char element[100];
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
} ListNode;
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	strcpy(node->data, data);
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1)
		head->link = node; // (2)
	}
	return head; // 변경된 헤드 포인터를 반환한다.
}
typedef struct Gamelog {
	int p1_score;
	int p2_score;
}Gamelog;

typedef struct Node {
	Gamelog gamelog;
	struct Node* pNext;
}Node;

Node* phead = NULL;
Node* ptail = NULL;

void AddNode(Gamelog _gamelog);
void Display_data();
void Display_gamelog(Gamelog* _Gam);
void gotoxy(int x, int y);
void shuffle(Card card_all[56]);
void hand_out1(Player* p1, Player* p2, Card card_all[56]);
void filldeck(Card card_all[56]);
void setcolor(int color, int bgcolor);
void first();
void explain();
void gotoxy(int x, int y);
void c_shape(int a, int b, int c);
void drow();
void play(Player* p1, Player* p2);
void print_c(Player a);
void gamelog_write(Player p1, Player p2);
void gamelog_read();
void Deletedata();

int main() {
	Level = 0;
	system("mode con cols=110 lines=40");
	explain();
	system("color E4");
	Card card_all[56];
	if (Level == 1) {

		Player p1, p2;
		p1.score = 0;
		p2.score = 0;
		filldeck(card_all);
		shuffle(card_all);
		for (int i = 0; i < 56; i++) {
			p1.player_card[i].num = 0;
			p2.player_card[i].num = 0;
			p1.player_card[i].shape = 5;	//초기화 5
			p2.player_card[i].shape = 5;
		}
		hand_out1(&p1, &p2, card_all);
		play(&p1, &p2);
		system("cls");
		if (p1.score > p2.score) {
			system("color E4");
			gotoxy(20, 45);
			printf("p1 %d점 p2 %d점으로 p1이 승리하였습니다!", p1.score, p2.score);
		}
		else if (p1.score < p2.score) {
			system("color E4");
			gotoxy(20, 45);
			printf("p1 %d점 p2 %d점으로 p2가 승리하였습니다!", p1.score, p2.score);
		}
		else if (p1.score == p2.score) {
			system("color E4");
			gotoxy(20, 45);
			printf("p1 %d점 p2 %d점으로 무승부입니다!\n\n", p1.score, p2.score);
		}
		gamelog_write(p1, p2);
	}
	else if (Level == 2) {
		gamelog_read();
		char ch;
		ch = getch();
		if (ch == '0') exit(0);
	}
	else if (Level == 3) {
		exit(0);
	}

}

// 카드 섞는 함수
void shuffle(Card card_all[56])
{
	srand(time(NULL));
	for (int i = 0; i < 56; i++)
	{
		int index = rand() % 56;
		Card temp;
		temp = card_all[index];
		card_all[index] = card_all[i];
		card_all[i] = temp;
	}
}

//카드 나눠주는 함수
void hand_out1(Player* p1, Player* p2, Card card_all[56]) {
	for (int i = 0; i < 56; i++)
	{
		if (i < 28)
			p1->player_card[i] = card_all[i];
		else
			p2->player_card[i - 28] = card_all[i];
	}
}

//카드 출력
void print_c(Player a) {
	enum Shape type;
	for (int i = 0; i < 28; i++) {
		type = a.player_card[i].shape;
		switch (type) {
		case spade:
			printf("|    %s  %d|\n", SPADE, a.player_card[i].num);
			break;
		case club:
			printf("|    %s  %d|\n", CLUB, a.player_card[i].num);
			break;
		case dia:
			printf("|    %s  %d|\n", DIA, a.player_card[i].num);
			break;
		case heart:
			printf("|    %s  %d|\n", HEART, a.player_card[i].num);
			break;
		}
	}
	printf("--------------------\n");
}

// 카드 채우는 함수
void filldeck(Card card_all[56])
{
	int i = 0;
	//모양 4개
	for (int j = 0; j < 4; j++) {
		//과일 1개- 5장, 과일 2개-3장, 과일3개-3장, 과일 4개-2장, 과일 5개-1장
		for (int k = 0; k < 14; k++)
		{
			if (k < 5) {
				card_all[i].num = 1;
				card_all[i].shape = j;
				i++;
			}
			else if (k >= 5 && k < 8) {
				card_all[i].num = 2;
				card_all[i].shape = j;
				i++;
			}
			else if (k >= 8 && k < 11) {
				card_all[i].num = 3;
				card_all[i].shape = j;
				i++;
			}
			else if (k >= 11 && k < 13) {
				card_all[i].num = 4;
				card_all[i].shape = j;
				i++;
			}
			else {
				card_all[i].num = 5;
				card_all[i].shape = j;
				i++;
			}
		}
	}
}

void setcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void first()
{
	int i;
	setcolor(15, 15);
	for (i = 1; i <= 11; i++)
	{
		gotoxy(91, i - 1);
		printf("■■■■■■■■■");
	}

	setcolor(15, 1);
	printf("\n");
	setcolor(15, 15);
	gotoxy(0, 28);
	printf("■■■■■■■■■");
	setcolor(15, 1);
	printf("  ■");
	setcolor(15, 15);
	for (i = 1; i <= 10; i++)
	{
		gotoxy(0, 28 + i);
		printf("■■■■■■■■■");
	}
	setcolor(15, 1);
}

void explain()
{
	char Ch;
	int i;

	system("cls");
	system("color E4");
	gotoxy(43, 5);
	printf("★☆★ HALLI GALLI ★☆★");
	gotoxy(30, 10);
	printf("게임설명 : 플레이어 1의 카드는 왼쪽에 생기고 ");
	gotoxy(15, 12);
	printf("플레이어 2의 카드는 오른쪽에 생깁니다. 자신의 턴일시 카드옆에 블록이 생깁니다.");
	gotoxy(13, 14);
	printf("자신의 턴일때마다 카드를 내며 만약 똑같은 모양의 카드의 숫자의 합이 5일 경우 종을 눌러");
	gotoxy(22, 16);
	printf("점수를 획득하고 카드를 다 뽑으면 게임을 종료하게 됩니다.");
	gotoxy(28, 18);
	printf("총 획득한 점수가 높은 플레이어가 이기는 게임입니다.");
	gotoxy(30, 20);
	printf("플레이어 1의 카드 내는 키는 Z, 종을 치는 키는 V 입니다.");
	gotoxy(30, 22);
	printf("플레이어 2의 카드 내는 키는 M, 종을 치는 키는 /입니다.");
	gotoxy(52, 27);
	printf("게임 메뉴");
	gotoxy(50, 29);
	printf("1. 게임 시작");
	gotoxy(50, 30);
	printf("\n");
	gotoxy(50, 31);
	printf("2. 게임 로그");
	gotoxy(50, 32);
	printf("\n");
	gotoxy(50, 33);
	printf("3. 게임 종료");
	for (i = 5; i <= 34; i++)
	{
		if ((i / 2) % 2 == 0) {
			gotoxy(4, i);
			printf("□");
			gotoxy(104, i);
			printf("□");
		}
		else {
			gotoxy(4, i);
			printf("■");
			gotoxy(104, i);
			printf("■");
		}

		i++;
	}
	gotoxy(4, 3);
	printf("■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □");
	gotoxy(4, 35);
	printf("■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □  ■  □");
	Ch = 'p';
	while (1)
	{
		Ch = getch();
		if (Ch == '1')
		{
			Level = 1;
			system("cls");
			break;
		}
		else if (Ch == '2')
		{
			Level = 2;
			system("cls");
			break;
		}
		else if (Ch == '3') {
			Level = 3;
			system("cls");
			break;
		}
		else
		{
			system("cls");
			gotoxy(45, 16);
			printf("다시 입력하세요");
			gotoxy(50, 19);
			printf("1. 게임 시작");
			gotoxy(50, 20);
			printf("\n");
			gotoxy(50, 21);
			printf("2. 게임 로그");
			gotoxy(50, 22);
			printf("\n");
			gotoxy(50, 23);
			printf("3. 게임 종료");
		}
	}

}

int check(Card a, Card b, int p) { //p1의 카드, p2의 카드, 플레이어
	int result = 0;
	if (a.num + b.num == 5) {
		system("cls");
		result = 1;
		setcolor(4, 14);
		gotoxy(48, 4);
		printf(" p%d 할리갈리!!", p);
		return result;
	}
	else {
		system("cls");
		result = 0;
		setcolor(4, 14);
		gotoxy(48, 4);
		printf("p%d 잘못눌렀습니다.", p);
		result;
	}

}

int i = 0;
int j = 0;

void play(Player* p1, Player* p2) {
	system("color E4");
	ListNode* head = NULL;
	head = insert_first(head, "p1");
	head = insert_first(head, "p2");
	ListNode* p = head;
	while (1) {
		char drow = 'p';

		if (p1->player_card[i].shape == 5) {
			break;
		}
		if (p2->player_card[j].shape == 5) {
			break;
		}
		setcolor(4, 14);
		gotoxy(48, 2);
		printf("현재 차례=%s", p->data);
		p = p->link;
		drow = getch();
		if (drow == 'z') {
			++i;
			c_shape(p1->player_card[i - 1].shape, p1->player_card[i - 1].num, 1);
		}
		else if (drow == 'v') {
			if (check(p1->player_card[i - 1], p2->player_card[j - 1], 1) == 1) {
				p1->score += 1;
			}
			else {
				p1->score -= 1;
			}
		}
		else if (drow == 'm') {
			++j;
			c_shape(p2->player_card[j - 1].shape, p2->player_card[j - 1].num, 2);
		}
		else if (drow == '/') {
			if (check(p1->player_card[i - 1], p2->player_card[j - 1], 2) == 1) {
				p2->score += 1;
			}
			else {
				p2->score -= 1;
			}
		}
	}
}

void gamelog_write(Player p1, Player p2) {
	system("color E4");
	FILE* fp = fopen("gamelog.txt", "a+");
	fprintf(fp, "%d  %d", p1.score, p2.score);
	fclose(fp);
};
void gamelog_read() {
	FILE* fp = fopen("gamelog.txt", "r");
	Gamelog gamelog;

	while (!feof(fp)) {

		fscanf(fp, "%d\t", &gamelog.p1_score);
		fscanf(fp, "%d\t\n", &gamelog.p2_score);
		AddNode(gamelog);
	}
	fclose(fp);

	Display_data();
	Deletedata();
}
void Display_data() {
	Node* pCur = phead;
	if (phead == NULL) {
		printf("데이터가 없음\n");
		return;
	}
	while (pCur != NULL) {
		Display_gamelog(&pCur->gamelog);
		pCur = pCur->pNext;
	}
}
void Display_gamelog(Gamelog* _Gam) {
	printf("p1 점수: %d\t", _Gam->p1_score);
	printf("p2 점수: %d\n", _Gam->p2_score);

}
void Deletedata() {
	Node* pCur = phead;
	Node* pDel = NULL;
	if (phead == NULL) return;
	while (pCur != NULL) {
		pDel = pCur;
		pCur = pCur->pNext;
		free(pDel);
	}
	phead = ptail = NULL;
}
void AddNode(Gamelog _gamelog) {
	Node* Newnode = (Node*)malloc(sizeof(Node));
	Newnode->gamelog = _gamelog;
	Newnode->pNext = NULL;
	if (phead == NULL) phead = Newnode;
	else ptail->pNext = Newnode;
	ptail = Newnode;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void c_shape(int a, int b, int c)
{
	int temp = 0;
	if (c == 1)
	{
		temp = 32;
	}
	else if (c == 2)
	{
		temp = 56;
	}

	setcolor(0, 15);
	if (a == 0)
	{
		setcolor(0, 15);
	}
	else if (a == 1)
	{
		setcolor(4, 15);
	}
	else if (a == 2)
	{
		setcolor(0, 15);
	}
	else if (a == 3)
	{
		setcolor(4, 15);
	}
	gotoxy(temp, 14);
	printf("                %d ", b);
	gotoxy(temp, 24);
	printf(" %d                ", b);

	if (a == 0)
	{
		if (b == 1)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♠ ");
			gotoxy(temp, 16);
			printf("                  ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♠        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("                  ");
			gotoxy(temp, 23);
			printf(" ♠               ");
			setcolor(15, 1);
		}
		else if (b == 2)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♠ ");
			gotoxy(temp, 16);
			printf("        ♠        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♠        ");
			gotoxy(temp, 23);
			printf(" ♠               ");
			setcolor(15, 1);
		}
		else if (b == 3)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♠ ");
			gotoxy(temp, 16);
			printf("        ♠        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♠        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♠        ");
			gotoxy(temp, 23);
			printf(" ♠               ");
			setcolor(15, 1);
		}
		else if (b == 4)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♠ ");
			gotoxy(temp, 16);
			printf("    ♠      ♠    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♠      ♠    ");
			gotoxy(temp, 23);
			printf(" ♠               ");
			setcolor(15, 1);
		}
		else if (b == 5)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♠ ");
			gotoxy(temp, 16);
			printf("    ♠      ♠    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♠        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♠      ♠    ");
			gotoxy(temp, 23);
			printf(" ♠               ");
			setcolor(15, 1);
		}
	}
	else if (a == 1)
	{
		if (b == 1)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ♥ ");
			gotoxy(temp, 16);
			printf("                  ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♥        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("                  ");
			gotoxy(temp, 23);
			printf(" ♥               ");
			setcolor(15, 1);
		}
		else if (b == 2)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ♥ ");
			gotoxy(temp, 16);
			printf("        ♥        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♥        ");
			gotoxy(temp, 23);
			printf(" ♥               ");
			setcolor(15, 1);
		}
		else if (b == 3)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ♥ ");
			gotoxy(temp, 16);
			printf("        ♥        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♥        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♥        ");
			gotoxy(temp, 23);
			printf(" ♥               ");
			setcolor(15, 1);
		}
		else if (b == 4)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ♥ ");
			gotoxy(temp, 16);
			printf("    ♥      ♥    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♥      ♥    ");
			gotoxy(temp, 23);
			printf(" ♥               ");
			setcolor(15, 1);
		}
		else if (b == 5)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ♥ ");
			gotoxy(temp, 16);
			printf("    ♥      ♥    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♥        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♥      ♥    ");
			gotoxy(temp, 23);
			printf(" ♥               ");
			setcolor(15, 1);
		}
	}
	else if (a == 2)
	{
		if (b == 1)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♣ ");
			gotoxy(temp, 16);
			printf("                  ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♣        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("                  ");
			gotoxy(temp, 23);
			printf(" ♣               ");
			setcolor(15, 1);
		}
		else if (b == 2)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♣ ");
			gotoxy(temp, 16);
			printf("        ♣        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♣        ");
			gotoxy(temp, 23);
			printf(" ♣               ");
			setcolor(15, 1);
		}
		else if (b == 3)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♣ ");
			gotoxy(temp, 16);
			printf("        ♣        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♣        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ♣        ");
			gotoxy(temp, 23);
			printf(" ♣               ");
			setcolor(15, 1);
		}
		else if (b == 4)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♣ ");
			gotoxy(temp, 16);
			printf("    ♣      ♣    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♣      ♣    ");
			gotoxy(temp, 23);
			printf(" ♣               ");
			setcolor(15, 1);
		}
		else if (b == 5)
		{
			setcolor(0, 15);
			gotoxy(temp, 15);
			printf("               ♣ ");
			gotoxy(temp, 16);
			printf("    ♣      ♣    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ♣        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ♣      ♣    ");
			gotoxy(temp, 23);
			printf(" ♣               ");
			setcolor(15, 1);
		}
	}

	else if (a == 3)
	{
		if (b == 1)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ◆ ");
			gotoxy(temp, 16);
			printf("                  ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ◆        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("                  ");
			gotoxy(temp, 23);
			printf(" ◆               ");
			setcolor(15, 1);
		}
		else if (b == 2)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ◆ ");
			gotoxy(temp, 16);
			printf("        ◆        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ◆        ");
			gotoxy(temp, 23);
			printf(" ◆               ");
			setcolor(15, 1);
		}
		else if (b == 3)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ◆ ");
			gotoxy(temp, 16);
			printf("        ◆        ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ◆        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("        ◆        ");
			gotoxy(temp, 23);
			printf(" ◆               ");
			setcolor(15, 1);
		}
		else if (b == 4)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ◆ ");
			gotoxy(temp, 16);
			printf("    ◆      ◆    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("                  ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ◆      ◆    ");
			gotoxy(temp, 23);
			printf(" ◆               ");
			setcolor(15, 1);
		}
		else if (b == 5)
		{
			setcolor(4, 15);
			gotoxy(temp, 15);
			printf("               ◆ ");
			gotoxy(temp, 16);
			printf("    ◆      ◆    ");
			gotoxy(temp, 17);
			printf("                  ");
			gotoxy(temp, 18);
			printf("                  ");
			gotoxy(temp, 19);
			printf("        ◆        ");
			gotoxy(temp, 20);
			printf("                  ");
			gotoxy(temp, 21);
			printf("                  ");
			gotoxy(temp, 22);
			printf("    ◆      ◆    ");
			gotoxy(temp, 23);
			printf(" ◆               ");
			setcolor(15, 1);
		}
	}
}


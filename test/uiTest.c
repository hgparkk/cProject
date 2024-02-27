#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

//마우스 입력 관련 변수
typedef struct mouse {
	HANDLE hIn, hOut;
	DWORD dwNOER;
	INPUT_RECORD rec;
}Mouse;

typedef struct review
{
	char ID[20];
	char code[28];
	char repu[4];
	char review[];
}Review;

void mouseMove(int* x, int* y)
{
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	while (TRUE)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		*x = mmval.rec.Event.MouseEvent.dwMousePosition.X;
		*y = mmval.rec.Event.MouseEvent.dwMousePosition.Y;
		return;
	}
}

//화면 크기 정하기
void setConsole()
{
	system("Console");
	system("mode con:cols=60 lines=30");

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

//콘솔창에서 좌표로 이동하기
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//좌표에 문자열 출력
void text(int x, int y, char text[])
{
	gotoxy(x, y);
	printf("%s", text);
}

//네모 박스 만들기
void drawBox(int x, int y, int width, int height)
{
	gotoxy(x, y);
	printf("┌");
	for (int i = 0; i < width; i++)
	{
		printf("─");
	}
	printf("┐");

	for (int i = 0; i < height; i++) {
		gotoxy(x, y + 1 + i);
		printf("│");
		for (int j = 0; j < width; j++) {
			printf(" ");
		}
		printf("│");
	}


	gotoxy(x, y + height + 1);
	printf("└");
	for (int i = 0; i < width; i++)
	{
		printf("─");
	}
	printf("┘");
}

//콘솔창 화면 지우기
void clearConsole()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw);
}

// 색 원상복구
void colorSetRestore()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7);
}

Review* reviewFileRead(int* _size)
{
	Review temp;
	Review* temps;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s", temp.ID, temp.code, temp.repu, temp.review);
			size++;
		}
		temps = (Review*)malloc(sizeof(Review) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s", temps[size].ID, temps[size].code, temps[size].repu, temps[size].review);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//해당 좌표에 문자열 입력
void textInput(int x, int y, char* text, bool pw)
{
	char temp[60] = "\0";
	int num = 0;
	gotoxy(x, y);
	strcat(temp, text);
	while (temp[num] != '\0')
	{
		if (pw == TRUE)
		{
			printf("*");
		}
		else
		{
			putchar(temp[num]);
		}
		num++;
	}
	while (TRUE)
	{
		if (_kbhit())
		{
			temp[num] = _getch();
			if (temp[num] == 13)
			{
				temp[num] = '\0';
				break;
			}
			else if (temp[num] == '\b' && num != 0)
			{
				printf("\b \b");
				temp[num] = '\0';
				num--;
			}
			else
			{
				if (temp[num] == '\b' && num == 0)
					continue;
				else
				{
					if (pw == TRUE)
						printf("*");
					else
						putchar(temp[num]);
				}
				num++;
			}
		}
	}
	strcpy(text, temp);
}

int main()
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	char menuName[40] = "\0";
	char code[28] = "\0";
	int price = 0;

	// 메뉴등록 창
	drawBox(17, 9, 30, 1);

	drawBox(17, 14, 30, 1);

	drawBox(10, 23, 11, 1);
	text(12, 24, "메뉴등록");
	drawBox(37, 23, 11, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		colorSetRestore();
		gotoxy(7, 4);
		printf("%d", price);
		text(7, 10, "메뉴이름");
		text(7, 15, "가격");

		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 52))
		{
			//메뉴이름 입력
			if ((9 <= y) && (y <= 11))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 4, menuName, FALSE);
					}
				}
			}
			//가격 입력
			if ((14 <= y) && (y <= 16))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						char tempPrice[20];
						itoa(price,tempPrice,10);
						textInput(19, 15, tempPrice, FALSE);
						price = atoi(tempPrice);
					}
				}
			}
		}
	}
}
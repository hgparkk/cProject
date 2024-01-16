#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <conio.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

//마우스 입력 관련 변수
typedef struct mouse {
	HANDLE hIn, hOut;
	DWORD dwNOER;
	INPUT_RECORD rec;
}Mouse;

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

//마우스 이동 이벤트
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

// 글자 색을 바꾸는 함수
void colorSetSelect()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 112);
}

// 색 원상복구
void colorSetRestore()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7);
}

//해당 좌표에 문자열 입력
void textInput(int x, int y, char* text, bool pw)
{
	char temp[20] = "\0";
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

//해당 좌표에 문자열 입력(가변길이)
void textInput2(int x, int y, char* text)
{
	char* temp = (char*)calloc(200, sizeof(char));
	int num = 0;
	gotoxy(x, y);
	strcat(temp, text);
	while (temp[num] != '\0')
	{
		putchar(temp[num]);
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
					putchar(temp[num]);
				}
				num++;
			}
		}
	}
	strcpy(text, temp);
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
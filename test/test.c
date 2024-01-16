#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

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
int main() {
	drawBox(10, 10, 30, 10);
	text(14, 12, "가게 등록이 완료되었습니다.");
	drawBox(19, 18, 10, 1);
	text(24, 19, "확인");
}
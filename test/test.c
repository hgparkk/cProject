#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

//�ܼ�â���� ��ǥ�� �̵��ϱ�
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//��ǥ�� ���ڿ� ���
void text(int x, int y, char text[])
{
	gotoxy(x, y);
	printf("%s", text);
}

//�׸� �ڽ� �����
void drawBox(int x, int y, int width, int height)
{
	gotoxy(x, y);
	printf("��");
	for (int i = 0; i < width; i++)
	{
		printf("��");
	}
	printf("��");

	for (int i = 0; i < height; i++) {
		gotoxy(x, y + 1 + i);
		printf("��");
		for (int j = 0; j < width; j++) {
			printf(" ");
		}
		printf("��");
	}


	gotoxy(x, y + height + 1);
	printf("��");
	for (int i = 0; i < width; i++)
	{
		printf("��");
	}
	printf("��");
}
int main() {
	drawBox(10, 10, 30, 10);
	text(14, 12, "���� ����� �Ϸ�Ǿ����ϴ�.");
	drawBox(19, 18, 10, 1);
	text(24, 19, "Ȯ��");
}
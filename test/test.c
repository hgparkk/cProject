#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

//���콺 �Է� ���� ����
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

//ȭ�� ũ�� ���ϱ�
void setConsole()
{
	system("Console");
	system("mode con:cols=60 lines=30");

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

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

//�ܼ�â ȭ�� �����
void clearConsole()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw);
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
		fprintf(stderr, "����� ���� ������ �� �� �����ϴ�.\n");
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

int main()
{
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;
	int size = 0;

	drawBox(10, 2, 40, 3);
	drawBox(10, 7, 40, 3);
	drawBox(10, 12, 40, 3);

	text(3, 19, "    �� = �������� ������ ȥ�� ���ϰ� �Ļ��� �� �ִ� ����");
	text(3, 20, "  �ڡ� = ���ο��� ��õ�� �� ���������� ȣ��ȣ���� ����");
	text(3, 21, "�ڡڡ� = �� ���� �Ļ縦 ���� �ָ����� ������ �� �ִ� ����");

	drawBox(10, 23, 11, 1);
	text(12, 24, "���������");
	drawBox(24, 23, 10, 1);
	text(27, 24, "��������");
	drawBox(37, 23, 13, 1);
	text(39, 24, "ȸ����������");

	// ���콺 �̵��� Ŭ���� ó��
	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((2 <= y) && (y <= 16))
		{
			if ((9 <= x) && (x <= 51))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwEventFlags & MOUSE_WHEELED)
					{
						// ��ũ�� ���� Ȯ��
						short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

						if (wheelDelta > 0) {
							// ���콺 ���� ���� ��ũ�ѵ�
							text(12, 5, "Mouse wheel scrolled up");
						}
						else if (wheelDelta < 0) {
							// ���콺 ���� �Ʒ��� ��ũ�ѵ�
							text(12, 5, "Mouse wheel scrolled down");
						}
					}
				}
			}
		}
	}
}
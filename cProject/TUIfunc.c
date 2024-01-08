#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct mouse{
	HANDLE hIn, hOut;
	DWORD dwNOER;
	INPUT_RECORD rec;
}Mouse;

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

//���콺 �̵� �̺�Ʈ
void mouseMove(int* x, int* y)
{
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		*x = mmval.rec.Event.MouseEvent.dwMousePosition.X;
		*y = mmval.rec.Event.MouseEvent.dwMousePosition.Y;
		return;
	}
}

// ���콺 Ŀ���� ��ư ���� �ø��� ���� �ٲٴ� �Լ�
void colorSetSelect()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 112);
}

// �� ���󺹱�
void colorSetRestore()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7);
}


//�ش� ��ǥ�� ���ڿ� �Է�
void textInput(int x, int y, char* text, int pw)
{
	char temp[20] = "\0";
	int num = 0;
	gotoxy(x, y);
	strcat(temp, text);
	while (temp[num]!='\0')
	{
		if (pw == 1)
		{
			printf("*");
		}
		else
		{
			_putch(temp[num]);
		}
		num++;
	}
	while (1)
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
					if (pw == 1)
						_putch('*');
					else
						_putch(temp[num]);
				}
				num++;
			}
		}
	}
	strcpy(text, temp);
}

//��ǥ�� ���ڿ� �Է�
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
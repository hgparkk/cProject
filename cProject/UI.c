#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "TUIfunc.h"
#include "Global.h"
#define _CRT_SECURE_NO_WARNINGS

void title();
void registers();

// �α���â ȭ��
void title()
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	char ID[20] = "\0";
	char PW[20] = "\0";

	// â ũ�� ���ϱ�
	setConsole();

	// �α��� â
	text(7, 11, "���̵�");
	drawBox(17, 10, 20, 1);
	text(7, 17, "��й�ȣ");
	drawBox(17, 16, 20, 1);

	drawBox(41, 11, 10, 5);
	text(44, 14, "�α���");
	drawBox(11, 23, 10, 1);
	text(16, 24, "����");
	drawBox(24, 23, 10, 1);
	text(27, 24, "ID ã��");
	drawBox(37, 23, 10, 1);
	text(39, 24, "PW �ʱ�ȭ");

	// ���콺 �̵��� Ŭ���� ó��
	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 37))
		{
			//ID �Է�
			if ((10 <= y) && (y <= 12))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 11, ID, 0);
					}
				}
			}
			//PW �Է�
			if ((17 <= y) && (y <= 18))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 17, PW, 1);
					}
				}
			}
		}
		//�α��� ��ư
		if ((43 <= x) && (x <= 51))
		{
			if ((11 <= y) && (y <= 16))
			{
				colorSetSelect();
				text(44, 14, "�α���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						text(0, 1, "�α��� ��ư �Դϴ�");
					}
				}
			}
			else
			{
				colorSetRestore();
				text(44, 14, "�α���");
			}
		}
		else
		{
			colorSetRestore();
			text(44, 14, "�α���");
		}
		if ((22 <= y) && (y <= 24))
		{
			//�����ϱ� ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "����");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						clearConsole();
						colorSetRestore();
						text(16, 24, "    ");
						registers();
					}
				}
			}
			else
			{
				colorSetRestore();
				text(16, 24, "����");
			}
			//ID ã�� ��ư
			if ((25 <= x) && (x <= 35))
			{
				colorSetSelect();
				text(27, 24, "ID ã��");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						text(0, 1, "ID ã���Դϴ�");
					}
				}
			}
			else
			{
				colorSetRestore();
				text(27, 24, "ID ã��");
			}
			//PW �ʱ�ȭ ��ư
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "PW �ʱ�ȭ");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						text(0, 1, "PW �ʱ�ȭ�Դϴ�");
					}
				}
			}
			else
			{
				colorSetRestore();
				text(39, 24, "PW �ʱ�ȭ");
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "����");
			text(27, 24, "ID ã��");
			text(39, 24, "PW �ʱ�ȭ");
		}
	}
}

//���� ȭ��
void registers()
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y, owner;

	char ID[20] = "\0";
	char PW[20] = "\0";

	// ���� â
	text(7, 11, "���̵�");
	drawBox(17, 10, 25, 1);
	text(7, 14, "��й�ȣ");
	drawBox(17, 13, 25, 1);
	text(7, 17, "���� ���� �̽ʴϱ�?");
	text(35, 17, "��");
	text(38, 17, "�ƴϿ�");

	drawBox(11, 23, 10, 1);
	text(16, 24, "����");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while(1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			if ((10 <= y) && (y <= 12))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 11, ID, 0);
					}
				}
			}
			if ((13 <= y) && (y <= 15))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 14, PW, 1);
					}
				}
			}
		}
		if ((17 <= y) && (y <= 18))
		{
			if ((35 <= x) && (x <= 36))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						text(38, 17, "�ƴϿ�");
						colorSetSelect();
						text(35, 17, "��");
						owner = 1;
					}
				}
			}
			if ((38 <= x) && (x <= 39))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						text(35, 17, "��");
						colorSetSelect();
						text(38, 17, "�ƴϿ�");
						owner = 0;
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//���� ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "����");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						text(16, 26, "�����ϱ� ��ư�Դϴ�.");
					}
				}
			}
			else
			{
				colorSetRestore();
				text(16, 24, "����");
			}
			//���ư��� ��ư
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "���ư���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						clearConsole();
						colorSetRestore();
						text(39, 24, "       ");
						title();
					}
				}
			}
			else
			{
				colorSetRestore();
				text(39, 24, "���ư���");
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "����");
			text(39, 24, "���ư���");
		}
	}
}
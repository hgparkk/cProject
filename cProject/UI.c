#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "TUIfunc.h"
#include "func.h"
#include "file.h"
#define _CRT_SECURE_NO_WARNINGS

void title();
void newUser();
void newUserInput(char* ID, char* PW, char* userName, char* birth, int owner);
void login(char* ID, char* PW);
void idFind();
void idFindCheck(char* userName, char* birth);
void pwReset();
void pwResetCheck(char* userName, char* ID, char* birth);
void newRest(char* _ID, bool regist);
void newRestInput(char* ID, char* restName, char* loc, char* bHours, bool regist);

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
						textInput(19, 11, ID, FALSE);
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
						textInput(19, 17, PW, TRUE);
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
						colorSetRestore();
						login(ID, PW);
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
						newUser();
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
						clearConsole();
						colorSetRestore();
						text(25, 24, "         ");
						idFind();
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
						clearConsole();
						colorSetRestore();
						text(39, 24, "         ");
						pwReset();
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
void newUser()
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;
	int owner = 0;

	char userName[10] = "\0";
	char ID[20] = "\0";
	char PW[20] = "\0";
	char birth[7] = "\0";

	// ���� â
	text(7, 8, "�̸�");
	drawBox(17, 7, 25, 1);
	text(7, 11, "���̵�");
	drawBox(17, 10, 25, 1);
	text(7, 14, "��й�ȣ");
	drawBox(17, 13, 25, 1);
	text(7, 17, "�������");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);
	text(7, 20, "���� ���� �̽ʴϱ�?");
	text(7, 21, "(���� ������ ���Խ� ���� �ϳ� �ʼ� ���)");
	text(35, 20, "��");
	colorSetSelect();
	text(38, 20, "�ƴϿ�");
	colorSetRestore();

	drawBox(11, 23, 10, 1);
	text(16, 24, "����");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//�̸� �Է�
			if ((7 <= y) && (y <= 9))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 8, userName, FALSE);
					}
				}
			}
			//ID�Է�
			if ((10 <= y) && (y <= 12))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 11, ID, FALSE);
					}
				}
			}
			//PW�Է�
			if ((13 <= y) && (y <= 15))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 14, PW, TRUE);
					}
				}
			}
			//��������Է�
			if ((16 <= y) && (y <= 18))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 17, birth, FALSE);
					}
				}
			}
		}
		//���� ���� ���� ����
		if ((20 <= y) && (y <= 21))
		{
			if ((35 <= x) && (x <= 36))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						text(38, 20, "�ƴϿ�");
						colorSetSelect();
						text(35, 20, "��");
						owner = 1;
					}
				}
			}
			if ((38 <= x) && (x <= 42))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						text(35, 20, "��");
						colorSetSelect();
						text(38, 20, "�ƴϿ�");
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
						colorSetRestore();
						newUserInput(ID, PW, userName, birth, owner);
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
						text(38, 20, "       ");
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

//���� ���� ���Ͽ� �Է�
void newUserInput(char* ID, char* PW, char* userName, char* birth, int owner)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;

	User resUser;
	strcpy(resUser.ID, ID);
	strcpy(resUser.PW, PW);
	strcpy(resUser.userName, userName);
	strcpy(resUser.birth, birth);
	resUser.owner = owner;
	if (isValidID(ID))
	{
		if (isValidID2(ID))
		{
			if (isValidPW(PW))
			{
				if (isValidName1(userName) || isValidName2(userName))
				{
					if (isValidBirth(birth))
					{
						userInfoFileWrite(resUser);
						if (owner == 1)
						{
							clearConsole();
							colorSetRestore();
							text(35, 20, "          ");
							newRest(resUser.ID, TRUE);
						}
						else
						{
							drawBox(15, 10, 25, 10);
							text(18, 12, "������ �Ϸ�Ǿ����ϴ�.");
							drawBox(22, 18, 10, 1);
							text(27, 19, "Ȯ��");
							while (1)
							{
								ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
								mouseMove(&x, &y);
								if ((22 <= x) && (x <= 32))
								{
									if ((17 <= y) && (y <= 19))
									{
										colorSetSelect();
										text(27, 19, "Ȯ��");
										if (mmval.rec.EventType == MOUSE_EVENT)
										{
											if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
											{
												clearConsole();
												colorSetRestore();
												text(27, 19, "       ");
												text(35, 20, "          ");
												title();
											}
										}
									}
									else
									{
										colorSetRestore();
										text(27, 19, "Ȯ��");
									}
								}
								else
								{
									colorSetRestore();
									text(27, 19, "Ȯ��");
								}
							}
						}
					}
					else
					{
						text(20, 27, "                                      ");
						text(20, 27, "��ȿ���� ���� ������� �Դϴ�.");
					}
				}
				else
				{
					text(20, 27, "                                      ");
					text(20, 27, "��ȿ���� ���� �̸� �Դϴ�.");
				}
			}
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "��ȿ���� ���� PW �Դϴ�.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "�ߺ��Ǵ� ID �Դϴ�.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "��ȿ���� ���� ID �Դϴ�.");
	}
}

//�α��� ��ư
void login(char* ID, char* PW)
{
	User* temps;
	int size;
	int suc = 0;
	temps = userInfoFileRead(&size);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].ID, ID) == 0)
		{
			if (strcmp(temps[i].PW, PW) == 0)
			{
				suc = 1;
			}
			else
			{
				suc = 2;
			}
		}
	}
	if (suc == 2)
	{
		text(20, 27, "��й�ȣ�� �ٸ��ϴ�");
	}
	else if (suc == 1)
	{
		text(20, 27, "�α��� ����");
	}
	else
	{
		text(20, 27, "��ġ�ϴ� ID�� �����ϴ�.");
	}
	free(temps);
}

//IDã�� ȭ��
void idFind()
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;
	char userName[10] = "\0";
	char birth[7] = "\0";

	// IDã�� â
	text(7, 8, "�̸�");
	drawBox(17, 7, 25, 1);
	text(7, 17, "�������");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "ã��");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//�̸� �Է�
			if ((7 <= y) && (y <= 9))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 8, userName, FALSE);
					}
				}
			}
			//��������Է�
			if ((16 <= y) && (y <= 18))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 17, birth, FALSE);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//ã�� ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "ã��");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						idFindCheck(userName, birth);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(16, 24, "ã��");
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
			text(16, 24, "ã��");
			text(39, 24, "���ư���");
		}
	}
}

//IDã���� Ȯ�ι�ư
void idFindCheck(char* userName, char* birth)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;
	int userNum;

	User* temps;
	int size;
	int suc = 0;
	temps = userInfoFileRead(&size);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].userName, userName) == 0)
		{
			if (strcmp(temps[i].birth, birth) == 0)
			{
				suc = 1;
				userNum = i;
			}
		}
	}

	if (suc == 1)
	{
		text(20, 27, "                                      ");
		drawBox(15, 10, 25, 10);
		gotoxy(18, 12);
		printf("ID�� %s �Դϴ�.", temps[userNum].ID);
		drawBox(22, 18, 10, 1);
		text(27, 19, "Ȯ��");
		while (1)
		{
			ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
			mouseMove(&x, &y);
			if ((22 <= x) && (x <= 32))
			{
				if ((17 <= y) && (y <= 19))
				{
					colorSetSelect();
					text(27, 19, "Ȯ��");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							clearConsole();
							colorSetRestore();
							text(27, 19, "       ");
							text(35, 20, "          ");
							title();
						}
					}
					else
					{
						colorSetRestore();
						text(27, 19, "Ȯ��");
					}
				}
				else
				{
					colorSetRestore();
					text(27, 19, "Ȯ��");
				}
			}
		}
	}
	else
	{
		text(20, 27, "��ġ�ϴ� ������ �����ϴ�");
	}
	free(temps);
}

//PW�ʱ�ȭ ȭ��
void pwReset()
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;
	char ID[20] = "\0";
	char userName[10] = "\0";
	char birth[7] = "\0";

	// ���� â
	text(7, 11, "�̸�");
	drawBox(17, 10, 25, 1);
	text(7, 14, "���̵�");
	drawBox(17, 13, 25, 1);
	text(7, 17, "�������");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(15, 24, "�ʱ�ȭ");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//�̸� �Է�
			if ((10 <= y) && (y <= 12))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 11, userName, FALSE);
					}
				}
			}
			//���̵� �Է�
			if ((13 <= y) && (y <= 15))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 14, ID, FALSE);
					}
				}
			}
			//��������Է�
			if ((16 <= y) && (y <= 18))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 17, birth, FALSE);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//�ʱ�ȭ ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(15, 24, "�ʱ�ȭ");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						pwResetCheck(userName, ID, birth);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(15, 24, "�ʱ�ȭ");
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
			text(15, 24, "�ʱ�ȭ");
			text(39, 24, "���ư���");
		}
	}
}

//PW�ʱ�ȭ â�� �ʱ�ȭ ��ư
void pwResetCheck(char* userName, char* ID, char* birth)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;

	int button = 0;
	int userNum;
	char rePW[20] = "\0";

	User* temps;
	int size;
	int suc = 0;
	temps = userInfoFileRead(&size);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].userName, userName) == 0)
		{
			if (strcmp(temps[i].ID, ID) == 0)
			{
				if (strcmp(temps[i].birth, birth) == 0)
				{
					suc = 1;
					userNum = i;
				}
			}
		}
	}

	if (suc == 1)
	{
		text(20, 27, "                                      ");
		drawBox(5, 10, 48, 10);
		text(10, 12, "�� PW �Է�");
		drawBox(23, 11, 25, 1);
		drawBox(22, 18, 10, 1);
		text(27, 19, "Ȯ��");
		while (1)
		{
			ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
			mouseMove(&x, &y);
			if ((23 <= x) && (x <= 48))
			{
				if ((10 <= y) && (y <= 12))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							textInput(25, 12, rePW, TRUE);
						}
					}
				}
			}
			if ((22 <= x) && (x <= 32))
			{
				if ((17 <= y) && (y <= 19))
				{
					colorSetSelect();
					text(27, 19, "Ȯ��");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if (button == 0)
							{
								if (isValidPW(rePW))
								{
									colorSetRestore();
									drawBox(5, 10, 48, 10);
									text(19, 12, "PW�� �ʱ�ȭ�Ǿ����ϴ�.");
									strcpy(temps[userNum].PW, rePW);
									userInfoFileReWrite(temps, size);
									button = 1;
									drawBox(22, 18, 10, 1);
									text(27, 19, "Ȯ��");
								}
								else
								{
									colorSetRestore();
									text(19, 17, "��ȿ���� ���� PW�Դϴ�.");
								}
							}
							else
							{
								clearConsole();
								colorSetRestore();
								text(27, 19, "       ");
								text(35, 20, "          ");
								title();
							}
						}
					}
					else
					{
						colorSetRestore();
						text(27, 19, "Ȯ��");
					}
				}
				else
				{
					colorSetRestore();
					text(27, 19, "Ȯ��");
				}
			}
		}
	}
	else
	{
		text(20, 27, "��ġ�ϴ� ������ �����ϴ�");
	}
	free(temps);
}

//���� ���
void newRest(char* _ID, bool regist)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	bool tempregist = regist;

	char ID[20] = "\0";
	strcpy(ID, _ID);
	char* restName = (char*)calloc(200, sizeof(char));
	char* loc = (char*)calloc(200, sizeof(char));
	char* bHours = (char*)calloc(200, sizeof(char));

	// ���Ե�� â
	text(7, 8, "�����̸�");
	drawBox(17, 7, 25, 1);
	text(7, 11, "������ġ");
	drawBox(17, 10, 25, 1);
	text(7, 14, "�����ð�");
	drawBox(17, 13, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "���");
	//�Ϲ� ����� ���
	if (regist == FALSE)
	{
		drawBox(37, 23, 10, 1);
		text(39, 24, "���ư���");
	}

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//�����̸� �Է�
			if ((7 <= y) && (y <= 9))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput2(19, 8, restName);
						realloc(restName, sizeof(char) * (strlen(restName)+2));
					}
				}
			}
			//������ġ �Է�
			if ((10 <= y) && (y <= 12))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput2(19, 11, loc);
						realloc(loc, sizeof(char) * (strlen(loc)+2));
					}
				}
			}
			//�����ð� �Է�
			if ((13 <= y) && (y <= 15))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput2(19,14, bHours);
						realloc(bHours, sizeof(char) * (strlen(bHours))+2);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//��� ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						newRestInput(ID, restName, loc, bHours, tempregist);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(16, 24, "���");
			}
			//�Ϲ� ����� ���
			if (regist == FALSE)
			{
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
							text(38, 20, "       ");
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
		}
		else
		{
			colorSetRestore();
			text(16, 24, "���");
			//�Ϲ� ����� ���
			if (regist == FALSE)
			{
				text(39, 24, "���ư���");
			}
		}
	}
}

//�������� ���Ͽ� �Է�
void newRestInput(char* ID, char* restName, char* loc, char* bHours, bool regist)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;

	Rest rest;
	rest.restName = (char*)calloc(strlen(restName), sizeof(char));
	rest.loc = (char*)calloc(strlen(loc), sizeof(char));
	rest.bHours = (char*)calloc(strlen(bHours), sizeof(char));
	strcpy(rest.ID, ID);
	strcpy(rest.restName, restName);
	strcpy(rest.loc, loc);
	strcpy(rest.bHours, bHours);
	if (strcmp(restName, "\0") != 0)
	{
		if (strcmp(loc, "\0") != 0)
		{
			if (strcmp(bHours, "\0") != 0)
			{
				restInfoFileWrite(rest);
				drawBox(10, 10, 30, 10);
				text(14, 12, "���� ����� �Ϸ�Ǿ����ϴ�.");
				drawBox(19, 18, 10, 1);
				text(24, 19, "Ȯ��");
				while (1)
				{
					ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
					mouseMove(&x, &y);
					if ((19 <= x) && (x <= 29))
					{
						if ((17 <= y) && (y <= 19))
						{
							colorSetSelect();
							text(24, 19, "Ȯ��");
							if (mmval.rec.EventType == MOUSE_EVENT)
							{
								if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
								{
									clearConsole();
									colorSetRestore();
									text(24, 19, "       ");
									text(35, 20, "          ");
									//���� ȭ�鿡�� �Ѿ���� ���
									if (regist == TRUE)
									{
										title();
									}
									//�Ϲ� ����� ���
								}
							}
						}
						else
						{
							colorSetRestore();
							text(24, 19, "Ȯ��");
						}
					}
					else
					{
						colorSetRestore();
						text(24, 19, "Ȯ��");
					}
				}
			}
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "�����ð��� �Էµ��� �ʾҽ��ϴ�.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "������ġ�� �Էµ��� �ʾҽ��ϴ�.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "�����̸��� �Էµ��� �ʾҽ��ϴ�.");
	}
}
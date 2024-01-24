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
void showMain(User user);
void newRest(User user, bool regist);
void newRestInput(User user, char* restName, char* loc, char* bHours, bool regist);
void newFavRest(User user);

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
							newRest(resUser, TRUE);
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
	int loginID = 0;
	int suc = 0;
	temps = userInfoFileRead(&size);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].ID, ID) == 0)
		{
			if (strcmp(temps[i].PW, PW) == 0)
			{
				suc = 1;
				loginID = i;
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
		clearConsole();
		colorSetRestore();
		text(44, 14, "        ");
		showMain(temps[loginID]);
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

	//�������� ���� �б�
	temps = userInfoFileRead(&size);

	//�Է��� ������ ���������� ��ġ�ϴ��� Ž��
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

	//��ġ�ϸ� ���̵� �����ֱ�
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
	//�������� ���� �б�
	temps = userInfoFileRead(&size);

	//�Է��� ������ ���������� ��ġ�ϴ��� Ž��
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

	//��ġ�ϸ� �� PW�� �޾� �����Ű��
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

//����ȭ��
void showMain(User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;
	int i = 0;

	int ownersRestSize = 0;
	int restListSize = 0;

	Rest* ownersRest;
	RestList* restList;

	//�� ���� â
	if (user.owner == 0)
	{
		int restSize = 0;
		int reviewSize = 0;

		int restCheck = 0;
		int reviewCheck = 0;

		drawBox(10, 2, 40, 3);
		drawBox(10, 7, 40, 3);
		drawBox(10, 12, 40, 3);

		text(3, 19, "�� = �������� ������ ���ϰ� �Ļ��� �� �ִ� ���� (���ټ�)");
		text(3, 20, "�� = ������ ��õ���ٸ��� ȣ��ȣ ���� �丮�� ���� (�丮)");
		text(3, 21, "�� = ������ ���� ��� �������� ���� ���� (����)");

		drawBox(10, 23, 11, 1);
		text(12, 24, "���������");
		drawBox(24, 23, 10, 1);
		text(27, 24, "��������");
		drawBox(37, 23, 13, 1);
		text(39, 24, "ȸ����������");

		//���Ͽ��� ���������� �������� �б�
		Rest* curRest = restInfoFileRead(&restSize);
		Review* curReview = reviewFileRead(&reviewSize);

		//���������� �������� ���Ͽ� ����Ʈ ������ ���ϱ�
		for (reviewCheck = 0; reviewCheck < reviewSize; reviewCheck++)
		{
			if (strcmp(curReview[reviewCheck].ID, user.ID) == 0)
			{
				for (restCheck = 0; restCheck < restSize; restCheck++)
				{
					if (strcmp(curRest[restCheck].code, curReview[reviewCheck].code) == 0)
					{
						restListSize++;
					}
				}
			}
		}

		//���������� ���������� ����Ʈ�� �ֱ�
		if (restListSize != 0)
		{
			restList = (RestList*)malloc(sizeof(RestList) * restListSize);
			for (reviewCheck = 0; reviewCheck < reviewSize; reviewCheck++)
			{
				if (strcmp(curReview[reviewCheck].ID, user.ID) == 0)
				{
					for (restCheck = 0; restCheck < restSize; restCheck++)
					{
						if (strcmp(curRest[restCheck].code, curReview[reviewCheck].code) == 0)
						{
							restList[i].rest = curRest[restCheck];
							restList[i].review = curReview[reviewCheck];
							i++;
						}
					}
				}
			}
			i = 0;
		}
	}
	//�������� ���� â
	else
	{
		int restSize = 0;
		int restCheck = 0;

		drawBox(10, 2, 40, 3);
		drawBox(10, 7, 40, 3);
		drawBox(10, 12, 40, 3);

		drawBox(24, 23, 10, 1);
		text(27, 24, "���Ե��");

		Rest* curRest = restInfoFileRead(&restSize);

		for (restCheck = 0; restCheck < restSize; restCheck++)
		{
			if (strcmp(curRest[restCheck].ID, user.ID) == 0)
			{
				ownersRestSize++;
			}
		}

		if (ownersRestSize != 0)
		{
			ownersRest = (Rest*)malloc(sizeof(Rest) * ownersRestSize);
			for (restCheck = 0; restCheck < restSize; restCheck++)
			{
				if (strcmp(curRest[restCheck].ID, user.ID) == 0)
				{
					ownersRest[i] = curRest[restCheck];
					i++;
				}
			}
			i = 0;
		}

	}


	while (1)
	{
		//�������� ������ ȭ��
		if (user.owner == 0)
		{
			if (restListSize == 0)
			{
				colorSetRestore();
				text(12, 4, "��ϵ� ������ �����ϴ�.");
			}
			else
			{
				colorSetRestore();
				text(12, 4, restList[i].rest.restName);
				if ((restList[i].review.repu / 100) == 1)
				{
					text(12, 5, "��");
				}
				if (((restList[i].review.repu % 100) / 10) == 1)
				{
					text(13, 5, "��");
				}
				if ((restList[i].review.repu % 10) == 1)
				{
					text(14, 5, "��");
				}
				if (restListSize >= 2)
				{
					text(12, 9, restList[i + 1].rest.restName);
					if ((restList[i + 1].review.repu / 100) == 1)
					{
						text(12, 9, "��");
					}
					if (((restList[i + 1].review.repu % 100) / 10) == 1)
					{
						text(13, 6, "��");
					}
					if ((restList[i + 1].review.repu % 10) == 1)
					{
						text(14, 7, "��");
					}
				}
				if (restListSize >= 3)
				{
					text(12, 14, restList[i + 2].rest.restName);
					if ((restList[i + 2].review.repu / 100) == 1)
					{
						text(12, 14, "��");
					}
					if (((restList[i + 2].review.repu % 100) / 10) == 1)
					{
						text(13, 14, "��");
					}
					if ((restList[i + 2].review.repu % 10) == 1)
					{
						text(14, 14, "��");
					}
				}
			}
		}
		else
		{
			if (ownersRestSize == 0)
			{
				colorSetRestore();
				text(12, 4, "(�̰��� �����Դϴ�.)");
			}
			else
			{
				colorSetRestore();
				text(12, 4, ownersRest[i].restName);
				if (ownersRestSize >= 2)
				{
					text(12, 9, ownersRest[i + 1].restName);
				}
				if (ownersRestSize >= 3)
				{
					text(12, 14, ownersRest[i + 2].restName);
				}
			}
		}
		// ���콺 �̵��� Ŭ���� ó��
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
						if (user.owner == 0)
						{
							// ��ũ�� ���� Ȯ��
							short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

							//���콺 ���� ��ũ�� ��
							if (wheelDelta > 0)
							{
								if ((restListSize > 3) && (0 < i))
								{
									i--;
								}
							}
							//���콺 �Ʒ��� ��ũ�� ��
							else if (wheelDelta < 0)
							{
								if ((restListSize > 3) && (restListSize > i + 3))
								{
									i++;
								}
							}
						}
						else
						{
							// ��ũ�� ���� Ȯ��
							short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

							//���콺 ���� ��ũ�� ��
							if (wheelDelta > 0)
							{
								if ((ownersRestSize > 3) && (0 < i))
								{
									i--;
								}
							}
							//���콺 �Ʒ��� ��ũ�� ��
							else if (wheelDelta < 0)
							{
								if ((ownersRestSize > 3) && (ownersRestSize > i + 3))
								{
									i++;
								}
							}
						}
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//��������� ��ư
			if ((9 <= x) && (x <= 24))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(12, 24, "���������");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							clearConsole();
							colorSetRestore();
							text(12, 24, "              ");
							newFavRest(user);
						}
					}
				}
			}
			else
			{
				if (user.owner == 0)
				{
					colorSetRestore();
					text(12, 24, "���������");
				}
			}
			//�������� ��ư�� ���Ե�� ��ư
			if ((25 <= x) && (x <= 36))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(27, 24, "��������");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							clearConsole();
							colorSetRestore();
							text(27, 24, "          ");
						}
					}
				}
				else
				{
					colorSetSelect();
					text(27, 24, "���Ե��");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							clearConsole();
							colorSetRestore();
							text(27, 24, "          ");
							newRest(user, FALSE);
						}
					}
				}
			}
			else
			{
				if (user.owner == 0)
				{
					colorSetRestore();
					text(27, 24, "��������");
				}
				else
				{
					colorSetRestore();
					text(27, 24, "���Ե��");
				}
			}
			//ȸ���������� ��ư
			if ((36 <= x) && (x <= 52))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(39, 24, "ȸ����������");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							clearConsole();
							colorSetRestore();
							text(39, 24, "          ");
						}
					}
				}
			}
			else
			{
				if (user.owner == 0)
				{
					colorSetRestore();
					text(39, 24, "ȸ����������");
				}
			}
		}
		else
		{
			if (user.owner == 0)
			{
				colorSetRestore();
				text(12, 24, "���������");
				text(27, 24, "��������");
				text(39, 24, "ȸ����������");
			}
			else
			{
				colorSetRestore();
				text(27, 24, "���Ե��");
			}
		}
	}
}

//���Ե�� ȭ��
void newRest(User user, bool regist)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	bool tempregist = regist;

	char ID[20] = "\0";
	strcpy(ID, user.ID);
	char restName[40] = "\0";
	char loc[60] = "\0";
	char bHours[60] = "\0";

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
						textInput(19, 8, restName, FALSE);
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
						textInput(19, 11, loc, FALSE);
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
						textInput(19, 14, bHours, FALSE);
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
						newRestInput(user, restName, loc, bHours, tempregist);
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
							showMain(user);
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
void newRestInput(User user, char* restName, char* loc, char* bHours, bool regist)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;

	Rest resRest;
	strcpy(resRest.ID, user.ID);
	strcpy(resRest.restName, restName);
	strcpy(resRest.loc, loc);
	strcpy(resRest.bHours, bHours);
	char code[28] = "\0";
	if (regist == TRUE)
	{
		newCode(code, user.ID, 1);
	}
	else
	{
		int size;
		int ownerSize = 0;
		Rest* rest = restInfoFileRead(&size);
		for (int i = 0; i < size; i++)
		{
			if (strcmp(rest[i].ID, user.ID) == 0)
			{
				ownerSize++;
			}
		}
		newCode(code, user.ID, ownerSize);
	}
	strcpy(resRest.code, code);
	if (strcmp(restName, "\0") != 0)
	{
		if (strcmp(loc, "\0") != 0)
		{
			if (strcmp(bHours, "\0") != 0)
			{
				restInfoFileWrite(resRest);
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
									else
									{
										text(16, 24, "          ");
										text(39, 24, "          ");
										showMain(user);
									}
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

//��������� ȭ��
void newFavRest(User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	char ID[20] = "\0";
	strcpy(ID, user.ID);
	char restName[40] = "\0";
	int repu = 0;
	char* review = (char*)calloc(300, sizeof(char));

	// ���Ե�� â
	text(7, 4, "�����̸�");
	drawBox(17, 3, 30, 1);
	text(7, 7, "����");

	text(19, 7, "��");
	text(22, 7, "��");
	text(25, 7, "��");

	text(27, 7, "(���ϴ� ������ Ŭ��)");

	text(3, 10, "�� = �������� ������ ���ϰ� �Ļ��� �� �ִ� ���� (���ټ�)");
	text(3, 11, "�� = ������ ��õ���ٸ��� ȣ��ȣ ���� �丮�� ���� (�丮)");
	text(3, 12, "�� = ������ ���� ��� �������� ���� ���� (����)");

	text(7, 15, "����");
	drawBox(17, 14, 30, 7);

	drawBox(25, 23, 10, 1);
	text(30, 24, "���");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 52))
		{
			//�����̸� �Է�
			if ((3 <= y) && (y <= 5))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput(19, 4, restName, FALSE);
					}
				}
			}
			//����
			if ((6 <= y) && (y <= 8))
			{
				//��
				if ((18 <= x) && (x <= 20))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu / 100) == 0)
							{
								colorSetSelect();
								text(19, 7, "��");
								repu += 100;
							}
							else
							{
								colorSetRestore();
								text(19, 7, "��");
								repu -= 100;
							}
						}
					}
				}
				//��
				if ((21 <= x) && (x <= 23))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu % 100) / 10 == 0)
							{
								colorSetSelect();
								text(22, 7, "��");
								repu += 10;
							}
							else
							{
								colorSetRestore();
								text(22, 7, "��");
								repu -= 10;
							}
						}
					}
				}
				//������
				if ((24 <= x) && (x <= 26))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu % 10) == 0)
							{
								colorSetSelect();
								text(25, 7, "��");
								repu += 1;
							}
							else
							{
								colorSetRestore();
								text(25, 7, "��");
								repu -= 1;
							}
						}
					}
				}
			}
			//���� �Է�
			if ((14 <= y) && (y <= 21))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						textInput2(19, 15, review);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//��� ��ư
			if ((24 <= x) && (x <= 36))
			{
				colorSetSelect();
				text(30, 24, "���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
					}
				}
			}
			else
			{
				colorSetRestore();
				text(30, 24, "���");
			}
		}
		else
		{
			colorSetRestore();
			text(30, 24, "���");
		}
	}
}
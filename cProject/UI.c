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
void newFavRestInput(User user, char* restName, int repu, char* usersReview);
void newFavRestInputDupThree(Review review, User user);
void userInfoReset(User user);
void userInfoResetInput(User user, char* userName, char* PW, char* birth);
void userResign(User user);
void userResignCheck(User user);

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
	drawBox(17, 10, 20, 1);
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
		colorSetRestore();
		text(7, 11, "���̵�");
		text(7, 17, "��й�ȣ");
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
						colorSetRestore();
						clearConsole();
						text(16, 24, "         ");
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
						colorSetRestore();
						clearConsole();
						text(27, 24, "         ");
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
						colorSetRestore();
						clearConsole();
						text(39, 24, "            ");
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

	char userName[12] = "\0";
	char ID[20] = "\0";
	char PW[20] = "\0";
	char birth[8] = "\0";

	// ���� â
	drawBox(17, 7, 25, 1);
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);
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
		colorSetRestore();
		text(7, 8, "�̸�");
		text(7, 11, "���̵�");
		text(7, 14, "��й�ȣ");
		text(7, 17, "�������");
		text(7, 18, "(YYMMDD)");
		text(7, 20, "���� ���� �̽ʴϱ�?");
		text(7, 21, "(���� ������ ���Խ� ���� �ϳ� �ʼ� ���)");
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
						colorSetRestore();
						clearConsole();
						text(35, 20, "            ");
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
						strcpy(resUser.ID, ID);
						strcpy(resUser.PW, PW);
						strcpy(resUser.userName, userName);
						strcpy(resUser.birth, birth);
						resUser.owner = owner;
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
		colorSetRestore();
		clearConsole();
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
	char userName[12] = "\0";
	char birth[8] = "\0";

	// IDã�� â
	drawBox(17, 7, 25, 1);
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "ã��");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		colorSetRestore();
		text(7, 8, "�̸�");
		text(7, 17, "�������");
		text(7, 18, "(YYMMDD)");
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
						colorSetRestore();
						clearConsole();
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
							colorSetRestore();
							clearConsole();
							text(27, 19, "       ");
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
	char userName[12] = "\0";
	char birth[8] = "\0";

	// ���� â
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(15, 24, "�ʱ�ȭ");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		colorSetRestore();
		text(7, 11, "�̸�");
		text(7, 14, "���̵�");
		text(7, 17, "�������");
		text(7, 18, "(YYMMDD)");
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
						colorSetRestore();
						clearConsole();
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

	drawBox(10, 2, 40, 3);
	drawBox(10, 7, 40, 3);
	drawBox(10, 12, 40, 3);

	//�� ���� â
	if (user.owner == 0)
	{
		int restSize = 0;
		int reviewSize = 0;

		int restCheck = 0;
		int reviewCheck = 0;

		drawBox(10, 23, 11, 1);
		text(12, 24, "���������");
		drawBox(23, 23, 13, 1);
		text(25, 24, "ȸ����������");
		drawBox(38, 23, 10, 1);
		text(40, 24, "��������");
		drawBox(10, 26, 11, 1);
		text(13, 27, "�α׾ƿ�");

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
		free(curRest);
		free(curReview);
	}
	//�������� ���� â
	else
	{
		int restSize = 0;
		int restCheck = 0;

		drawBox(10, 23, 11, 1);
		text(12, 24, "���Ե��");
		drawBox(23, 23, 13, 1);
		text(25, 24, "ȸ����������");
		drawBox(38, 23, 12, 1);
		text(40, 24, "�α׾ƿ�");

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
		free(curRest);
	}


	while (1)
	{
		//�������� ������ ȭ��
		if (user.owner == 0)
		{
			colorSetRestore();
			text(3, 19, "�� = �������� ������ ���ϰ� �Ļ��� �� �ִ� ���� (���ټ�)");
			text(3, 20, "�� = ������ ��õ���ٸ��� ȣ��ȣ ���� �丮�� ���� (�丮)");
			text(3, 21, "�� = ������ ���� ��� �������� ���� ���� (����)");
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
					text(14, 5, "��");
				}
				if ((restList[i].review.repu % 10) == 1)
				{
					text(16, 5, "��");
				}
				if (restListSize >= 2)
				{
					text(12, 9, restList[i + 1].rest.restName);
					if ((restList[i + 1].review.repu / 100) == 1)
					{
						text(12, 10, "��");
					}
					if (((restList[i + 1].review.repu % 100) / 10) == 1)
					{
						text(14, 10, "��");
					}
					if ((restList[i + 1].review.repu % 10) == 1)
					{
						text(16, 10, "��");
					}
				}
				if (restListSize >= 3)
				{
					text(12, 14, restList[i + 2].rest.restName);
					if ((restList[i + 2].review.repu / 100) == 1)
					{
						text(12, 15, "��");
					}
					if (((restList[i + 2].review.repu % 100) / 10) == 1)
					{
						text(14, 15, "��");
					}
					if ((restList[i + 2].review.repu % 10) == 1)
					{
						text(16, 15, "��");
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
									text(12, 4, "                ");
									text(12, 9, "                ");
									text(12, 14, "                ");
									text(12, 5, "                ");
									text(12, 10, "                ");
									text(12, 15, "                ");
									i--;
								}
							}
							//���콺 �Ʒ��� ��ũ�� ��
							else if (wheelDelta < 0)
							{
								if ((restListSize > 3) && (restListSize > i + 3))
								{
									text(12, 4, "                ");
									text(12, 9, "                ");
									text(12, 14, "                ");
									text(12, 5, "                ");
									text(12, 10, "                ");
									text(12, 15, "                ");
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
									text(12, 4, "                ");
									text(12, 9, "                ");
									text(12, 14, "                ");
									i--;
								}
							}
							//���콺 �Ʒ��� ��ũ�� ��
							else if (wheelDelta < 0)
							{
								if ((ownersRestSize > 3) && (ownersRestSize > i + 3))
								{
									text(12, 4, "                ");
									text(12, 9, "                ");
									text(12, 14, "                ");
									i++;
								}
							}
						}
					}
				}
				if ((1 <= y) && (y <= 5))
				{
					if ((restListSize != 0) || (ownersRestSize != 0))
					{
						text(9, 4, ">");
						if (mmval.rec.EventType == MOUSE_EVENT)
						{
							if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
							{
							}
						}
					}
				}
				else
				{
					text(9, 4, " ");
				}
				if ((6 <= y) && (y <= 10))
				{
					if ((restListSize >= 2) || (ownersRestSize >= 2))
					{
						text(9, 9, ">");
						if (mmval.rec.EventType == MOUSE_EVENT)
						{
							if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
							{
							}
						}
					}
				}
				else
				{
					text(9, 9, " ");
				}
				if ((11 <= y) && (y <= 15))
				{
					if ((restListSize >= 3) || (ownersRestSize >= 3))
					{
						text(9, 14, ">");
						if (mmval.rec.EventType == MOUSE_EVENT)
						{
							if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
							{
							}
						}
					}
				}
				else
				{
					text(9, 14, " ");
				}
			}
			else
			{
				text(9, 4, " ");
				text(9, 9, " ");
				text(9, 14, " ");
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//��������� ��ư�� ���Ե�� ��ư
			if ((9 <= x) && (x <= 22))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(12, 24, "���������");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							colorSetRestore();
							clearConsole();
							text(12, 24, "              ");
							newFavRest(user);
						}
					}
				}
				else
				{
					colorSetSelect();
					text(12, 24, "���Ե��");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							colorSetRestore();
							clearConsole();
							text(12, 24, "          ");
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
					text(12, 24, "���������");
				}
				else
				{
					colorSetRestore();
					text(12, 24, "���Ե��");
				}
			}
			//ȸ���������� ��ư
			if ((23 <= x) && (x <= 36))
			{
				colorSetSelect();
				text(25, 24, "ȸ����������");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						clearConsole();
						text(25, 24, "             ");
						userInfoReset(user);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(25, 24, "ȸ����������");
			}
			//�������� ��ư�� ���������� �α׾ƿ� ��ư
			if ((37 <= x) && (x <= 51))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(40, 24, "��������");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
						}
					}
				}
				else
				{
					colorSetSelect();
					text(40, 24, "�α׾ƿ�");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							colorSetRestore();
							clearConsole();
							text(39, 24, "          ");
							title();
						}
					}
				}
			}
			else
			{
				if (user.owner == 0)
				{
					colorSetRestore();
					text(40, 24, "��������");
				}
				else
				{
					colorSetRestore();
					text(40, 24, "�α׾ƿ�");
				}
			}
		}
		else
		{
			if (user.owner == 0)
			{
				colorSetRestore();
				text(12, 24, "���������");
				text(25, 24, "ȸ����������");
				text(40, 24, "��������");
			}
			else
			{
				colorSetRestore();
				text(12, 24, "���Ե��");
				text(25, 24, "ȸ����������");
				text(40, 24, "�α׾ƿ�");
			}
		}
		//�Ϲݰ��� �α׾ƿ� ��ư
		if (user.owner == 0)
		{
			if ((25 <= y) && (y <= 27))
			{
				if ((9 <= x) && (x <= 22))
				{
					colorSetSelect();
					text(13, 27, "�α׾ƿ�");
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							colorSetRestore();
							clearConsole();
							text(13, 27, "          ");
							title();
						}
					}
				}
				else
				{
					colorSetRestore();
					text(13, 27, "�α׾ƿ�");
				}
			}
			else
			{
				colorSetRestore();
				text(13, 27, "�α׾ƿ�");
			}
		}
	}
	free(restList);
	free(ownersRest);
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
	drawBox(17, 7, 25, 1);
	drawBox(17, 10, 25, 1);
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
		colorSetRestore();
		text(7, 8, "�����̸�");
		text(7, 11, "������ġ");
		text(7, 14, "�����ð�");
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
	char code[28] = "\0";

	//����ȭ�鿡�� �Ѿ���� ���
	if (regist == TRUE)
	{
		newCode(code, user.ID, 1);
	}
	else
	{
		int size;
		int ownerSize = 1;
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
	if ((strcmp(restName, "\0") != 0) && (strlen(restName) <= 40))
	{
		if ((strcmp(loc, "\0") != 0) && (strlen(loc) <= 60))
		{
			if (strcmp(bHours, "\0") != 0 && (strlen(bHours) <= 60))
			{
				strcpy(resRest.ID, user.ID);
				strcpy(resRest.restName, restName);
				strcpy(resRest.loc, loc);
				strcpy(resRest.bHours, bHours);
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
									//���� ȭ�鿡�� �Ѿ���� ���
									if (regist == TRUE)
									{
										title();
									}
									//�Ϲ� ����� ���
									else
									{
										text(16, 24, "          ");
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
				text(20, 27, "��ȿ���� ���� �����ð��Դϴ�.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "��ȿ���� ���� ������ġ�Դϴ�.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "��ȿ���� ���� �����̸��Դϴ�.");
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
	char* usersReview = (char*)calloc(300, sizeof(char));

	// ���Ե�� â
	drawBox(17, 3, 30, 1);

	text(19, 7, "��");
	text(22, 7, "��");
	text(25, 7, "��");

	drawBox(17, 14, 30, 7);

	drawBox(10, 23, 11, 1);
	text(12, 24, "���Ե��");
	drawBox(37, 23, 11, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		colorSetRestore();
		text(7, 4, "�����̸�");
		text(7, 7, "����");

		text(27, 7, "(���ϴ� ������ Ŭ��)");

		text(7, 15, "����");

		text(3, 10, "�� = �������� ������ ���ϰ� �Ļ��� �� �ִ� ���� (���ټ�)");
		text(3, 11, "�� = ������ ��õ���ٸ��� ȣ��ȣ ���� �丮�� ���� (�丮)");
		text(3, 12, "�� = ������ ���� ��� �������� ���� ���� (����)");
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
						textInput2(19, 15, usersReview);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//��� ��ư
			if ((9 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(12, 24, "���Ե��");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						newFavRestInput(user, restName, repu, usersReview);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(12, 24, "���Ե��");
			}
			//���ư��� ��ư
			if ((36 <= x) && (x <= 49))
			{
				colorSetSelect();
				text(39, 24, "���ư���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						clearConsole();
						text(39, 24, "          ");
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
		else
		{
			colorSetRestore();
			text(12, 24, "���Ե��");
			colorSetRestore();
			text(39, 24, "���ư���");
		}
	}
	free(usersReview);
}

//�������� ���Ͽ� �Է�
void newFavRestInput(User user, char* restName, int repu, char* usersReview)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;
	int dupCheck;
	int ownerCheck;

	int restSize = 0;
	int ownerSize = 0;
	int dupRestListSize = 0;

	int dupCase = 0;
	int i = 0;

	Review review;
	strcpy(review.ID, user.ID);
	review.repu = repu;
	strcpy(review.usersReview, usersReview);

	//���Ͽ��� �������� �б�
	Rest* restList = restInfoFileRead(&restSize);
	User* restOwnerList = userInfoFileRead(&ownerSize);

	RestOwner* dupRestList;

	for (dupCheck = 0; dupCheck < restSize; dupCheck++)
	{
		if (strcmp(restList[dupCheck].restName, restName) == 0)
		{
			dupRestListSize++;
		}
	}

	//�ߺ��Ǵ� �̸��� ���� ���Ե��� ����Ʈ�� ����
	if (dupRestListSize != 0)
	{
		dupRestList = (RestOwner*)malloc(sizeof(RestOwner) * dupRestListSize);
		for (dupCheck = 0; dupCheck < restSize; dupCheck++)
		{
			if (strcmp(restList[dupCheck].restName, restName) == 0)
			{
				for (ownerCheck = 0; ownerCheck < ownerSize; ownerCheck++)
				{
					if (strcmp(restList[dupCheck].ID, restOwnerList[ownerCheck].ID) == 0)
					{
						dupRestList[i].rest = restList[dupCheck];
						dupRestList[i].user = restOwnerList[ownerCheck];
						i++;
					}
				}
			}
		}
		i = 0;
	}

	if (dupRestListSize == 0)
	{
		//�Է��� ���԰� ���� ���
		dupCase = 1;
	}
	else if (dupRestListSize == 1)
	{
		//�Է��� ���԰� �ߺ����� ���� ���
		dupCase = 2;
	}
	else
	{
		//�Է��� ���԰� �ߺ��� ���
		dupCase = 3;
	}

	if (repu != 0)
	{
		if ((strcmp(usersReview, "\0") != 0) && (strlen(usersReview) <= 300))
		{
			if (dupCase == 2)
			{
				if (isValidRest(dupRestList[0].rest.code, user.ID))
				{
					strcpy(review.code, dupRestList[0].rest.code);
					reviewFileWrite(review);
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
										text(24, 19, "          ");
										showMain(user);
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
					text(20, 27, "�̹� �������� ��ϵ� �����Դϴ�");
				}
			}
			else if (dupCase == 1)
			{
				text(20, 27, "                                      ");
				text(20, 27, "��ϵ��� ���� �����Դϴ�.");
			}
			else
			{
				drawBox(6, 1, 48, 20);
				drawBox(10, 2, 40, 3);
				drawBox(10, 7, 40, 3);
				drawBox(10, 12, 40, 3);

				text(12, 19, "�� ��Ͽ��� �ش�Ǵ� ���Ը� ����ּ���");

				while (1)
				{
					//�������� ������ ȭ��
					if (dupRestListSize == 0)
					{
						colorSetRestore();
						text(12, 4, "(�̰��� �����Դϴ�.)");
					}
					else
					{
						colorSetRestore();
						text(12, 3, dupRestList[i].rest.loc);
						text(12, 4, dupRestList[i].rest.bHours);
						text(12, 5, dupRestList[i].user.userName);
						if (dupRestListSize >= 2)
						{
							text(12, 8, dupRestList[i + 1].rest.loc);
							text(12, 9, dupRestList[i + 1].rest.bHours);
							text(12, 10, dupRestList[i + 1].user.userName);
						}
						if (dupRestListSize >= 3)
						{
							text(12, 13, dupRestList[i + 2].rest.loc);
							text(12, 14, dupRestList[i + 2].rest.bHours);
							text(12, 15, dupRestList[i + 2].user.userName);
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
									// ��ũ�� ���� Ȯ��
									short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

									//���콺 ���� ��ũ�� ��
									if (wheelDelta > 0)
									{
										if ((dupRestListSize > 3) && (0 < i))
										{
											i--;
										}
									}
									//���콺 �Ʒ��� ��ũ�� ��
									else if (wheelDelta < 0)
									{
										if ((dupRestListSize > 3) && (dupRestListSize > i + 3))
										{
											i++;
										}
									}
								}
							}
							if ((1 <= y) && (y <= 5))
							{
								if (dupRestListSize != 0)
								{
									text(9, 4, ">");
									if (mmval.rec.EventType == MOUSE_EVENT)
									{
										if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											strcpy(review.code, dupRestList[i].rest.code);
											newFavRestInputDupThree(review, user);
										}
									}
								}
							}
							else
							{
								text(9, 4, " ");
							}
							if ((6 <= y) && (y <= 10))
							{
								if (dupRestListSize >= 2)
								{
									text(9, 9, ">");
									if (mmval.rec.EventType == MOUSE_EVENT)
									{
										if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											strcpy(review.code, dupRestList[i + 1].rest.code);
											newFavRestInputDupThree(review, user);
										}
									}
								}
							}
							else
							{
								text(9, 9, " ");
							}
							if ((11 <= y) && (y <= 15))
							{
								if (dupRestListSize >= 3)
								{
									text(9, 14, ">");
									if (mmval.rec.EventType == MOUSE_EVENT)
									{
										if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											strcpy(review.code, dupRestList[i + 2].rest.code);
											newFavRestInputDupThree(review, user);
										}
									}
								}
							}
							else
							{
								text(9, 14, " ");
							}
						}
						else
						{
							text(9, 4, " ");
							text(9, 9, " ");
							text(9, 14, " ");
						}
					}
				}
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "��ȿ���� ���� �����Դϴ�.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "������ũ�� �ϳ��� �����ؾ� �մϴ�.");
	}
	free(restList);
	free(restOwnerList);
}

//�������� ���Ͽ� �Է��Ҷ� �ߺ��Ǵ� ���Կ� ���� ó��
void newFavRestInputDupThree(Review review, User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	if (isValidRest(review.code, user.ID))
	{
		reviewFileWrite(review);
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
							text(24, 19, "         ");
							showMain(user);
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
		drawBox(10, 10, 30, 10);
		text(14, 12, "�̹� ��ϵ� �����Դϴ�.");
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
							text(24, 19, "         ");
							newFavRest(user);
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
}

//ȸ���������� ȭ��
void userInfoReset(User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;
	int num = 0;

	char userName[12] = "\0";
	char PW[20] = "\0";
	char birth[8] = "\0";
	char PWstar[20] = "\0";

	strcpy(userName, user.userName);
	strcpy(PW, user.PW);
	strcpy(birth, user.birth);
	while (PW[num] != '\0')
	{
		PWstar[num] = '*';
		num++;
	}

	// ���� â
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);

	text(19, 11, userName);
	text(19, 14, PWstar);
	text(19, 17, birth);

	drawBox(11, 23, 10, 1);
	text(14, 24, "��������");
	drawBox(24, 23, 10, 1);
	text(27, 24, "ȸ��Ż��");
	drawBox(37, 23, 10, 1);
	text(39, 24, "���ư���");

	while (1)
	{
		colorSetRestore();
		text(7, 11, "�̸�");
		text(7, 14, "��й�ȣ");
		text(7, 17, "�������");
		text(7, 18, "(YYMMDD)");
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//�̸��Է�
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
		if ((22 <= y) && (y <= 24))
		{
			//�������� ��ư
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(14, 24, "��������");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						userInfoResetInput(user, userName, PW, birth);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(14, 24, "��������");
			}
			//ȸ��Ż�� ��ư
			if ((23 <= x) && (x <= 35))
			{
				colorSetSelect();
				text(27, 24, "ȸ��Ż��");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						userResign(user);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(27, 24, "ȸ��Ż��");
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
						colorSetRestore();
						clearConsole();
						text(39, 24, "            ");
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
		else
		{
			colorSetRestore();
			text(14, 24, "��������");
			text(27, 24, "ȸ��Ż��");
			text(39, 24, "���ư���");
		}
	}
}

//������ ���� ���Ͽ� �ֱ�
void userInfoResetInput(User user, char* userName, char* PW, char* birth)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	User* temps;
	int size;
	int resetID;
	int suc = 0;
	temps = userInfoFileRead(&size);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].ID, user.ID) == 0)
		{
			resetID = i;
		}
	}

	if (isValidName1(userName) || isValidName2(userName))
	{
		if (isValidPW(PW))
		{
			if (isValidBirth(birth))
			{
				strcpy(user.userName, userName);
				strcpy(user.PW, PW);
				strcpy(user.birth, birth);
				temps[resetID] = user;
				userInfoFileReWrite(temps, size);
				drawBox(15, 10, 28, 10);
				text(18, 12, "ȸ�������� �����Ǿ����ϴ�");
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
									showMain(user);
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
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "��ȿ���� ���� ������� �Դϴ�.");
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
		text(20, 27, "��ȿ���� ���� �̸� �Դϴ�.");
	}
}

//ȸ��Ż���ϱ�
void userResign(User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	drawBox(9, 10, 38, 10);
	text(18, 12, "���� Ż���Ͻðڽ��ϱ�?");
	if (user.owner == 1)
	{
		text(12, 13, "(Ż�� �� ��ϵ� ���԰� �����˴ϴ�.)");
	}
	drawBox(18, 18, 8, 1);
	text(21, 19, "Ȯ��");
	drawBox(31, 18, 8, 1);
	text(34, 19, "���");
	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((17 <= y) && (y <= 19))
		{
			if ((17 <= x) && (x <= 27))
			{
				colorSetSelect();
				text(21, 19, "Ȯ��");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						userResignCheck(user);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(21, 19, "Ȯ��");
			}
			if ((30 <= x) && (x <= 40))
			{
				colorSetSelect();
				text(34, 19, "���");
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						clearConsole();
						colorSetRestore();
						text(34, 19, "        ");
						userInfoReset(user);
					}
				}
			}
			else
			{
				colorSetRestore();
				text(34, 19, "���");
			}
		}
		else
		{
			colorSetRestore();
			text(21, 19, "Ȯ��");
			text(34, 19, "���");
		}
	}
}

//ȸ��Ż��Ȯ��
void userResignCheck(User user)
{
	// ���콺 Ŭ�� ���� ����
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	int userSize, restSize, reviewSize, newRestSize, newReviewSize;

	int resignID;
	int* resignRest;
	int* resignReview;

	int resignRestSize = 0; 
	int resignReviewSize = 0;

	User* tempsUser = userInfoFileRead(&userSize);
	Rest* tempsRest = restInfoFileRead(&restSize);
	Review* tempsReview = reviewFileRead(&reviewSize);
	newRestSize = restSize;
	newReviewSize = reviewSize;

	for (int i = 0; i < userSize; i++)
	{
		if (strcmp(tempsUser[i].ID, user.ID) == 0)
		{
			resignID = i;
		}
	}

	//���������ϰ�� ������ ���Կ� ���並 �迭�� �����Ѵ�.
	if (user.owner == 1)
	{
		for (int i = 0; i < restSize; i++)
		{
			if (strcmp(tempsRest[i].ID, user.ID) == 0)
			{
				for (int j = 0; j < reviewSize; j++)
				{
					if (strcmp(tempsRest[i].code, tempsReview[j].code) == 0)
					{
						resignReviewSize++;
					}
				}
				resignRestSize++;
			}
		}
		resignRest = (int*)malloc(sizeof(int) * resignRestSize);
		resignReview = (int*)malloc(sizeof(int) * resignReviewSize);

		resignRestSize = 0;
		resignReviewSize = 0;

		for (int i = 0; i < restSize; i++)
		{
			if (strcmp(tempsRest[i].ID, user.ID) == 0)
			{
				for (int j = 0; j < reviewSize; j++)
				{
					if (strcmp(tempsRest[i].code, tempsReview[j].code) == 0)
					{
						resignReview[resignReviewSize] = j;
						resignReviewSize++;
					}
				}
				resignRest[resignRestSize] = i;
				resignRestSize++;
			}
		}
	}

	//���Ͽ��� �ش� ���� �����
	for (int i = resignID; i < userSize; i++)
	{
		tempsUser[i] = tempsUser[i + 1];
	}
	realloc(tempsUser, sizeof(User) * (userSize - 1));
	userInfoFileReWrite(tempsUser,userSize-1);

	if (user.owner == 1)
	{
		//���Ͽ��� �ش� ���� �����
		for (int i = 0; i < resignRestSize; i++)
		{
			for (int j = resignRest[i]; j < restSize; j++)
			{
				tempsRest[j] = tempsRest[j + 1];
				newRestSize--;
			}
		}
		realloc(tempsRest, sizeof(Rest) * newRestSize);
		restInfoFileReWrite(tempsRest, newRestSize);

		//���Ͽ��� �ش� ���� �����
		for (int i = 0; i < resignReviewSize; i++)
		{
			for (int j = resignReview[i]; j < reviewSize; j++)
			{
				tempsReview[j] = tempsReview[j + 1];
				newReviewSize--;
			}
		}
		realloc(tempsReview, sizeof(Review) * newReviewSize);
		reviewFileReWrite(tempsReview, newReviewSize);
	}

	drawBox(9, 10, 38, 10);
	text(18, 12, "ȸ���� Ż��Ǿ����ϴ�.");
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
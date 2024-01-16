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

// 로그인창 화면
void title()
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	char ID[20] = "\0";
	char PW[20] = "\0";

	// 창 크기 정하기
	setConsole();

	// 로그인 창
	text(7, 11, "아이디");
	drawBox(17, 10, 20, 1);
	text(7, 17, "비밀번호");
	drawBox(17, 16, 20, 1);

	drawBox(41, 11, 10, 5);
	text(44, 14, "로그인");
	drawBox(11, 23, 10, 1);
	text(16, 24, "가입");
	drawBox(24, 23, 10, 1);
	text(27, 24, "ID 찾기");
	drawBox(37, 23, 10, 1);
	text(39, 24, "PW 초기화");

	// 마우스 이동과 클릭시 처리
	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 37))
		{
			//ID 입력
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
			//PW 입력
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
		//로그인 버튼
		if ((43 <= x) && (x <= 51))
		{
			if ((11 <= y) && (y <= 16))
			{
				colorSetSelect();
				text(44, 14, "로그인");
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
				text(44, 14, "로그인");
			}
		}
		else
		{
			colorSetRestore();
			text(44, 14, "로그인");
		}
		if ((22 <= y) && (y <= 24))
		{
			//가입하기 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "가입");
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
				text(16, 24, "가입");
			}
			//ID 찾기 버튼
			if ((25 <= x) && (x <= 35))
			{
				colorSetSelect();
				text(27, 24, "ID 찾기");
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
				text(27, 24, "ID 찾기");
			}
			//PW 초기화 버튼
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "PW 초기화");
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
				text(39, 24, "PW 초기화");
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "가입");
			text(27, 24, "ID 찾기");
			text(39, 24, "PW 초기화");
		}
	}
}

//가입 화면
void newUser()
{
	// 마우스 클릭 관련 변수
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

	// 가입 창
	text(7, 8, "이름");
	drawBox(17, 7, 25, 1);
	text(7, 11, "아이디");
	drawBox(17, 10, 25, 1);
	text(7, 14, "비밀번호");
	drawBox(17, 13, 25, 1);
	text(7, 17, "생년월일");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);
	text(7, 20, "가게 주인 이십니까?");
	text(7, 21, "(가게 주인은 가입시 가게 하나 필수 등록)");
	text(35, 20, "예");
	colorSetSelect();
	text(38, 20, "아니오");
	colorSetRestore();

	drawBox(11, 23, 10, 1);
	text(16, 24, "가입");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//이름 입력
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
			//ID입력
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
			//PW입력
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
			//생년월일입력
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
		//가게 주인 여부 선택
		if ((20 <= y) && (y <= 21))
		{
			if ((35 <= x) && (x <= 36))
			{
				if (mmval.rec.EventType == MOUSE_EVENT)
				{
					if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						colorSetRestore();
						text(38, 20, "아니오");
						colorSetSelect();
						text(35, 20, "예");
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
						text(35, 20, "예");
						colorSetSelect();
						text(38, 20, "아니오");
						owner = 0;
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//가입 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "가입");
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
				text(16, 24, "가입");
			}
			//돌아가기 버튼
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "돌아가기");
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
				text(39, 24, "돌아가기");
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "가입");
			text(39, 24, "돌아가기");
		}
	}
}

//가입 정보 파일에 입력
void newUserInput(char* ID, char* PW, char* userName, char* birth, int owner)
{
	// 마우스 클릭 관련 변수
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
							text(18, 12, "가입이 완료되었습니다.");
							drawBox(22, 18, 10, 1);
							text(27, 19, "확인");
							while (1)
							{
								ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
								mouseMove(&x, &y);
								if ((22 <= x) && (x <= 32))
								{
									if ((17 <= y) && (y <= 19))
									{
										colorSetSelect();
										text(27, 19, "확인");
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
										text(27, 19, "확인");
									}
								}
								else
								{
									colorSetRestore();
									text(27, 19, "확인");
								}
							}
						}
					}
					else
					{
						text(20, 27, "                                      ");
						text(20, 27, "유효하지 않은 생년월일 입니다.");
					}
				}
				else
				{
					text(20, 27, "                                      ");
					text(20, 27, "유효하지 않은 이름 입니다.");
				}
			}
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "유효하지 않은 PW 입니다.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "중복되는 ID 입니다.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "유효하지 않은 ID 입니다.");
	}
}

//로그인 버튼
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
		text(20, 27, "비밀번호가 다릅니다");
	}
	else if (suc == 1)
	{
		text(20, 27, "로그인 성공");
	}
	else
	{
		text(20, 27, "일치하는 ID가 없습니다.");
	}
	free(temps);
}

//ID찾기 화면
void idFind()
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;
	char userName[10] = "\0";
	char birth[7] = "\0";

	// ID찾기 창
	text(7, 8, "이름");
	drawBox(17, 7, 25, 1);
	text(7, 17, "생년월일");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "찾기");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//이름 입력
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
			//생년월일입력
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
			//찾기 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "찾기");
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
				text(16, 24, "찾기");
			}
			//돌아가기 버튼
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "돌아가기");
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
				text(39, 24, "돌아가기");
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "찾기");
			text(39, 24, "돌아가기");
		}
	}
}

//ID찾기의 확인버튼
void idFindCheck(char* userName, char* birth)
{
	// 마우스 클릭 관련 변수
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
		printf("ID는 %s 입니다.", temps[userNum].ID);
		drawBox(22, 18, 10, 1);
		text(27, 19, "확인");
		while (1)
		{
			ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
			mouseMove(&x, &y);
			if ((22 <= x) && (x <= 32))
			{
				if ((17 <= y) && (y <= 19))
				{
					colorSetSelect();
					text(27, 19, "확인");
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
						text(27, 19, "확인");
					}
				}
				else
				{
					colorSetRestore();
					text(27, 19, "확인");
				}
			}
		}
	}
	else
	{
		text(20, 27, "일치하는 정보가 없습니다");
	}
	free(temps);
}

//PW초기화 화면
void pwReset()
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int x, y;
	char ID[20] = "\0";
	char userName[10] = "\0";
	char birth[7] = "\0";

	// 가입 창
	text(7, 11, "이름");
	drawBox(17, 10, 25, 1);
	text(7, 14, "아이디");
	drawBox(17, 13, 25, 1);
	text(7, 17, "생년월일");
	text(7, 18, "(YYMMDD)");
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(15, 24, "초기화");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//이름 입력
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
			//아이디 입력
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
			//생년월일입력
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
			//초기화 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(15, 24, "초기화");
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
				text(15, 24, "초기화");
			}
			//돌아가기 버튼
			if ((36 <= x) && (x <= 48))
			{
				colorSetSelect();
				text(39, 24, "돌아가기");
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
				text(39, 24, "돌아가기");
			}
		}
		else
		{
			colorSetRestore();
			text(15, 24, "초기화");
			text(39, 24, "돌아가기");
		}
	}
}

//PW초기화 창의 초기화 버튼
void pwResetCheck(char* userName, char* ID, char* birth)
{
	// 마우스 클릭 관련 변수
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
		text(10, 12, "새 PW 입력");
		drawBox(23, 11, 25, 1);
		drawBox(22, 18, 10, 1);
		text(27, 19, "확인");
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
					text(27, 19, "확인");
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
									text(19, 12, "PW가 초기화되었습니다.");
									strcpy(temps[userNum].PW, rePW);
									userInfoFileReWrite(temps, size);
									button = 1;
									drawBox(22, 18, 10, 1);
									text(27, 19, "확인");
								}
								else
								{
									colorSetRestore();
									text(19, 17, "유효하지 않은 PW입니다.");
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
						text(27, 19, "확인");
					}
				}
				else
				{
					colorSetRestore();
					text(27, 19, "확인");
				}
			}
		}
	}
	else
	{
		text(20, 27, "일치하는 정보가 없습니다");
	}
	free(temps);
}

//가게 등록
void newRest(char* _ID, bool regist)
{
	// 마우스 클릭 관련 변수
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

	// 가게등록 창
	text(7, 8, "가게이름");
	drawBox(17, 7, 25, 1);
	text(7, 11, "가게위치");
	drawBox(17, 10, 25, 1);
	text(7, 14, "영업시간");
	drawBox(17, 13, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "등록");
	//일반 등록일 경우
	if (regist == FALSE)
	{
		drawBox(37, 23, 10, 1);
		text(39, 24, "돌아가기");
	}

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//가게이름 입력
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
			//가게위치 입력
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
			//영업시간 입력
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
			//등록 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(16, 24, "등록");
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
				text(16, 24, "등록");
			}
			//일반 등록일 경우
			if (regist == FALSE)
			{
				//돌아가기 버튼
				if ((36 <= x) && (x <= 48))
				{
					colorSetSelect();
					text(39, 24, "돌아가기");
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
					text(39, 24, "돌아가기");
				}
			}
		}
		else
		{
			colorSetRestore();
			text(16, 24, "등록");
			//일반 등록일 경우
			if (regist == FALSE)
			{
				text(39, 24, "돌아가기");
			}
		}
	}
}

//가게정보 파일에 입력
void newRestInput(char* ID, char* restName, char* loc, char* bHours, bool regist)
{
	// 마우스 클릭 관련 변수
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
				text(14, 12, "가게 등록이 완료되었습니다.");
				drawBox(19, 18, 10, 1);
				text(24, 19, "확인");
				while (1)
				{
					ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
					mouseMove(&x, &y);
					if ((19 <= x) && (x <= 29))
					{
						if ((17 <= y) && (y <= 19))
						{
							colorSetSelect();
							text(24, 19, "확인");
							if (mmval.rec.EventType == MOUSE_EVENT)
							{
								if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
								{
									clearConsole();
									colorSetRestore();
									text(24, 19, "       ");
									text(35, 20, "          ");
									//가입 화면에서 넘어왔을 경우
									if (regist == TRUE)
									{
										title();
									}
									//일반 등록일 경우
								}
							}
						}
						else
						{
							colorSetRestore();
							text(24, 19, "확인");
						}
					}
					else
					{
						colorSetRestore();
						text(24, 19, "확인");
					}
				}
			}
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "영업시간이 입력되지 않았습니다.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "가게위치가 입력되지 않았습니다.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "가게이름이 입력되지 않았습니다.");
	}
}
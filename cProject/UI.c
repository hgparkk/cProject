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
							newRest(resUser, TRUE);
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
		text(20, 27, "비밀번호가 다릅니다");
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

	//유저정보 파일 읽기
	temps = userInfoFileRead(&size);

	//입력한 정보가 유저정보와 일치하는지 탐색
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

	//일치하면 아이디 보여주기
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
	//유저정보 파일 읽기
	temps = userInfoFileRead(&size);

	//입력한 정보와 유저정보가 일치하는지 탐색
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

	//일치하면 새 PW를 받아 저장시키기
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

//메인화면
void showMain(User user)
{
	// 마우스 클릭 관련 변수
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

	//고객 메인 창
	if (user.owner == 0)
	{
		int restSize = 0;
		int reviewSize = 0;

		int restCheck = 0;
		int reviewCheck = 0;

		drawBox(10, 2, 40, 3);
		drawBox(10, 7, 40, 3);
		drawBox(10, 12, 40, 3);

		text(3, 19, "★ = 지나가다 있으면 편하게 식사할 수 있는 가게 (접근성)");
		text(3, 20, "● = 남에게 추천해줄만한 호불호 없는 요리의 가게 (요리)");
		text(3, 21, "◆ = 저렴한 가격 대비 만족도가 높은 가게 (가격)");

		drawBox(10, 23, 11, 1);
		text(12, 24, "새맛집등록");
		drawBox(24, 23, 10, 1);
		text(27, 24, "맛집정렬");
		drawBox(37, 23, 13, 1);
		text(39, 24, "회원정보수정");

		//파일에서 가게정보와 리뷰정보 읽기
		Rest* curRest = restInfoFileRead(&restSize);
		Review* curReview = reviewFileRead(&reviewSize);

		//리뷰정보와 가게정보 비교하여 리스트 사이즈 정하기
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

		//리뷰정보와 가게정보를 리스트에 넣기
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
	//가게주인 메인 창
	else
	{
		int restSize = 0;
		int restCheck = 0;

		drawBox(10, 2, 40, 3);
		drawBox(10, 7, 40, 3);
		drawBox(10, 12, 40, 3);

		drawBox(24, 23, 10, 1);
		text(27, 24, "가게등록");

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
		//유저에게 보여줄 화면
		if (user.owner == 0)
		{
			if (restListSize == 0)
			{
				colorSetRestore();
				text(12, 4, "등록된 맛집이 없습니다.");
			}
			else
			{
				colorSetRestore();
				text(12, 4, restList[i].rest.restName);
				if ((restList[i].review.repu / 100) == 1)
				{
					text(12, 5, "★");
				}
				if (((restList[i].review.repu % 100) / 10) == 1)
				{
					text(13, 5, "●");
				}
				if ((restList[i].review.repu % 10) == 1)
				{
					text(14, 5, "◆");
				}
				if (restListSize >= 2)
				{
					text(12, 9, restList[i + 1].rest.restName);
					if ((restList[i + 1].review.repu / 100) == 1)
					{
						text(12, 9, "★");
					}
					if (((restList[i + 1].review.repu % 100) / 10) == 1)
					{
						text(13, 6, "●");
					}
					if ((restList[i + 1].review.repu % 10) == 1)
					{
						text(14, 7, "◆");
					}
				}
				if (restListSize >= 3)
				{
					text(12, 14, restList[i + 2].rest.restName);
					if ((restList[i + 2].review.repu / 100) == 1)
					{
						text(12, 14, "★");
					}
					if (((restList[i + 2].review.repu % 100) / 10) == 1)
					{
						text(13, 14, "●");
					}
					if ((restList[i + 2].review.repu % 10) == 1)
					{
						text(14, 14, "◆");
					}
				}
			}
		}
		else
		{
			if (ownersRestSize == 0)
			{
				colorSetRestore();
				text(12, 4, "(이것은 오류입니다.)");
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
		// 마우스 이동과 클릭시 처리
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
							// 스크롤 방향 확인
							short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

							//마우스 위로 스크롤 됨
							if (wheelDelta > 0)
							{
								if ((restListSize > 3) && (0 < i))
								{
									i--;
								}
							}
							//마우스 아래로 스크롤 됨
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
							// 스크롤 방향 확인
							short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

							//마우스 위로 스크롤 됨
							if (wheelDelta > 0)
							{
								if ((ownersRestSize > 3) && (0 < i))
								{
									i--;
								}
							}
							//마우스 아래로 스크롤 됨
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
			//새맛집등록 버튼
			if ((9 <= x) && (x <= 24))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(12, 24, "새맛집등록");
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
					text(12, 24, "새맛집등록");
				}
			}
			//맛집정렬 버튼과 가게등록 버튼
			if ((25 <= x) && (x <= 36))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(27, 24, "맛집정렬");
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
					text(27, 24, "가게등록");
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
					text(27, 24, "맛집정렬");
				}
				else
				{
					colorSetRestore();
					text(27, 24, "가게등록");
				}
			}
			//회원정보수정 버튼
			if ((36 <= x) && (x <= 52))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(39, 24, "회원정보수정");
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
					text(39, 24, "회원정보수정");
				}
			}
		}
		else
		{
			if (user.owner == 0)
			{
				colorSetRestore();
				text(12, 24, "새맛집등록");
				text(27, 24, "맛집정렬");
				text(39, 24, "회원정보수정");
			}
			else
			{
				colorSetRestore();
				text(27, 24, "가게등록");
			}
		}
	}
}

//가게등록 화면
void newRest(User user, bool regist)
{
	// 마우스 클릭 관련 변수
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
						textInput(19, 8, restName, FALSE);
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
						textInput(19, 11, loc, FALSE);
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
						textInput(19, 14, bHours, FALSE);
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
						newRestInput(user, restName, loc, bHours, tempregist);
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
							showMain(user);
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
void newRestInput(User user, char* restName, char* loc, char* bHours, bool regist)
{
	// 마우스 클릭 관련 변수
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

//새맛집등록 화면
void newFavRest(User user)
{
	// 마우스 클릭 관련 변수
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

	// 가게등록 창
	text(7, 4, "가게이름");
	drawBox(17, 3, 30, 1);
	text(7, 7, "평점");

	text(19, 7, "★");
	text(22, 7, "●");
	text(25, 7, "◆");

	text(27, 7, "(원하는 평점을 클릭)");

	text(3, 10, "★ = 지나가다 있으면 편하게 식사할 수 있는 가게 (접근성)");
	text(3, 11, "● = 남에게 추천해줄만한 호불호 없는 요리의 가게 (요리)");
	text(3, 12, "◆ = 저렴한 가격 대비 만족도가 높은 가게 (가격)");

	text(7, 15, "리뷰");
	drawBox(17, 14, 30, 7);

	drawBox(25, 23, 10, 1);
	text(30, 24, "등록");

	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 52))
		{
			//가게이름 입력
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
			//평점
			if ((6 <= y) && (y <= 8))
			{
				//별
				if ((18 <= x) && (x <= 20))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu / 100) == 0)
							{
								colorSetSelect();
								text(19, 7, "★");
								repu += 100;
							}
							else
							{
								colorSetRestore();
								text(19, 7, "★");
								repu -= 100;
							}
						}
					}
				}
				//원
				if ((21 <= x) && (x <= 23))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu % 100) / 10 == 0)
							{
								colorSetSelect();
								text(22, 7, "●");
								repu += 10;
							}
							else
							{
								colorSetRestore();
								text(22, 7, "●");
								repu -= 10;
							}
						}
					}
				}
				//마름모
				if ((24 <= x) && (x <= 26))
				{
					if (mmval.rec.EventType == MOUSE_EVENT)
					{
						if (mmval.rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							if ((repu % 10) == 0)
							{
								colorSetSelect();
								text(25, 7, "◆");
								repu += 1;
							}
							else
							{
								colorSetRestore();
								text(25, 7, "◆");
								repu -= 1;
							}
						}
					}
				}
			}
			//리뷰 입력
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
			//등록 버튼
			if ((24 <= x) && (x <= 36))
			{
				colorSetSelect();
				text(30, 24, "등록");
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
				text(30, 24, "등록");
			}
		}
		else
		{
			colorSetRestore();
			text(30, 24, "등록");
		}
	}
}
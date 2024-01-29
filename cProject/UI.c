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
	drawBox(17, 10, 20, 1);
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
		colorSetRestore();
		text(7, 11, "아이디");
		text(7, 17, "비밀번호");
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

	char userName[12] = "\0";
	char ID[20] = "\0";
	char PW[20] = "\0";
	char birth[8] = "\0";

	// 가입 창
	drawBox(17, 7, 25, 1);
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);
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
		colorSetRestore();
		text(7, 8, "이름");
		text(7, 11, "아이디");
		text(7, 14, "비밀번호");
		text(7, 17, "생년월일");
		text(7, 18, "(YYMMDD)");
		text(7, 20, "가게 주인 이십니까?");
		text(7, 21, "(가게 주인은 가입시 가게 하나 필수 등록)");
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
		colorSetRestore();
		clearConsole();
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
	char userName[12] = "\0";
	char birth[8] = "\0";

	// ID찾기 창
	drawBox(17, 7, 25, 1);
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(16, 24, "찾기");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		colorSetRestore();
		text(7, 8, "이름");
		text(7, 17, "생년월일");
		text(7, 18, "(YYMMDD)");
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
							colorSetRestore();
							clearConsole();
							text(27, 19, "       ");
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
	char userName[12] = "\0";
	char birth[8] = "\0";

	// 가입 창
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);

	drawBox(11, 23, 10, 1);
	text(15, 24, "초기화");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		colorSetRestore();
		text(7, 11, "이름");
		text(7, 14, "아이디");
		text(7, 17, "생년월일");
		text(7, 18, "(YYMMDD)");
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

	drawBox(10, 2, 40, 3);
	drawBox(10, 7, 40, 3);
	drawBox(10, 12, 40, 3);

	//고객 메인 창
	if (user.owner == 0)
	{
		int restSize = 0;
		int reviewSize = 0;

		int restCheck = 0;
		int reviewCheck = 0;

		drawBox(10, 23, 11, 1);
		text(12, 24, "새맛집등록");
		drawBox(23, 23, 13, 1);
		text(25, 24, "회원정보수정");
		drawBox(38, 23, 10, 1);
		text(40, 24, "맛집정렬");
		drawBox(10, 26, 11, 1);
		text(13, 27, "로그아웃");

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
		free(curRest);
		free(curReview);
	}
	//가게주인 메인 창
	else
	{
		int restSize = 0;
		int restCheck = 0;

		drawBox(10, 23, 11, 1);
		text(12, 24, "가게등록");
		drawBox(23, 23, 13, 1);
		text(25, 24, "회원정보수정");
		drawBox(38, 23, 12, 1);
		text(40, 24, "로그아웃");

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
		//유저에게 보여줄 화면
		if (user.owner == 0)
		{
			colorSetRestore();
			text(3, 19, "★ = 지나가다 있으면 편하게 식사할 수 있는 가게 (접근성)");
			text(3, 20, "● = 남에게 추천해줄만한 호불호 없는 요리의 가게 (요리)");
			text(3, 21, "◆ = 저렴한 가격 대비 만족도가 높은 가게 (가격)");
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
					text(14, 5, "●");
				}
				if ((restList[i].review.repu % 10) == 1)
				{
					text(16, 5, "◆");
				}
				if (restListSize >= 2)
				{
					text(12, 9, restList[i + 1].rest.restName);
					if ((restList[i + 1].review.repu / 100) == 1)
					{
						text(12, 10, "★");
					}
					if (((restList[i + 1].review.repu % 100) / 10) == 1)
					{
						text(14, 10, "●");
					}
					if ((restList[i + 1].review.repu % 10) == 1)
					{
						text(16, 10, "◆");
					}
				}
				if (restListSize >= 3)
				{
					text(12, 14, restList[i + 2].rest.restName);
					if ((restList[i + 2].review.repu / 100) == 1)
					{
						text(12, 15, "★");
					}
					if (((restList[i + 2].review.repu % 100) / 10) == 1)
					{
						text(14, 15, "●");
					}
					if ((restList[i + 2].review.repu % 10) == 1)
					{
						text(16, 15, "◆");
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
									text(12, 4, "                ");
									text(12, 9, "                ");
									text(12, 14, "                ");
									text(12, 5, "                ");
									text(12, 10, "                ");
									text(12, 15, "                ");
									i--;
								}
							}
							//마우스 아래로 스크롤 됨
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
							// 스크롤 방향 확인
							short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

							//마우스 위로 스크롤 됨
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
							//마우스 아래로 스크롤 됨
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
			//새맛집등록 버튼과 가게등록 버튼
			if ((9 <= x) && (x <= 22))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(12, 24, "새맛집등록");
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
					text(12, 24, "가게등록");
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
					text(12, 24, "새맛집등록");
				}
				else
				{
					colorSetRestore();
					text(12, 24, "가게등록");
				}
			}
			//회원정보수정 버튼
			if ((23 <= x) && (x <= 36))
			{
				colorSetSelect();
				text(25, 24, "회원정보수정");
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
				text(25, 24, "회원정보수정");
			}
			//맛집정렬 버튼과 가게주인의 로그아웃 버튼
			if ((37 <= x) && (x <= 51))
			{
				if (user.owner == 0)
				{
					colorSetSelect();
					text(40, 24, "맛집정렬");
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
					text(40, 24, "로그아웃");
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
					text(40, 24, "맛집정렬");
				}
				else
				{
					colorSetRestore();
					text(40, 24, "로그아웃");
				}
			}
		}
		else
		{
			if (user.owner == 0)
			{
				colorSetRestore();
				text(12, 24, "새맛집등록");
				text(25, 24, "회원정보수정");
				text(40, 24, "맛집정렬");
			}
			else
			{
				colorSetRestore();
				text(12, 24, "가게등록");
				text(25, 24, "회원정보수정");
				text(40, 24, "로그아웃");
			}
		}
		//일반고객의 로그아웃 버튼
		if (user.owner == 0)
		{
			if ((25 <= y) && (y <= 27))
			{
				if ((9 <= x) && (x <= 22))
				{
					colorSetSelect();
					text(13, 27, "로그아웃");
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
					text(13, 27, "로그아웃");
				}
			}
			else
			{
				colorSetRestore();
				text(13, 27, "로그아웃");
			}
		}
	}
	free(restList);
	free(ownersRest);
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
	drawBox(17, 7, 25, 1);
	drawBox(17, 10, 25, 1);
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
		colorSetRestore();
		text(7, 8, "가게이름");
		text(7, 11, "가게위치");
		text(7, 14, "영업시간");
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
	char code[28] = "\0";

	//가입화면에서 넘어왔을 경우
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
									//가입 화면에서 넘어왔을 경우
									if (regist == TRUE)
									{
										title();
									}
									//일반 등록일 경우
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
				text(20, 27, "유효하지 않은 영업시간입니다.");
			}
		}
		else
		{
			text(20, 27, "                                      ");
			text(20, 27, "유효하지 않은 가게위치입니다.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "유효하지 않은 가게이름입니다.");
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
	char* usersReview = (char*)calloc(300, sizeof(char));

	// 가게등록 창
	drawBox(17, 3, 30, 1);

	text(19, 7, "★");
	text(22, 7, "●");
	text(25, 7, "◆");

	drawBox(17, 14, 30, 7);

	drawBox(10, 23, 11, 1);
	text(12, 24, "가게등록");
	drawBox(37, 23, 11, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		colorSetRestore();
		text(7, 4, "가게이름");
		text(7, 7, "평점");

		text(27, 7, "(원하는 평점을 클릭)");

		text(7, 15, "리뷰");

		text(3, 10, "★ = 지나가다 있으면 편하게 식사할 수 있는 가게 (접근성)");
		text(3, 11, "● = 남에게 추천해줄만한 호불호 없는 요리의 가게 (요리)");
		text(3, 12, "◆ = 저렴한 가격 대비 만족도가 높은 가게 (가격)");
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
						textInput2(19, 15, usersReview);
					}
				}
			}
		}
		if ((22 <= y) && (y <= 24))
		{
			//등록 버튼
			if ((9 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(12, 24, "가게등록");
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
				text(12, 24, "가게등록");
			}
			//돌아가기 버튼
			if ((36 <= x) && (x <= 49))
			{
				colorSetSelect();
				text(39, 24, "돌아가기");
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
				text(39, 24, "돌아가기");
			}
		}
		else
		{
			colorSetRestore();
			text(12, 24, "가게등록");
			colorSetRestore();
			text(39, 24, "돌아가기");
		}
	}
	free(usersReview);
}

//맛집정보 파일에 입력
void newFavRestInput(User user, char* restName, int repu, char* usersReview)
{
	// 마우스 클릭 관련 변수
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

	//파일에서 가게정보 읽기
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

	//중복되는 이름을 가진 가게들을 리스트에 저장
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
		//입력한 가게가 없을 경우
		dupCase = 1;
	}
	else if (dupRestListSize == 1)
	{
		//입력한 가게가 중복되지 않을 경우
		dupCase = 2;
	}
	else
	{
		//입력한 가게가 중복될 경우
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
					text(14, 12, "맛집 등록이 완료되었습니다.");
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
										text(24, 19, "          ");
										showMain(user);
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
					text(20, 27, "이미 맛집으로 등록된 가게입니다");
				}
			}
			else if (dupCase == 1)
			{
				text(20, 27, "                                      ");
				text(20, 27, "등록되지 않은 가게입니다.");
			}
			else
			{
				drawBox(6, 1, 48, 20);
				drawBox(10, 2, 40, 3);
				drawBox(10, 7, 40, 3);
				drawBox(10, 12, 40, 3);

				text(12, 19, "위 목록에서 해당되는 가게를 골라주세요");

				while (1)
				{
					//유저에게 보여줄 화면
					if (dupRestListSize == 0)
					{
						colorSetRestore();
						text(12, 4, "(이것은 오류입니다.)");
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
									// 스크롤 방향 확인
									short wheelDelta = HIWORD(mmval.rec.Event.MouseEvent.dwButtonState);

									//마우스 위로 스크롤 됨
									if (wheelDelta > 0)
									{
										if ((dupRestListSize > 3) && (0 < i))
										{
											i--;
										}
									}
									//마우스 아래로 스크롤 됨
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
			text(20, 27, "유효하지 않은 리뷰입니다.");
		}
	}
	else
	{
		text(20, 27, "                                      ");
		text(20, 27, "평점마크를 하나라도 선택해야 합니다.");
	}
	free(restList);
	free(restOwnerList);
}

//맛집정보 파일에 입력할때 중복되는 가게에 대한 처리
void newFavRestInputDupThree(Review review, User user)
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	if (isValidRest(review.code, user.ID))
	{
		reviewFileWrite(review);
		drawBox(10, 10, 30, 10);
		text(14, 12, "맛집 등록이 완료되었습니다.");
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
							text(24, 19, "         ");
							showMain(user);
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
		drawBox(10, 10, 30, 10);
		text(14, 12, "이미 등록된 맛집입니다.");
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
							text(24, 19, "         ");
							newFavRest(user);
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
}

//회원정보수정 화면
void userInfoReset(User user)
{
	// 마우스 클릭 관련 변수
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

	// 가입 창
	drawBox(17, 10, 25, 1);
	drawBox(17, 13, 25, 1);
	drawBox(17, 16, 25, 1);

	text(19, 11, userName);
	text(19, 14, PWstar);
	text(19, 17, birth);

	drawBox(11, 23, 10, 1);
	text(14, 24, "정보수정");
	drawBox(24, 23, 10, 1);
	text(27, 24, "회원탈퇴");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

	while (1)
	{
		colorSetRestore();
		text(7, 11, "이름");
		text(7, 14, "비밀번호");
		text(7, 17, "생년월일");
		text(7, 18, "(YYMMDD)");
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((19 <= x) && (x <= 42))
		{
			//이름입력
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
		if ((22 <= y) && (y <= 24))
		{
			//정보수정 버튼
			if ((10 <= x) && (x <= 24))
			{
				colorSetSelect();
				text(14, 24, "정보수정");
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
				text(14, 24, "정보수정");
			}
			//회원탈퇴 버튼
			if ((23 <= x) && (x <= 35))
			{
				colorSetSelect();
				text(27, 24, "회원탈퇴");
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
				text(27, 24, "회원탈퇴");
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
				text(39, 24, "돌아가기");
			}
		}
		else
		{
			colorSetRestore();
			text(14, 24, "정보수정");
			text(27, 24, "회원탈퇴");
			text(39, 24, "돌아가기");
		}
	}
}

//수정된 정보 파일에 넣기
void userInfoResetInput(User user, char* userName, char* PW, char* birth)
{
	// 마우스 클릭 관련 변수
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
				text(18, 12, "회원정보가 수정되었습니다");
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
									showMain(user);
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
			else
			{
				text(20, 27, "                                      ");
				text(20, 27, "유효하지 않은 생년월일 입니다.");
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
		text(20, 27, "유효하지 않은 이름 입니다.");
	}
}

//회원탈퇴하기
void userResign(User user)
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y;

	drawBox(9, 10, 38, 10);
	text(18, 12, "정말 탈퇴하시겠습니까?");
	if (user.owner == 1)
	{
		text(12, 13, "(탈퇴 시 등록된 가게가 삭제됩니다.)");
	}
	drawBox(18, 18, 8, 1);
	text(21, 19, "확인");
	drawBox(31, 18, 8, 1);
	text(34, 19, "취소");
	while (1)
	{
		ReadConsoleInput(mmval.hIn, &mmval.rec, 1, &mmval.dwNOER);
		mouseMove(&x, &y);
		if ((17 <= y) && (y <= 19))
		{
			if ((17 <= x) && (x <= 27))
			{
				colorSetSelect();
				text(21, 19, "확인");
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
				text(21, 19, "확인");
			}
			if ((30 <= x) && (x <= 40))
			{
				colorSetSelect();
				text(34, 19, "취소");
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
				text(34, 19, "취소");
			}
		}
		else
		{
			colorSetRestore();
			text(21, 19, "확인");
			text(34, 19, "취소");
		}
	}
}

//회원탈퇴확인
void userResignCheck(User user)
{
	// 마우스 클릭 관련 변수
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

	//가게주인일경우 삭제할 가게와 리뷰를 배열에 저장한다.
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

	//파일에서 해당 유저 지우기
	for (int i = resignID; i < userSize; i++)
	{
		tempsUser[i] = tempsUser[i + 1];
	}
	realloc(tempsUser, sizeof(User) * (userSize - 1));
	userInfoFileReWrite(tempsUser,userSize-1);

	if (user.owner == 1)
	{
		//파일에서 해당 가게 지우기
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

		//파일에서 해당 리뷰 지우기
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
	text(18, 12, "회원이 탈퇴되었습니다.");
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
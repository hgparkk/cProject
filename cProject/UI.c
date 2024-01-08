#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "TUIfunc.h"
#include "Global.h"
#define _CRT_SECURE_NO_WARNINGS

void title();
void registers();

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
						textInput(19, 11, ID, 0);
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
						textInput(19, 17, PW, 1);
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
						text(0, 1, "로그인 버튼 입니다");
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
						registers();
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
						text(0, 1, "ID 찾기입니다");
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
						text(0, 1, "PW 초기화입니다");
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
void registers()
{
	// 마우스 클릭 관련 변수
	Mouse mmval;
	mmval.hIn = GetStdHandle(STD_INPUT_HANDLE);
	mmval.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(mmval.hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	int x, y, owner;

	char ID[20] = "\0";
	char PW[20] = "\0";

	// 가입 창
	text(7, 11, "아이디");
	drawBox(17, 10, 25, 1);
	text(7, 14, "비밀번호");
	drawBox(17, 13, 25, 1);
	text(7, 17, "가게 주인 이십니까?");
	text(35, 17, "예");
	text(38, 17, "아니오");

	drawBox(11, 23, 10, 1);
	text(16, 24, "가입");
	drawBox(37, 23, 10, 1);
	text(39, 24, "돌아가기");

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
						text(38, 17, "아니오");
						colorSetSelect();
						text(35, 17, "예");
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
						text(35, 17, "예");
						colorSetSelect();
						text(38, 17, "아니오");
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
						text(16, 26, "가입하기 버튼입니다.");
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
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "TUI.h"

void MouseClick(int* x, int* y)
{
	HANDLE       hIn, hOut;
	DWORD        dwNOER;
	INPUT_RECORD rec;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	while (TRUE) {
		ReadConsoleInput(hIn, &rec, 1, &dwNOER);

		if (rec.EventType == MOUSE_EVENT) {
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				*x = rec.Event.MouseEvent.dwMousePosition.X;
				*y = rec.Event.MouseEvent.dwMousePosition.Y;
				return;
			}
		}
	}
}

int main()
{
	int x, y;

	printf("³¡³»±â");

	while (1) {
		MouseClick(&x, &y);
		if (y == 0) {
			if (x < 6) break;
		}
		gotoxy(0, 1);
		printf("%2d, %2d\n", x, y);
	}
}
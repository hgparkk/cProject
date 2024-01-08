typedef struct mouse {
	HANDLE hIn, hOut;
	DWORD dwNOER;
	INPUT_RECORD rec;
}Mouse;
void setConsole();
void gotoxy(int x, int y);
void text(int x, int y, char text[]);
void mouseMove(int* x, int* y);
void colorSetSelect();
void colorSetRestore();
void textInput(int x, int y, char* text, int pw);
void drawBox(int x, int y, int width, int height);
void clearConsole();
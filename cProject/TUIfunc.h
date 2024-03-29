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
void textInput(int x, int y, char* text, bool pw);
void textInput2(int x, int y, char* text);
void newCode(char* code, char* ID, int num);
void drawBox(int x, int y, int width, int height);
void clearConsole();
void textOutput(int x, int y, char* text);
#include <stdbool.h>

//유저 구조체
typedef struct user
{
	char ID[20];
	char PW[20];
	char userName[12];
	char birth[8];
	int owner;
}User;

//가게 구조체
typedef struct rest
{
	char code[28];
	char ID[20];
	char restName[40];
	char loc[60];
	char bHours[60];
}Rest;

//메뉴 구조체
typedef struct menu
{
	char code[28];
	char menuName[40];
	int price;
}Menu;

//리뷰 구조체
typedef struct review
{
	char ID[20];
	char code[28];
	int repu;
	char review[];
}Review;

typedef struct restList
{
	Rest rest;
	Review review;
}RestList;

void userInfoFileWrite(User user);
void userInfoFileReWrite(User* user, int size);
User* userInfoFileRead(int* _size);

void restInfoFileWrite(Rest rest);
Rest* restInfoFileRead(int* _size);

void menuFileWrite(Menu menu);
Menu* menuFileRead(int* _size);

void reviewFileWrite(Review review);
Review* reviewFileRead(int* _size);

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
	char usersReview[304];
	int repu;
}Review;

typedef struct restList
{
	Rest rest;
	Review review;
}RestList;

typedef struct favListArray
{
	RestList* restList;
	int size;
}FavListArray;

typedef struct restOwnerArray
{
	Rest* ownersRest;
	int size;
}RestListArray;

typedef struct reviewArray
{
	Review* review;
	int size;
}ReviewArray;

typedef struct restOwner
{
	Rest rest;
	User user;
}RestOwner;

void userInfoFileWrite(User user);
void userInfoFileReWrite(User user, int seek);
User* userInfoFileRead(int* _size);
void userInfoFileDeleteLine(int seek);

void restInfoFileWrite(Rest rest);
void restInfoFileReWrite(Rest rest, int seek);
Rest* restInfoFileRead(int* _size);
void restInfoFileDeleteLine(int seek);

void menuFileWrite(Menu menu);
Menu* menuFileRead(int* _size);

void reviewFileWrite(Review review);
void reviewFileReWrite(Review review, int seek);
Review* reviewFileRead(int* _size);
void reviewFileDeleteLine(int seek);
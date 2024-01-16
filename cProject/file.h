#include <stdbool.h>
#include <time.h>

//유저 구조체
typedef struct user
{
	char ID[20];
	char PW[20];
	char userName[10];
	char birth[7];
	int owner;
}User;

//가게 구조체
typedef struct rest
{
	char ID[20];
	char* restName;
	char* loc;
	char* bHours;
}Rest;

//메뉴 구조체
typedef struct menu
{
	char* restName;
	char* menuName;
	int price;
}Menu;

//리뷰 구조체
typedef struct review
{
	char ID[20];
	char* restName;
	char repu[4];
	char* review;
	struct tm* cTime;
}Review;

void userInfoFileWrite(User user);
void userInfoFileReWrite(User* user, int size);
User* userInfoFileRead(int* _size);

void restInfoFileWrite(Rest rest);

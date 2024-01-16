#include <stdbool.h>
#include <time.h>

//���� ����ü
typedef struct user
{
	char ID[20];
	char PW[20];
	char userName[10];
	char birth[7];
	int owner;
}User;

//���� ����ü
typedef struct rest
{
	char ID[20];
	char* restName;
	char* loc;
	char* bHours;
}Rest;

//�޴� ����ü
typedef struct menu
{
	char* restName;
	char* menuName;
	int price;
}Menu;

//���� ����ü
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

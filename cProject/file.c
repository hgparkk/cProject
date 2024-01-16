#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

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

void userInfoFileReWrite(User* user, int size)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "w");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		fprintf(fp, "%s %s %s %s %d\n", user[i].ID, user[i].PW, user[i].userName, user[i].birth, user[i].owner);
	}
	fclose(fp);
}

void userInfoFileWrite(User user)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	if (user.owner == TRUE)
	{
		fprintf(fp, "%s %s %s %s %d\n", user.ID, user.PW, user.userName, user.birth, user.owner);
	}
	else
	{
		fprintf(fp, "%s %s %s %s %d\n", user.ID, user.PW, user.userName, user.birth, user.owner);
	}
	fclose(fp);
}

User* userInfoFileRead(int* _size)
{
	User temp;
	int owner;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %d\n", temp.ID, temp.PW, temp.userName, temp.birth, &owner);
		size++;
	}
	User* temps = (User*)malloc(sizeof(User) * size);
	size = 0;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %d\n", temps[size].ID, temps[size].PW, temps[size].userName, temps[size].birth, &owner);
		if (owner == 0)
		{
			temps[size].owner = FALSE;
		}
		else
		{
			temps[size].owner = TRUE;
		}
		size++;
	}
	fclose(fp);
	*_size = size;
	return temps;
}

void restInfoFileWrite(Rest rest)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	fprintf(fp, "%s\n%s\n%s\n%s\n\n",rest.ID, rest.restName, rest.loc, rest.bHours);
	fclose(fp);
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

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
	char usersReview[304];
}Review;

//유저정보 파일 쓰기 (수정)
void userInfoFileReWrite(User* user, int size)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "w");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(fp, "%s %s %s %s %d\n", user[i].ID, user[i].PW, user[i].userName, user[i].birth, user[i].owner);
		}
	}
	fclose(fp);
}

//유저정보 파일 쓰기 (추가)
void userInfoFileWrite(User user)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fprintf(fp, "%s %s %s %s %d\n", user.ID, user.PW, user.userName, user.birth, user.owner);
	}
	fclose(fp);
}

//유저정보 파일 읽기
User* userInfoFileRead(int* _size)
{
	User temp;
	User* temps;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s %d\n", temp.ID, temp.PW, temp.userName, temp.birth, &temp.owner);
			size++;
		}
		temps = (User*)malloc(sizeof(User) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s %d\n", temps[size].ID, temps[size].PW, temps[size].userName, temps[size].birth, &temps[size].owner);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//가게정보 파일 쓰기 (수정)
void restInfoFileReWrite(Rest* rest, int size)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "w");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(fp, "%s %s %s %s %s\n", rest[i].code, rest[i].ID, rest[i].restName, rest[i].loc, rest[i].bHours);
		}
	}
	fclose(fp);
}

//가게정보 파일 쓰기 (추가)
void restInfoFileWrite(Rest rest)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fprintf(fp, "%s %s %s %s %s\n", rest.code, rest.ID, rest.restName, rest.loc, rest.bHours);
	}
	fclose(fp);
}

//가게정보 파일 읽기
Rest* restInfoFileRead(int* _size)
{
	Rest temp;
	Rest* temps;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s %s\n", temp.code, temp.ID, temp.restName, temp.loc, temp.bHours);
			size++;
		}
		temps = (Rest*)malloc(sizeof(Rest) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s %s\n", temps[size].code, temps[size].ID, temps[size].restName, temps[size].loc, temps[size].bHours);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//메뉴정보 파일 쓰기
void menuFileWrite(Menu menu)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\menu.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fprintf(fp, "%s %s %d\n", menu.code, menu.menuName, menu.price);
	}
	fclose(fp);
}

//메뉴정보 파일 읽기
Menu* menuFileRead(int* _size)
{
	Menu temp;
	Menu* temps;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\menu.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d\n", temp.code, temp.menuName, &temp.price);
			size++;
		}
		temps = (Menu*)malloc(sizeof(Menu) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\menu.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d\n", temps[size].code, temps[size].menuName, &temps[size].price);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//리뷰정보 파일 쓰기 (수정)
void reviewFileReWrite(Review* review, int size)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "w");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(fp, "%s %s %d %s\n", review[i].ID, review[i].code, review[i].repu, review[i].usersReview);
		}
	}
	fclose(fp);
}

//리뷰정보 파일 쓰기 (추가)
void reviewFileWrite(Review review)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "a");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		fprintf(fp, "%s %s %d %s\n", review.ID, review.code, review.repu, review.usersReview);
	}
	fclose(fp);
}

//리뷰정보 파일 읽기
Review* reviewFileRead(int* _size)
{
	Review temp;
	Review* temps;
	int size = 0;
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d %s\n", temp.ID, temp.code, &temp.repu, temp.usersReview);
			size++;
		}
		temps = (Review*)malloc(sizeof(Review) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d %s\n", temps[size].ID, temps[size].code, &temps[size].repu, temps[size].usersReview);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}
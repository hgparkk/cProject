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

//유저정보 파일 수정
void userInfoFileReWrite(User user, int seek)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r+");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		if (seek != 0)
		{
			fseek(fp, (sizeof(User) * seek) + 1, SEEK_SET);
		}
		fwrite(&user, sizeof(User), 1, fp);
		fprintf(fp, " ");
	}
	fclose(fp);
}

//유저정보 파일 쓰기
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
		fwrite(&user, sizeof(User),1, fp);
		fprintf(fp,"\n");
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
			fread(&temp, sizeof(User), 1, fp);
			fscanf(fp, "\n");
			size++;
		}
		temps = (User*)malloc(sizeof(User) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");
		while (!feof(fp))
		{
			fread(&temps[size], sizeof(User), 1, fp);
			fscanf(fp, "\n");
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//유저정보 삭제
void userInfoFileDeleteLine(int seek) {
	FILE* inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "r");
	FILE* tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "w");

	if (inputFile == NULL || tempFile == NULL) {
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	User temp;
	int currentLine = 0;

	while (!feof(inputFile))
	{
		fread(&temp, sizeof(User), 1, inputFile);
		fscanf(inputFile, "\n");
		if (currentLine != seek)
		{
			fwrite(&temp, sizeof(User), 1, tempFile);
			fprintf(tempFile, "\n");
		}
		currentLine++;
	}

	fclose(inputFile);
	fclose(tempFile);

	inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\userInfo.txt", "w");
	tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "r");

	while (!feof(tempFile))
	{
		fread(&temp, sizeof(User), 1, tempFile);
		fscanf(tempFile, "\n");
		fwrite(&temp, sizeof(User), 1, inputFile);
		fprintf(inputFile, "\n");
	}

	fclose(inputFile);
	fclose(tempFile);
}

//가게정보 파일 수정
void restInfoFileReWrite(Rest rest, int seek)
{
	FILE* fp;
	fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "r+");

	if (fp == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else
	{
		if (seek != 0)
		{
			fseek(fp, (sizeof(Rest) * seek) + 1, SEEK_SET);
		}
		fwrite(&rest, sizeof(Rest), 1, fp);
		fprintf(fp, " ");
	}
	fclose(fp);
}

//가게정보 파일 쓰기
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
		fwrite(&rest, sizeof(Rest), 1, fp);
		fprintf(fp, "\n");
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
			fread(&temp, sizeof(Rest), 1, fp);
			fscanf(fp, "\n");
			size++;
		}
		temps = (Rest*)malloc(sizeof(Rest) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "r");
		while (!feof(fp))
		{
			fread(&temps[size], sizeof(Rest), 1, fp);
			fscanf(fp, "\n");
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//가게정보 삭제
void restInfoFileDeleteLine(int seek) {
	FILE* inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "r");
	FILE* tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "w");

	if (inputFile == NULL || tempFile == NULL) {
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	Rest temp;
	int currentLine = 0;

	while (!feof(inputFile))
	{
		fread(&temp, sizeof(Rest), 1, inputFile);
		fscanf(inputFile, "\n");
		if (currentLine != seek)
		{
			fwrite(&temp, sizeof(Rest), 1, tempFile);
			fprintf(tempFile, "\n");
		}
		currentLine++;
	}

	fclose(inputFile);
	fclose(tempFile);

	inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\restInfo.txt", "w");
	tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "r");

	while (!feof(tempFile))
	{
		fread(&temp, sizeof(Rest), 1, tempFile);
		fscanf(tempFile, "\n");
		fwrite(&temp, sizeof(Rest), 1, inputFile);
		fprintf(inputFile, "\n");
	}

	fclose(inputFile);
	fclose(tempFile);
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
		fwrite(menu.code, sizeof(char), sizeof(menu.code), fp);
		fwrite(menu.menuName, sizeof(char), sizeof(menu.menuName), fp);
		fprintf(fp,"%d\n", menu.price);
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
			fread(temp.code, sizeof(char), sizeof(temp.code), fp);
			fread(temp.menuName, sizeof(char), sizeof(temp.menuName), fp);
			fscanf(fp,"%d\n", temp.price);
			size++;
		}
		temps = (Menu*)malloc(sizeof(Menu) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\menu.txt", "r");
		while (!feof(fp))
		{
			fread(temp.code, sizeof(char), sizeof(temp.code), fp);
			fread(temp.menuName, sizeof(char), sizeof(temp.menuName), fp);
			fscanf(fp,"%d\n", temp.price);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//리뷰정보 파일 수정
void reviewFileReWrite(Review review, int seek)
{
	FILE* inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");
	FILE* tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "w");

	if (inputFile == NULL || tempFile == NULL) {
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	Review temp;
	int currentLine = 0;

	while (fscanf(inputFile, "%s %s %d %[^\n]", temp.ID, temp.code, &temp.repu, temp.usersReview) == 4)
	{
		if (currentLine != seek)
		{
			fprintf(tempFile, "%s %s %d %s\n", temp.ID, temp.code, temp.repu, temp.usersReview);
		}
		else
		{
			fprintf(tempFile, "%s %s %d %s\n", review.ID, review.code, review.repu, review.usersReview);
		}
		currentLine++;
	}

	fclose(inputFile);
	fclose(tempFile);

	inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "w");
	tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "r");

	while (fscanf(tempFile, "%s %s %d %[^\n]", temp.ID, temp.code, &temp.repu, temp.usersReview) == 4)
	{
		fprintf(inputFile, "%s %s %d %s\n", temp.ID, temp.code, temp.repu, temp.usersReview);
	}

	fclose(inputFile);
	fclose(tempFile);
}

//리뷰정보 파일 쓰기
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
			fscanf(fp, "%s %s %d %[^\n]", temp.ID, temp.code, &temp.repu, temp.usersReview);
			size++;
		}
		temps = (Review*)malloc(sizeof(Review) * size);
		size = 0;
		fp = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d %[^\n]", temps[size].ID, temps[size].code, &temps[size].repu, temps[size].usersReview);
			size++;
		}
	}
	fclose(fp);
	*_size = size;
	return temps;
}

//리뷰정보 삭제
void reviewFileDeleteLine(int seek) {
	FILE* inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "r");
	FILE* tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "w");

	if (inputFile == NULL || tempFile == NULL) {
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	Review temp;
	int currentLine = 0;

	while (fscanf(inputFile, "%s %s %d %[^\n]", temp.ID, temp.code, &temp.repu, temp.usersReview) == 4)
	{
		if (currentLine != seek)
		{
			fprintf(tempFile, "%s %s %d %s\n", temp.ID, temp.code, temp.repu, temp.usersReview);
		}
		currentLine++;
	}

	fclose(inputFile);
	fclose(tempFile);

	inputFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\review.txt", "w");
	tempFile = fopen("C:\\Users\\phg2559\\Documents\\cProject\\cProject\\file\\temp.txt", "r");

	while (fscanf(tempFile, "%s %s %d %[^\n]", temp.ID, temp.code, &temp.repu, temp.usersReview) == 4)
	{
		fprintf(inputFile, "%s %s %d %s\n", temp.ID, temp.code, temp.repu, temp.usersReview);
	}

	fclose(inputFile);
	fclose(tempFile);
}
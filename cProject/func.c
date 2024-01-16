#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include "file.h"
#define _CRT_SECURE_NO_WARNINGS

//유효한 ID 검사
int isValidID(const char* ID)
{

	// ID의 길이 검증
	int len = strlen(ID);
	if (len < 4 || len > 20)
	{
		return 0;
	}

	// 첫 글자는 알파벳 소문자여야 함
	if (!islower(ID[0]))
	{
		return 0;
	}

	// 나머지 글자는 알파벳 소문자나 숫자여야 함
	for (int i = 1; i < len; i++)
	{
		if (!islower(ID[i]) && !isdigit(ID[i]))
		{
			return 0;
		}
	}

	return 1;
}

//ID 중복 검사
int isValidID2(const char* ID)
{
	User* temps;
	int size;
	temps = userInfoFileRead(&size);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(temps[i].ID, ID) == 0)
		{
			return 0;
		}
	}
	return 1;
}

//유효한 PW 검사
int isValidPW(const char* PW)
{

	// PW의 길이 검증
	int len = strlen(PW);
	if (len < 8 || len > 20)
	{
		return 0;
	}

	// 첫 글자는 알파벳 소문자여야 함
	if (!islower(PW[0]))
	{
		return 0;
	}

	// 나머지 글자는 알파벳 소문자나 숫자여야 함
	for (int i = 1; i < len; i++)
	{
		if (!islower(PW[i]) && !isdigit(PW[i]))
		{
			return 0;
		}
	}

	return 1;
}

int isKoreanChar(char ch) 
{
	// ASCII 범위 이외의 문자를 한글로 간주
	return (ch < 0 || ch > 127);
}

//유효한 이름 검증 1
int isValidName1(const char* name) 
{
	//이름의 길이 검증
	int len = strlen(name);
	if (len < 2 || len > 10)
	{
		return 0;
	}

	while (*name != '\0') 
	{
		//한글인지 검사
		if (!isKoreanChar(*name)) 
		{
			return 0;
		}
		name++;
	}
	return 1;
}

//유효한 이름 검증 2
int isValidName2(const char* name)
{
	//이름의 길이 검증
	int len = strlen(name);
	if (len < 2 || len > 10)
	{
		return 0;
	}

	while (*name != '\0') {
		// 영어 알파벳인지 검사
		if (!isalpha(*name)) {
			return 0;
		}
		name++;
	}
	return 1;
}

//유효한 생년월일 검증
int isValidBirth(const char* birth)
{

	//생년월일 길이 검증
	int len = strlen(birth);
	if (len != 6)
	{
		return 0;
	}

	//숫자로만 이루어져야 함
	for (int i = 1; i < len; i++)
	{
		if (!isdigit(birth[i]))
		{
			return 0;
		}
	}

	return 1;
}
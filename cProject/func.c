#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include "file.h"
#define _CRT_SECURE_NO_WARNINGS

//��ȿ�� ID �˻�
int isValidID(const char* ID)
{

	// ID�� ���� ����
	int len = strlen(ID);
	if (len < 4 || len > 20)
	{
		return 0;
	}

	// ù ���ڴ� ���ĺ� �ҹ��ڿ��� ��
	if (!islower(ID[0]))
	{
		return 0;
	}

	// ������ ���ڴ� ���ĺ� �ҹ��ڳ� ���ڿ��� ��
	for (int i = 1; i < len; i++)
	{
		if (!islower(ID[i]) && !isdigit(ID[i]))
		{
			return 0;
		}
	}

	return 1;
}

//ID �ߺ� �˻�
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

//��ȿ�� PW �˻�
int isValidPW(const char* PW)
{

	// PW�� ���� ����
	int len = strlen(PW);
	if (len < 8 || len > 20)
	{
		return 0;
	}

	// ù ���ڴ� ���ĺ� �ҹ��ڿ��� ��
	if (!islower(PW[0]))
	{
		return 0;
	}

	// ������ ���ڴ� ���ĺ� �ҹ��ڳ� ���ڿ��� ��
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
	// ASCII ���� �̿��� ���ڸ� �ѱ۷� ����
	return (ch < 0 || ch > 127);
}

//��ȿ�� �̸� ���� 1
int isValidName1(const char* name) 
{
	//�̸��� ���� ����
	int len = strlen(name);
	if (len < 2 || len > 10)
	{
		return 0;
	}

	while (*name != '\0') 
	{
		//�ѱ����� �˻�
		if (!isKoreanChar(*name)) 
		{
			return 0;
		}
		name++;
	}
	return 1;
}

//��ȿ�� �̸� ���� 2
int isValidName2(const char* name)
{
	//�̸��� ���� ����
	int len = strlen(name);
	if (len < 2 || len > 10)
	{
		return 0;
	}

	while (*name != '\0') {
		// ���� ���ĺ����� �˻�
		if (!isalpha(*name)) {
			return 0;
		}
		name++;
	}
	return 1;
}

//��ȿ�� ������� ����
int isValidBirth(const char* birth)
{

	//������� ���� ����
	int len = strlen(birth);
	if (len != 6)
	{
		return 0;
	}

	//���ڷθ� �̷������ ��
	for (int i = 1; i < len; i++)
	{
		if (!isdigit(birth[i]))
		{
			return 0;
		}
	}

	return 1;
}
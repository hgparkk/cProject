#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//int main()
//{
//	char strOldFolder[] = "C:\\Users\\phg2559\\Documents\\cProject\\test\\file\\temp.txt";
//	char strNewFolder[] = "C:\\Users\\phg2559\\Documents\\cProject\\test\\file\\userInfo.txt";
//
//	//�̸��� �ٲٰ� ����� ���� �޴´�.
//	int nResult = rename(strOldFolder, strNewFolder);
//
//	if (nResult == 0)
//	{
//		printf("�̸� ���� ����");
//	}
//	else if (nResult == -1)
//	{
//		perror("�̸� ���� ���� - ");
//	}
//
//	int reMoveResult = remove(strNewFolder);
//	if (nResult == 0)
//	{
//		printf("���� ���� ����");
//	}
//	else if (nResult == -1)
//	{
//		perror("���� ���� ���� - ");
//	}
//
//	return 0;
//}
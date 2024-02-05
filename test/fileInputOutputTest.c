#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//int main()
//{
//	char strOldFolder[] = "C:\\Users\\phg2559\\Documents\\cProject\\test\\file\\temp.txt";
//	char strNewFolder[] = "C:\\Users\\phg2559\\Documents\\cProject\\test\\file\\userInfo.txt";
//
//	//이름을 바꾸고 결과를 리턴 받는다.
//	int nResult = rename(strOldFolder, strNewFolder);
//
//	if (nResult == 0)
//	{
//		printf("이름 변경 성공");
//	}
//	else if (nResult == -1)
//	{
//		perror("이름 변경 실패 - ");
//	}
//
//	int reMoveResult = remove(strNewFolder);
//	if (nResult == 0)
//	{
//		printf("파일 삭제 성공");
//	}
//	else if (nResult == -1)
//	{
//		perror("파일 삭제 실패 - ");
//	}
//
//	return 0;
//}
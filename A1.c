#define _CRT_SECURE_NO_WARNINGS 1

#define MAX_LAYER 10

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<assert.h>

int Layer_Move(int Destination[], int Sourse[], size_t Number)
{
	int i = 0;

	int SumD = 0, SumS = 0;

	if (Destination == Sourse || !Number || !Sourse[0])
	{
		return NULL;
	}
	else {
		printf("%-15s|", "Sourse");
		for (i = 0; i < MAX_LAYER; i++)
		{
			printf("%-3d", Sourse[i]);
		}
		printf("\n");
		printf("%-15s|", "Destination");
		for (i = 0; i < MAX_LAYER; i++)
		{
			printf("%-3d", Destination[i]);
		}
		printf("\n");

		for (i = 0; i < Number; i++)
		{
			if (Destination[i])
			{
				SumD++;
			}
			if (Sourse[i])
			{
				SumS++;
			}
		}
		if (!SumD)
		{
			printf("D-sum %d|S-sum %d\n", SumD, SumS);
			memmove(&Destination[SumD], &Sourse[SumS - 1], sizeof(int));
			memset(&Sourse[SumS - 1], NULL, sizeof(int));
		}
		else if (Destination[SumD - 1] > Sourse[SumS - 1])
		{
			printf("D-sum %d|S-sum %d\n", SumD, SumS);
			memmove(&Destination[SumD], &Sourse[SumS - 1], sizeof(int));
			memset(&Sourse[SumS - 1], NULL, sizeof(int));
		}
		else
		{
			printf("D-sum %d|S-sum %d\n", SumD, SumS);
			printf("||||\n");
		}
		printf("%-15s|", "Sourse");
		for (i = 0; i < MAX_LAYER; i++)
		{
			printf("%-3d", Sourse[i]);
		}
		printf("\n");
		printf("%-15s|", "Destination");
		for (i = 0; i < MAX_LAYER; i++)
		{
			printf("%-3d", Destination[i]);
		}
		printf("\n\n");
		return Destination[SumD];
	}
	return NULL;
}



//int main()
//{
//	int A[MAX_LAYER] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
//	int B[MAX_LAYER] = { 0 };
//	int C[MAX_LAYER] = { 0 };
//
//	int* Arr[] = { A,B,C };
//
//	int i = 0, j = 0;
//	int input = 1;
//
//	char TmpChar1 = 0;
//	char TmpChar2 = 0;
//
//	do{
//		for (i = 0; i < 3; i++)
//		{
//			printf("%-2c|", 'A' + i);
//			for (j = 0; j < MAX_LAYER; j++)
//			{
//				printf("%-3d", Arr[i][j]);
//			}
//			printf("\n\n");
//		}
//
//		scanf("%cto%c", &TmpChar1, &TmpChar2);
//
//		if (TmpChar1 >= 'A' && TmpChar1 <= 'C' && TmpChar2 >= 'A' && TmpChar2 <= 'C')
//		{
//			printf("\nT1:%c T2:%c\n", TmpChar1, TmpChar2);
//			printf("%d\n", Layer_Move(Arr[TmpChar2 - 'A'], Arr[TmpChar1 - 'A'], MAX_LAYER));
//		}
//
//	} while (input);
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS 1

#define MAX_LAYER 3

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<assert.h>

int Layer_Move(int* Destination, int* Sourse, size_t Number)
{
	assert(Destination && Sourse);
	int i = 0;

	int SumD = 0, SumS = 0;

	//目标为源时不操作
	//数组元素个数为0时不操作
	//源为空时不操作
	if (Destination == Sourse || !Number || !Sourse[0])
	{
		return NULL;
	}
	else {
		//转移前
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

		//总计拿到最顶上的元素+1的地址
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
		//转移源柱最顶上的元素
		if (!SumD)
		{				//目标柱没有元素时直接转移
			printf("D-sum %d|S-sum %d\n", SumD, SumS);
			memmove(&Destination[SumD], &Sourse[SumS - 1], sizeof(int));
			memset(&Sourse[SumS - 1], NULL, sizeof(int));
		}
		else if (Destination[SumD - 1] > Sourse[SumS - 1])
		{				//目标柱元素大于源柱元素时转移
			printf("D-sum %d|S-sum %d\n", SumD, SumS);
			memmove(&Destination[SumD], &Sourse[SumS - 1], sizeof(int));
			memset(&Sourse[SumS - 1], NULL, sizeof(int));
		}
		else
		{				//目标柱元素小于源柱时不转移
			printf("||||\n");
		}

		//转移后
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

void Move(int* sourse, int* destination)
{
	Layer_Move(destination, sourse, MAX_LAYER);
}

void Hanoi(int* d1, int* d2, int* d3, size_t Count)
{

	if (Count == 1)
	{
		Move(d1, d3);
	}
	else
	{
		Hanoi(d1, d3, d2, Count - 1);
		Move(d1, d3);
		Hanoi(d2, d1, d3, Count - 1);
	}
}

void Init_Layer_Arr(int* Destination, size_t Count)
{
	int i = 0;
	for (i = 0; i < Count; i++)
	{
		Destination[i] = Count - i;
	}
}

int IsWin(const int* Sourse, size_t Count)
{
	assert(Sourse && Count);
	if (Sourse[Count - 1])
	{
		return 1;		//胜利返回1
	}
	else
	{
		return 0;		//失败返回0
	}
}

//int main()
//{
//	int Arr[3][MAX_LAYER] = { 0 };
//
//	int i = 0, j = 0;
//	int input = 1;
//
//	char TmpChar1 = 0;
//	char TmpChar2 = 0;
//
//	Init_Layer_Arr(Arr[0], MAX_LAYER);
//
//#ifdef AI_
//	{
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
//		Hanoi(Arr[0], Arr[1], Arr[2], MAX_LAYER);
//
//		for (i = 0; i < 3; i++)
//		{
//			printf("%-2c|", 'A' + i);
//			for (j = 0; j < MAX_LAYER; j++)
//			{
//				printf("%-3d", Arr[i][j]);
//			}
//			printf("\n\n");
//		}
//	}
//#else
//	{
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
//		输入合法时传输入移动函数
//		if (TmpChar1 >= 'A' && TmpChar1 <= 'C' && TmpChar2 >= 'A' && TmpChar2 <= 'C')
//		{
//			printf("\nT1:%c T2:%c\n", TmpChar1, TmpChar2);
//			printf("Move:%d\n", Layer_Move(Arr[TmpChar2 - 'A'], Arr[TmpChar1 - 'A'], MAX_LAYER));
//		}
//		input = !IsWin(Arr[2], MAX_LAYER);
//	} while (input);
//	}
//#endif
//	printf("\nYou WIn\n");
//	return 0;
//}
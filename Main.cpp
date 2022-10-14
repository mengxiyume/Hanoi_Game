#define _CRT_SECURE_NO_WARNINGS 1

#define AI

#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<assert.h>
#include<string.h>

#define Window_Width 1920
#define Window_Height 1080

#define Column_Width 50

#define LAYER_NUMBER_MAX 14
#define LAYER_NUMBER 8

typedef struct Layer
{
	float width;
	float height;
	int color;
	int line;
}Layer;

struct Column
{
	int x;
	int y;
	int width;
	int height;
}c1;

typedef struct Choice
{
	unsigned char sourse;
	unsigned char destination;
	bool state;
}Choice;

typedef struct Layer_Arr
{
	char ID;
	Layer* arr[];
}Layer_Arr;

Layer_Arr* InitLayerArr(size_t Number)
{
	assert(Number);
	Layer_Arr* ret = NULL;
	int i = 0;
	ret = (Layer_Arr* )calloc(1, sizeof(Layer_Arr) + sizeof(Layer*) * Number);
	assert(ret);

	for (i = 0; i < Number; i++)
	{
		ret->arr[i] = (Layer*)calloc(1, sizeof(Layer));
		assert(ret->arr[i]);
	}
	return ret;
}

//每一层的初始化
Layer_Arr* GetLayer(size_t Number,Layer_Arr** destination)
{
	assert(destination);
	int i = 0;
	int Layer_Height = Window_Height / 16;
	Layer_Arr* ret = *destination;
	for (i = 0; i < 3; i++)
	{
		int j = 0;
		destination[i] = InitLayerArr(Number);

		if (i == 0)
		{
			destination[i]->ID = 'A' + i;
			for (j = 0; j < Number; j++)
			{
				int L_H = Layer_Height * LAYER_NUMBER_MAX / LAYER_NUMBER;
				int L_W_MAX = Window_Width / 3 / 6 * 5;
				int L_W_MIN = Window_Width / 3 / 6;
				destination[i]->arr[j]->color = 0x5500 + (0xEE11 - 0x5511) / (Number - 1) * j;

				if (LAYER_NUMBER <= LAYER_NUMBER_MAX)
				{
					destination[i]->arr[j]->height = Layer_Height;
				}
				else
				{
					destination[i]->arr[j]->height = L_H;
				}
				destination[i]->arr[j]->width = L_W_MIN + (L_W_MAX - L_W_MIN)
					/ Number * (Number - j);		//每一层的宽度
				destination[i]->arr[j]->line = Number - j;
			}
		}
		else
		{
			destination[i]->ID = 'A' + i;
			*(destination[i]->arr[j]) = { 0 };		//初始化空数组
			//*(name[number]->arr[number])
			// !
			//*name[number]->arr[number]
		}
	}
	return ret;
}

int Layer_Move(Layer_Arr** Arr,size_t destination, size_t sourse,size_t Count)
{

	//memmove(Arr[destination]->arr[i], Tmp_Sourse, sizeof(Layer));
	//memset(Tmp_Sourse, 0, sizeof(Layer));

	static int MoveNumber = 0;

	MoveNumber++;

	assert(Arr);

	int i = 0;
	int SumD = 0, SumS = 0;

	if (destination == sourse || !Count || !Arr[sourse]->arr[0]->line)
	{
		return NULL;
	}
	else
	{
		for (i = 0; i < Count; i++)
		{
			if (Arr[destination]->arr[i]->line)
			{
				SumD++;
			}
			if (Arr[sourse]->arr[i]->line)
			{
				SumS++;
			}
		}
		if (!SumD)
		{
			memmove(Arr[destination]->arr[SumD],
				Arr[sourse]->arr[SumS - 1], sizeof(Layer));;
			memset(Arr[sourse]->arr[SumS - 1], 0, sizeof(Layer));
		}
		else if (Arr[destination]->arr[SumD - 1]->line > Arr[sourse]->arr[SumS - 1]->line)
		{
			memmove(*(Arr[destination]->arr + SumD),
				*(Arr[sourse]->arr + SumS - 1), sizeof(Layer));;
			memset(*(Arr[sourse]->arr + SumS - 1), 0, sizeof(Layer));
		}
		else
		{
			return NULL;
		}
		return MoveNumber;
	}
}

void putLine(Layer_Arr* sourse,size_t Cl)
{
	int n = 0;
	int x, y;
	int L_H = Window_Height / 16;
	if (LAYER_NUMBER > LAYER_NUMBER_MAX)
	{
		L_H = L_H * LAYER_NUMBER_MAX / LAYER_NUMBER;
	}
	y = Window_Height - 2 * Column_Width;
	for (n = 0; n < LAYER_NUMBER; n++)
	{
		if (sourse->arr[n]->line)
		{
			x = Window_Width/3/2+Window_Width / 3 * Cl - sourse->arr[n]->width / 2;
			y -= L_H;
			int tx, ty, tw, th;
			char text[10]; 
			settextstyle(sourse->arr[n]->height, 0, _T("宋体"));
			setfillcolor(sourse->arr[n]->color);
			fillrectangle(x, y,
				x + sourse->arr[n]->width,
				y + sourse->arr[n]->height);
			sprintf(text, "%d", sourse->arr[n]->line);
			tw = textwidth(text);
			th = textheight(text);
			tx = x + sourse->arr[n]->width / 2 - tw / 2;
			ty = y + sourse->arr[n]->height / 2 - th / 2;
			outtextxy(tx, ty, text);
		}
	}

}

bool IsWin(const Layer_Arr* Sourse, size_t Count)
{
	int i = 0;
	if (Sourse->arr[Count - 1]->line == 1)
	{
		return true;
	}
	return false;
}

bool eaeryPut(int mouseC, const Choice* choice, Layer_Arr** Arr, bool Win)
{
	int n = 0;
	cleardevice();

	if (mouseC)
	{
		setfillcolor(0xF6FFC6);
		fillrectangle(Window_Width / 3 * (mouseC - 1), 0, Window_Width / 3 * mouseC, Window_Height);
	}
	if (choice->sourse)
	{
		setfillcolor(0xB6BBA6);
		fillrectangle(Window_Width / 3 * (choice->sourse - 1), 0, Window_Width / 3 * choice->sourse, Window_Height);
	}
	if (choice->destination)
	{
		setfillcolor(0x7777CC);
		fillrectangle(Window_Width / 3 * (choice->destination - 1), 0, Window_Width / 3 * choice->destination, Window_Height);
	}

	for (n = 1; n <= 3; n++)
	{
		c1.x = Window_Width / 3 / 2 - Column_Width / 2 + (n - 1) * Window_Width / 3;
		setfillcolor(0xbbbbbb / n);
		fillrectangle(c1.x, c1.y, c1.x + c1.width, c1.y + c1.height);
	}

	putLine(Arr[0], 0);
	putLine(Arr[1], 1);		//打印可移动长方体(·)
	putLine(Arr[2], 2);

	setfillcolor(0x000000);
	fillrectangle(0, Window_Height - Column_Width * 2, Window_Width, Window_Height);

	settextstyle(50, 0, _T("宋体"));

	switch (mouseC)
	{
	case 1:
		outtextxy(100, 20, _T("A柱"));
		break;
	case 2:
		outtextxy(100, 20, _T("B柱"));
		break;
	case 3:
		outtextxy(100, 20, _T("C柱"));
		break;
	default:
		outtextxy(100, 20, _T("把握不柱"));
		break;
	}
	switch (choice->sourse)
	{
	case 1:
		outtextxy(50, 70, _T("选择A"));
		break;
	case 2:
		outtextxy(50, 70, _T("选择B"));
		break;
	case 3:
		outtextxy(50, 70, _T("选择C"));
		break;
	default:
		break;
	}
	switch (choice->destination)
	{
	case 1:
		outtextxy(50, 120, _T("目标A"));
		break;
	case 2:
		outtextxy(50, 120, _T("目标B"));
		break;
	case 3:
		outtextxy(50, 120, _T("目标C"));
		break;
	default:
		break;
	}
	if (Win)
	{
		settextstyle(400, 0, "宋体");
		int x = 0, y = 0;
		char text[1021] = "WIN";
		x = Window_Width / 2 - textwidth(text) / 2;
		y = Window_Height / 2 - textheight(text) / 2;
		outtextxy(x, y, text);

		settextstyle(50, 0, "宋体");
		strcpy(text, "按任意键退出");
		x = Window_Width / 2 - textwidth(text) / 2;
		y = Window_Height / 2 - textheight(text) / 2 - 200;
		outtextxy(x, y, text);

		FlushBatchDraw();
		system("pause");
		return true;
	}
	FlushBatchDraw();
	return false;
}

//void CloseGame(Layer_Arr* (*destination)[3])
//{
//	int i = 0, j = 0;
//	for (i = 0; i < 3; i++)
//	{
//		for (j = 0; j < LAYER_NUMBER; i++)
//		{
//			free((*destination)[i]->arr[j]);
//			(*destination)[i]->arr[j] = NULL;
//		}
//		(*destination)[i] = NULL;
//	}
//}

int AI_Move(Layer_Arr** Arr, int Sourse, int Destination)
{
	return Layer_Move(Arr, Destination, Sourse, LAYER_NUMBER);
}

int Hanoi(Layer_Arr** Arr, size_t d1, size_t d2, size_t d3, size_t Count, int mouseC, Choice* choice, bool Win)
{
	int ret = 0;
	if (Count == 1)
	{
		ret = AI_Move(Arr, d1, d3);
		eaeryPut(mouseC, choice, Arr, Win);
	}
	else
	{
		Hanoi(Arr, d1, d3, d2, Count - 1, mouseC, choice, Win);
		ret = AI_Move(Arr, d1, d3);
		eaeryPut(mouseC, choice, Arr, Win);
		Hanoi(Arr, d2, d1, d3, Count - 1, mouseC, choice, Win);
	}
	return ret;
}

int Game()
{
	initgraph(Window_Width, Window_Height);
	setbkcolor(0xffffff);
	cleardevice();

	setlinestyle(PS_NULL);
	setfillcolor(0x000000);
	settextcolor(0x000000);

	c1.x = 0;
	c1.y = Column_Width;
	c1.width = Column_Width;
	c1.height = Window_Height - Column_Width;

	MOUSEMSG msg = GetMouseMsg();
	int mouseC = 0;

	int MoveNumber = 0;

	Layer_Arr* Arr[3] = { 0 };
	GetLayer(LAYER_NUMBER, Arr);

	Choice choice = { 0 };

	bool MouseOnce = false;
	bool Win = false;

	BeginBatchDraw();

#ifdef AI_
	{
		MoveNumber = Hanoi(Arr, 0, 1, 2, LAYER_NUMBER, mouseC, &choice, Win);
		eaeryPut(mouseC, &choice, Arr, true);
	}
#else
	{
		while (1)
		{
			int n = 0;

			//输入消息
			{
				msg = { 0 };
				if (MouseHit())
				{
					msg = GetMouseMsg();

				}
			}

			//消息处理
			{
				for (n = 1; n <= 3; n++)
				{
					if (msg.x > (n - 1) * Window_Width / 3 && msg.x <= Window_Width * n / 3)
					{
						mouseC = n;
					}
				}
				//拿到当前所处位置

				if (msg.uMsg == WM_LBUTTONUP)
				{
					if (!MouseOnce)
					{
						MouseOnce = true;
						if (!choice.state)
						{
							choice.destination = NULL;
							choice.sourse = mouseC;
							choice.state = true;
						}
						else if (choice.state && choice.sourse)
						{
							choice.destination = mouseC;
							//移动
							Layer_Move(Arr, choice.destination - 1, choice.sourse - 1, LAYER_NUMBER);
							choice.destination = NULL;
							choice.sourse = NULL;
							choice.state = false;
						}
					}
					Win = IsWin(Arr[2], LAYER_NUMBER);
				}
				else if (msg.uMsg == WM_LBUTTONDOWN)
				{
					MouseOnce = false;
				}

			}

			//输出消息
			if (eaeryPut(mouseC, &choice, Arr, Win))
			{
				//CloseGame(&Arr);
				return 0;
			}

		}
	}
#endif
	EndBatchDraw();

	closegraph();
	return 0;
}

int main()
{

	return Game();
}
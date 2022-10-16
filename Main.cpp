#define _CRT_SECURE_NO_WARNINGS 1

#define AI_

#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<assert.h>
#include<string.h>

#define Window_Width 1920
#define Window_Height 1080

#define Column_Width 50

#define LAYER_NUMBER_MAX 12

int LAYER_NUMBER = 0;
int MoveNumber = 0;


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

bool IfMove(Layer_Arr** Arr, size_t destination, size_t sourse, size_t Count)
{
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
			return true;
		}
		else if (Arr[destination]->arr[SumD - 1]->line > Arr[sourse]->arr[SumS - 1]->line)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

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

	int i = 0;
	int SumS = 0, SumD = 0;

	assert(Arr);

	if (IfMove(Arr, destination, sourse, Count))
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
		memmove(Arr[destination]->arr[SumD],
				Arr[sourse]->arr[SumS - 1], 
				sizeof(Layer));
		memset(Arr[sourse]->arr[SumS - 1], 
				0, sizeof(Layer));
		MoveNumber++;
	}
	return MoveNumber;
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

bool eaeryPut(int mouseC, const Choice* choice, Layer_Arr** Arr, bool Win,size_t MoveNumber,bool AI)
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
		setfillcolor(0x44AAAA);
		fillrectangle(Window_Width / 3 * (choice->sourse - 1), 0, Window_Width / 3 * choice->sourse, Window_Height);
		
		for (n < 0; n < 3; n++)
		{
			if (n != choice->sourse - 1)
			{
				if (IfMove(Arr, n, choice->sourse - 1, LAYER_NUMBER))
				{
					setfillcolor(0x88FF88);
				}
				else
				{
					setfillcolor(0x8888FF);
				}
				fillrectangle(Window_Width / 3 * n, 0, Window_Width / 3 * (n + 1), Window_Height);
			}
		}

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

	{
		settextstyle(50, 0, "宋体");
		int x = 0, y = 0;
		char text[128] = { 0 };

		sprintf(text, "已移动步数%d", MoveNumber);

		x = Window_Width / 2 - textwidth(text) / 2;
		y = Window_Height - Column_Width * 2 + textheight(text) / 4;

		outtextxy(x, y, text);
	}

	if(AI)
	{ 
		setfillcolor(0xDDEECC);
		fillrectangle(250, 250, Window_Width - 250, Window_Height - 250);
		settextstyle(140, 0, "宋体");
		int x = 0, y = 0;
		char text[1021] = "按下Enter开始游戏";
		x = Window_Width / 2 - textwidth(text) / 2;
		y = Window_Height / 2 - textheight(text) / 2;
		outtextxy(x, y, text);
	}
	else if (Win)
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

bool AI_Move(Layer_Arr** Arr, int Sourse, int Destination)
{
	return Layer_Move(Arr, Destination, Sourse, LAYER_NUMBER);
}

bool Hanoi(Layer_Arr** Arr, size_t d1, size_t d2, size_t d3, size_t Count, int mouseC, Choice* choice, bool Win)
{
	if (Count == 1)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			return false;
		}
		AI_Move(Arr, d1, d3);
		eaeryPut(mouseC, choice, Arr, Win, MoveNumber,true);
	}
	else
	{
		if (!Hanoi(Arr, d1, d3, d2, Count - 1, mouseC, choice, Win))
		{
			return false;
		}
		AI_Move(Arr, d1, d3);
		eaeryPut(mouseC, choice, Arr, Win, MoveNumber,true);
		if (!Hanoi(Arr, d2, d1, d3, Count - 1, mouseC, choice, Win))
		{
			return false;
		}
	}
	return true;
}

void CloseHanoi(Layer_Arr**Arr,size_t Number)
{
	int i = 0, n = 0;
	for(n = 0;n < 3;n++)
	{
		for (i = 0; i < Number; i++)
		{
			free(Arr[n]->arr[i]);
			Arr[n]->arr[i] = NULL;
		}
	}
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

	Layer_Arr* Arr[3] = { 0 };

	Choice choice = { 0 };

	bool MouseOnce = false;
	bool Win = false;

	BeginBatchDraw();

	LAYER_NUMBER = 9;
	MoveNumber = NULL;
	while (true)
	{
		GetLayer(LAYER_NUMBER, Arr);
		if (Hanoi(Arr, 0, 1, 2, LAYER_NUMBER, mouseC, &choice, Win))
		{
			DWORD t1, t2;
			t1 = t2 = GetTickCount();
			while (true)
			{
				t2 = GetTickCount();
				if (t2 - t1 >= 1000)
				{
					break;
				}
				if (GetAsyncKeyState(VK_RETURN))
				{
					break;
				}
				eaeryPut(mouseC, &choice, Arr, true, MoveNumber, true);
			}

			CloseHanoi(Arr, LAYER_NUMBER);
			if (LAYER_NUMBER<=39)
			{
				LAYER_NUMBER += 1;
			}
			else if(LAYER_NUMBER >= 39)
			{
				LAYER_NUMBER -= 1;
			}
		}
		else
		{
			eaeryPut(mouseC, &choice, Arr, true, MoveNumber, true);
			CloseHanoi(Arr, LAYER_NUMBER);
			break;
		}
	}

	{
		LAYER_NUMBER = 5;
		MoveNumber = NULL;
		GetLayer(LAYER_NUMBER, Arr);
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
			if (eaeryPut(mouseC, &choice, Arr, Win, MoveNumber,false))
			{
				//CloseGame(&Arr);
				return 0;
			}

		}
		EndBatchDraw();
	}
		closegraph();
		return 0;
}

int main()
{

	return Game();
}
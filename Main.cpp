#define _CRT_SECURE_NO_WARNINGS 1

#include<graphics.h>
#include<Windows.h>
#include<stdio.h>

#include<iostream>

int main()
{
	//bool b = 32;

	//int a = b;

	//在cpp中，bool只有0值和非0值
	//std::cout << a << ' ' << b << std::endl;

	//signed char c1 = 256;
	//signed char c2 = 257;	//高位截瘫
	//unsigned char c3 = -1;

	//std::cout << (int)c1 << ' ' << (int)c2 << ' ' << (int)c3 << std::endl;

	//float f = 0xFFFFFFFF;

	//std::cout << f << std::endl;


	//bool型只有0值与非零值(菲林值)（？
	//bool b = 32;

	//switch (b)
	//{
	//case 32:
	//	std::cout << "Out" << std::endl;
	//	break;
	//default:
	//	std::cout << "ouT" << std::endl;
	//}

	//unsigned u = 10;
	//int i = -42;

	////这里将i转化为了无符号计算
	//std::cout << i + u << std::endl;
	//std::cout << i + i << std::endl;

	//unsigned u1 = 42, u2 = 10;

	//std::cout << u1 - u2 << std::endl;			//32
	//std::cout << u2 - u1 << std::endl;			//错误值
	//std::cout <<(int)( u2 - u1 )<< std::endl;		//-32

	//for (unsigned i = 10; i >= 0; --i)
	//	std::cout << i << ' ';			//i为无符号数，不会小于0，循环将永远持续下去
	//std::cout << std::endl;
	//unsigned n = 11;
	//while (n>0)
	//{
	//	--n;
	//	std::cout << n << ' ';
	//}
	//std::cout << std::endl;

	//unsigned u = 10, u2 = 42;
	//
	//std::cout << u2 - u << std::endl;	//32
	//std::cout << u - u2 << std::endl;	//(unsigned)-32
	//std::cout << (unsigned)-32 << std::endl;

	//int i = 10, i2 = 42;

	//std::cout << i2 - i << std::endl;	//32
	//std::cout << i - i2 << std::endl;	//-32
	//std::cout << i - u << std::endl;	//0
	//std::cout << u - i << std::endl;	//0

	//字面值常量
	//  20 /* 十进制 */
	// 024 /* 八进制 */
	//0x14 /* 十六进制 */
	// "-" 取负，将字面值常量转化为负数形式

	//默认浮点型字面值是一个double
	//指数
	//3.14159	-		3.14159E0
	//0.		-		0e0
	//.001		-		1e-3

	//字符和字符串字面值
	//std::cout << "a really, really long string literal "
	//	" that spans two lines" << std::endl;
	//转义序列
	//换行符		\n		横向制表符	\t		蜂鸣符			\a
	//纵向制表符	\v		退格符		\b		双引号			\"
	//反斜杠		\\		问号		\?		单引号			\'
	//回车符		\r		进纸符		\f

	//std::cout << "AAA";
	//Sleep(1000);
	//std::cout << "\a\a" << std::endl;

	//std::cout << "Hi \x4dO\115\n";
	//std::cout << '\115' << '\n';

	

	return 0;
/*	int a, b;
	scanf("%d%d", &a, &b);
	printf("\n a+b=%d\n", a + b);
	return 0*/;
}

//int main()
//{
//	initgraph(1000, 1000);
//	MOUSEMSG msg = { 0 };
//	bool MouseStateL = false;
//	bool Selece = false;
//	setbkcolor(0xffffff);
//	cleardevice();
//	BeginBatchDraw();
//	while (1)
//	{
//		FlushBatchDraw();
//		cleardevice();
//		if (MouseHit())
//		{
//			msg = GetMouseMsg();
//		}
//		if (Selece)
//		{
//			setfillcolor(0xff00);
//			fillrectangle(0, 0, msg.x, msg.y);
//		}
//		setfillcolor(0x000000);
//		fillrectangle(msg.x, msg.y, msg.x + 300, msg.y + 300);
//		Sleep(10);
//	}
//	EndBatchDraw();
//
//	return 0;
//}
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include "pch.h"
#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define LEFT  0x4B00
#define RIGHT 0x4D00
#define UP    0x4800
#define DOWN  0x5000
#define ESC   0x011B
#define ENTER 0x1C0D
#define SIZE 10
#define GAMEFRAME_WIDTH 64
#define FRAME_HEIGHTH 48
#define DATAFRAME_WIDTH 48

int i, j;
//蛇的结构体
/*typedef   struct SnakeBody
{
	int x;
	int y;
	struct SnakeBody *previous;
	struct SnakeBody *next;
} *head, *tail;*/
void startup();
void welcomeUI()
{
	IMAGE img1;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\微信图片_20180808214022.jpg"));
	putimage(0, 0, &img1);
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			startup();
		}
	}
	
	
	

	/*int n;
	char s[20];
	RECT r = { 0,0,1120,480 };
	drawtext(_T("Please input '1' to go on"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	InputBox(s, 20, "输入1以继续");
	sscanf_s(s, "%d", &n);
	switch (n)
	{
	case 1:
		closegraph();
		initgraph(1120, 480);
		//drawtext(_T("Hello World!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}*/
}

//初始化函数
void startup()
{
	for (i = 0; i < GAMEFRAME_WIDTH; i++)
	{
		moveto(i*SIZE, 0);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 0, (i + 1)*SIZE, SIZE);
		moveto(i*SIZE, (FRAME_HEIGHTH-1)*SIZE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, (FRAME_HEIGHTH - 1)*SIZE, (i + 1)*SIZE, (FRAME_HEIGHTH )*SIZE);
	}
	for (j = 0; j < FRAME_HEIGHTH; j++)
	{
		moveto(0, j*SIZE);
		setfillcolor(BLUE);
		fillrectangle(0,j*SIZE,SIZE,(j+1)*SIZE);
		moveto((GAMEFRAME_WIDTH - 1)*SIZE, j*SIZE);
		setfillcolor(BLUE);
		fillrectangle((GAMEFRAME_WIDTH - 1)*SIZE, j*SIZE, GAMEFRAME_WIDTH*SIZE, (j + 1)*SIZE);
	}
}



int main()
{
	initgraph(1120, 480);
	welcomeUI();
	startup();
	getchar();
	closegraph();
}	
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include "pch.h"
#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
//宏定义
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
//函数声明
void startup();
//循环变量
int i, j;
//食物的结构体
struct food
{
	int x;
	int y;
} food1;
//毒药的结构体
struct poison
{
	int x;
	int y;
}poison1 ;
//蛇的结构体
struct Snake
{
	int x[50];
	int y[50];
	int length;
	struct Snake *previous;
	struct Snake *next;
} *head, *tail,snake;
//毒药的生成
void creaPoison()
{
	srand((unsigned)time(NULL));
	poison1.x = (rand() * 100) % 53 + 1;
	poison1.y = (rand() * 100) % 54 + 1;
	moveto(poison1.x*SIZE, poison1.y*SIZE);
	setfillcolor(GREEN);
	fillcircle(poison1.x*SIZE + SIZE / 2, poison1.y*SIZE + SIZE / 2, SIZE / 2);
}
//食物的生成
void creatFood()
{
	srand((unsigned)time(NULL));
	food1.x = (rand() * 100) % 62 + 1;
	food1.y = (rand() * 100) % 62 + 1;
	moveto(food1.x*SIZE, food1.y*SIZE);
	setfillcolor(RED);
	fillcircle(food1.x*SIZE + 5, food1.y*SIZE + 5, SIZE / 2);
}
//初始化界面
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
			break;
		}
	}
}
//数据初始化函数
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
	snake.x[0] = GAMEFRAME_WIDTH / 2;
	snake.y[0] = FRAME_HEIGHTH / 2;
	moveto(snake.x[0], snake.y[0]);
	setfillcolor(YELLOW);
	fillcircle(snake.x[0] - SIZE / 2, snake.y[0] - SIZE / 2, SIZE / 2);
	snake.length = 4;

	creatFood();
	creaPoison();
}
//主函数
int main()
{
	initgraph(1120, 480);
	welcomeUI();
	startup();
	getchar();
	closegraph();
}	
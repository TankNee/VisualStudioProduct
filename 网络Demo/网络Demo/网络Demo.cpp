#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include"pch.h"
#include<stdlib.h>
#pragma warning(disable:4996)
#define radius 10
#define height 600
#define width 600
#define movespeed 100
typedef struct snake {
	int x;
	int y;
	snake *next;
	snake *prior;
}snake;
typedef struct food {
	int x;
	int y;
	int color_x;
	int color_y;
	int color_z;
	int food_radius;
}food;
food *foodl = new food;
char direction, memory = 's';
snake *p = new snake, *head = p, *tail = new snake, *delete_tail = new snake, *p1 = NULL;
BOOL judge = false;


void foodcolor()
{
	foodl->color_x = rand() % 255;
	foodl->color_y = rand() % 255;
	foodl->color_z = rand() % 255;
	setfillcolor(RGB(foodl->color_x, foodl->color_y, foodl->color_z));
	solidcircle(foodl->x, foodl->y, radius);
}
void judgefood(snake *head)
{
	if (pow((double)(head->x - foodl->x), 2) + pow((double)(head->y - foodl->y), 2) <= pow(double(radius + radius), 2))
	{
		judge = true;
		setfillcolor(BLACK);
		solidcircle(foodl->x, foodl->y, radius);
		foodl->x = rand() % (height - radius);
		foodl->y = rand() % (width - radius) + radius;//初始化食物坐标
	}
}
void showsnake(snake *head)
{
	snake *p = head;
	while (p)
	{
		setfillcolor(YELLOW);
		solidcircle(p->x, p->y, radius);
		p = p->next;
	}
}
void judgesnake()//判断蛇是否吃到食物
{
	showsnake(head);
	if (judge == false)
	{
		setfillcolor(BLACK);
		solidcircle(delete_tail->x, delete_tail->y, radius);
		delete_tail = delete_tail->prior; //删除尾节点
		delete_tail->next = NULL;
	}
	else
	{
		judge = false;
	}
}
void boardcontrol()
{
	p1 = new snake; //开辟一个新节点
	judgesnake();
	Sleep(movespeed);
	while (kbhit())
		direction = getch();
	if (direction == 'k')
		system("pause");
	if (direction == 'w' || direction == 's' || direction == 'a' || direction == 'd')
		memory = direction;
	else
	{
		direction = memory;
	}
	switch (direction) //根据按键不同的方向 控制尾节点排在头结点的坐标位置 一次来判断蛇头的移动
	{
	case 'w':
	{
		p1->x = head->x;
		p1->y = head->y - 2 * radius; break;
	}
	case 's':
	{
		p1->x = head->x;
		p1->y = head->y + 2 * radius; break;
	}
	case 'a':
	{
		p1->x = head->x - 2 * radius;
		p1->y = head->y; break;
	}
	case 'd':
	{
		p1->x = head->x + 2 * radius;
		p1->y = head->y; break;
	}
	default:break;
	}
	p1->next = head;
	head->prior = p1; //p1成为头结点
	head = p1;
	showsnake(head);
	FlushBatchDraw();
}
void initsnake()//把最开始的是三个节点连接起来
{
	p->x = 200;
	p->y = 200;
	tail->x = 200 + 2 * radius;
	tail->y = 200;
	delete_tail->x = tail->x + 2 * radius;
	delete_tail->y = 200;//给最开始蛇三个节点的坐标赋值
	delete_tail->next = NULL;
	p->next = tail;
	tail->next = delete_tail; //三个节点坐标的地址前后相互连接起来
	tail->prior = p;
	delete_tail->prior = tail;
}
void main()
{
	foodl->x = rand() % (height - radius);
	foodl->y = rand() % (width - radius) + radius;//初始化食物坐标
	head = p;
	initgraph(height, width);
	initsnake();
	showsnake(head);
	char c = getch();
	BeginBatchDraw();//开始批量绘图操作
	while (1)
	{
		foodcolor();
		judgefood(head);
		boardcontrol();
	}
	EndBatchDraw();//结束批量绘图操作
	closegraph();
}

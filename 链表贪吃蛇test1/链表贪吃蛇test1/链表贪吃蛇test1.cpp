#include<stdio.h>
#include<Windows.h>
#include "pch.h"
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include <iostream>
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
//上：1  下：2  左：3  右：4     
int snakedir =4;
//函数声明
void startup();
//循环变量
int i, j;
//蛇身的长度
int length=4;
//速度控制变量
int  sleeptime = 100;
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
typedef struct snakeNode
{
	int x;
	int y;
	struct snakeNode *previous=NULL;
	struct snakeNode *next=NULL;
} snakenode;
snakenode *head;
int checkMove(snakenode *checkpoint);
void iniSnake()
{
	snakenode *snakept_1,*snakept_2;
	head = (snakenode *)malloc(sizeof(snakenode));
	head->x = GAMEFRAME_WIDTH / 2;
	head->y = FRAME_HEIGHTH / 2;
	head->next = NULL;
	head->previous = NULL;
	snakept_2 = head;
	for (i = 2; i <= length; i++)
	{
		snakept_1= (snakenode *)malloc(sizeof(snakeNode));
		snakept_1->x = snakept_2->x - 1;
		snakept_1->y = snakept_2->y;
		snakept_1->next = snakept_2->next;              
		snakept_2->next = snakept_1;				  //将两个链节连接起来			
		snakept_1->previous = snakept_2;
		snakept_2 = snakept_1;
	}

}
//毒药的生成
void creatPoison()
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
	food1.x = (rand() * 100) % 34 + 1;
	food1.y = (rand() * 100) % 15 + 1;
	moveto(food1.x*SIZE, food1.y*SIZE);
	setfillcolor(RED);
	fillcircle(food1.x*SIZE + SIZE / 2, food1.y*SIZE + SIZE / 2, SIZE / 2);
}
void coverAndClear(snakenode *pt)
{
	snakenode *temp;
	temp = pt;
	moveto(temp->x*SIZE, temp->y*SIZE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillcircle(temp->x*SIZE + SIZE / 2, temp->y*SIZE + SIZE / 2, SIZE / 2);
}
void snakePaint()
{
	snakenode *point;
	point = head;
	moveto(point->x*SIZE, point->y*SIZE);
	setfillcolor(YELLOW);
	setlinecolor(WHITE);
	fillcircle(point->x*SIZE+ SIZE / 2, point->y*SIZE+ SIZE / 2,SIZE/2);
	point = point->next;
	while (point!=NULL)
	{
		moveto(point->x*SIZE, point->y*SIZE);
		setfillcolor(LIGHTBLUE);
		setlinecolor(WHITE);
		fillcircle(point->x*SIZE + SIZE / 2, point->y*SIZE + SIZE / 2, SIZE / 2);
		point = point->next;
	} 
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
void starGameUI()
{
	IMAGE img1;
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x)//尚未完成，这里匹配的难度选择关卡
		{

		}
	}
}
//数据初始化函数
void startup()
{
	//打印边框
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
	//初始化蛇身
	iniSnake();
	//打印蛇身
	snakePaint();
	//打印食物与毒药
	creatFood();
	creatPoison();
}
//蛇移动函数
//移动方法：新建一个头节点，删除一个尾节点
void snakeMove()
{
	int check;
	int temp_x = head->x, temp_y = head->y;
	if (snakedir == 1)
	{
		head->y -= 1;
	}
	else if (snakedir == 2)
	{
		head->y += 1;
	}
	else if (snakedir == 3)
	{
		head->x -= 1;
	}
	else if (snakedir == 4)
	{
		head->x += 1;
	}
	snakenode *temp = (snakenode *)malloc(sizeof(snakenode));//建立新的节点放在新蛇的第二节，替换原来的头部
	temp->x = temp_x;
	temp->y = temp_y;
	temp->next = head->next;
	head->next->previous = temp;//将新的第二节与第三节连接
	head->next = temp;//将新的头部与第二节相连
	check = checkMove(head);
	if (check == 1)
	{
		creatFood();
		return;
	}
	else if (check == 2)
	{
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		coverAndClear(temp->next);
		free(temp->next);
		temp->next = NULL;
		temp = temp->previous;
		coverAndClear(temp->next);
		free(temp->next);
		temp->next = NULL;
		creatPoison();
	}
	else if (check == 3)
	{
		system("pause");
		Sleep(3000);
		exit(0);
	}
	else if (check == 0)
	{
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		coverAndClear(temp->next);
		free(temp->next);
		temp->next = NULL;
	}
}
int checkMove(snakenode *checkpoint)//检查函数，判断蛇的移动是否合法
{
	if (checkpoint->x == food1.x&&checkpoint->y == food1.y)
	{
		return 1;
	}
	else if (checkpoint->x == poison1.x&&checkpoint->y == poison1.y)
	{
		return 2;
	}
	else if (checkpoint->x == 0 || checkpoint->x == 64 || checkpoint->y == 0 || checkpoint->y == 48)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}
//获取用户输入
void getInput()
{
	int input;
	int key;
	if (_kbhit())
	{
		input = _getch();
		if (input == 119||input==87)//119  w
		{
			snakedir = 1;			
		}
		else if(input==115||input==83)//115  s
		{
			snakedir = 2;			
		}
		else if (input == 97||input==65)//97  a  
		{
			snakedir = 3;
		}
		else if(input==100||input==68)//100  d
		{
			snakedir = 4;
		}
		else if (input == 224)
		{
			key = _getch();
			if (key == 72)//上键
			{
				snakedir = 1;
			}
			else if (key == 80)//下键
			{
				snakedir = 2;
			}
			else if (key == 75)//左键
			{
				snakedir = 3;
			}
			else if (key == 77)//右键
			{
				snakedir = 4;
			}
		}
	}//控制蛇的移动，基本已完成！
	else
	{
		Sleep(sleeptime);
		snakeMove();
	}
}
//游戏主函数
void startGame()
{
	snakedir = 4;
	while (1)
	{
		getInput();
		snakePaint();
	}
}
//主函数
int main()
{
	initgraph(1120, 480);	
	welcomeUI();
	startup();
	startGame();
	getchar(); 
	closegraph();
}	
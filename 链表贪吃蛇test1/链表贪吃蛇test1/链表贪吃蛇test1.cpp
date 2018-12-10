#include<stdio.h>
#include<Windows.h>
#include "pch.h"
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include <iostream>
//宏定义
#define SIZE 10
#define GAMEFRAME_WIDTH 64
#define FRAME_HEIGHTH 48
#define DATAFRAME_WIDTH 48
//上：1  下：2  左：3  右：4     
int snakedir =4;
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
//炸弹的结构体
struct boom
{
	int x;
	int y;
}boom1;
struct smartFood
{
	int x;
	int y;
}smartfood1;
//函数声明
void startup();
int checkMove(snakenode *checkpoint);
int checkProp();
void datashow();
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
	poison1.x =rand() % 48 + 15;
	poison1.y = rand()  % 37 + 10;
	if (checkProp() == 1 || checkProp() == 2)
	{
		creatPoison();
	}
	moveto(poison1.x*SIZE, poison1.y*SIZE);
	setlinecolor(WHITE);
	setfillcolor(GREEN);
	fillcircle(poison1.x*SIZE + SIZE / 2, poison1.y*SIZE + SIZE / 2, SIZE / 2);
}
//食物的生成
void creatFood()
{
	srand((unsigned)time(NULL));
	food1.x = rand() % 56 + 7;
	food1.y = rand()  % 44 + 3;
	if (checkProp()==1||checkProp()==3)
	{
		creatFood();
	}
	moveto(food1.x*SIZE, food1.y*SIZE);
	setlinecolor(WHITE);
	setfillcolor(RED);
	fillcircle(food1.x*SIZE + SIZE / 2, food1.y*SIZE + SIZE / 2, SIZE / 2);
}
//炸弹的生成
void creatBoom()
{
	srand((unsigned)time(NULL));
	boom1.x = rand()  % 54 + 7;
	boom1.y = rand()  % 34 + 13;
	if (checkProp() == 2 || checkProp() == 3)
	{
		creatBoom();
	}
	moveto(boom1.x*SIZE, boom1.y*SIZE);
	setlinecolor(WHITE);
	setfillcolor(LIGHTGRAY);
	fillcircle(boom1.x*SIZE + SIZE / 2, boom1.y*SIZE + SIZE / 2, SIZE / 2);
}
void creatSmartFood()
{
	srand((unsigned)time(NULL));
	smartfood1.x = rand()  % 54 + 7;
	smartfood1.y = rand()  % 46 + 1;
	moveto(smartfood1.x*SIZE, smartfood1.y*SIZE);
	setlinecolor(WHITE);
	setfillcolor(LIGHTCYAN);
	fillcircle(smartfood1.x*SIZE + SIZE / 2, smartfood1.y*SIZE + SIZE / 2, SIZE / 2);
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
void dataShow()
{
	moveto(80 * SIZE, 5 * SIZE);
	setcolor(YELLOW);
	settextcolor(GREEN);
	RECT r = {800,50,1000,70};
	drawtext(_T("贪吃蛇"), &r, DT_CENTER);

}
void startGameUI()
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
void endGameUI()
{
	IMAGE img1;
	MOUSEMSG m;
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
	//打印各类道具
	creatFood();
	creatPoison();
	creatSmartFood();
	creatBoom();
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
		length++;
		creatFood();
		return;
	}
	else if (check == 2)
	{
		length--;
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
		int len;
		len = length / 2;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		if (len == 0)
		{
			system("pause");
			exit(0);
		}
		for (i = 0; i <= len; i++)
		{
			coverAndClear(temp->next);
			free(temp->next);
			temp->next = NULL;
			temp = temp->previous;
		}
		creatBoom();
	}
	else if (check == 4)
	{
		system("pause");
		Sleep(3000);
		exit(0);
	}
	else if (check == 5)
	{
		int food_x, food_y;
		food_x = food1.x;
		food_y = food1.y;
		temp_x = head->x;
		temp_y = head->y;
		if ((temp_x - food_x)*(temp_y - food_y) >= 0)
		{
			if (temp_x - food_x >= 0)
			{
				if (snakedir == 3 || snakedir == 4)
				{
					while (head->y!=food_y)
					{
						snakedir = 1;
						snakeMove();
					}
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
					}
					while (head->y != food_y)
					{
						snakedir = 1;
						snakeMove();
					}
				}
			}
			else
			{
				if (snakedir == 3 || snakedir == 4)
				{
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
					}
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
					}
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
					}

				}
			}
		}
		else
		{
			if (temp_x - food_x >= 0)
			{
				if (snakedir == 3 || snakedir == 4)
				{
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
					}
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
					}
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
					}
				}
			}
			else
			{
				if (snakedir == 3 || snakedir == 4)
				{
					while (head->y != food_y)
					{
						snakedir = 1;
						snakeMove();
					}
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
					}
					while (head->y != food_y)
					{
						snakedir = 1;
						snakeMove();
					}
				}
			}
		}

	}
	else if (check == -1)
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
	else if (checkpoint->x == boom1.x&&checkpoint->y == boom1.y)
	{
		return 3;
	}
	else if (checkpoint->x == 0 || checkpoint->x == 63 || checkpoint->y == 0 || checkpoint->y == 48)
	{
		return 4;
	}
	else if (checkpoint->x == smartfood1.x&&checkpoint->y ==smartfood1.y)
	{
		return 5;
	}
	else
	{
		return 0;
	}
	checkpoint = head->next;
	while (true)
	{
		if (head->x == checkpoint->x&&head->y == checkpoint->y)
		{
			return -1;
		}
		else if (checkpoint->next == NULL)
		{
			break;
		}
		checkpoint = checkpoint->next;
	}
}
//道具检查函数，检查是否生成在同一位置
int checkProp()
{
	if (food1.x == poison1.x&&food1.y == poison1.y)
	{
		return 1;
	}
	else if (boom1.x == poison1.x&&boom1.y == poison1.y)
	{
		return 2;
	}
	else if (boom1.x == food1.x&&boom1.y == food1.y)
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
		dataShow();
	}
}
//主函数
int main()
{
	initgraph(1120, 480);	
	//welcomeUI();
	startup();
	startGame();
	getchar(); 
	closegraph();
}	
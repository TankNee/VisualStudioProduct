#include<stdio.h>
#include<Windows.h>
#include "pch.h"
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include <iostream>
//TODO 道具链表化
//宏定义
#define SIZE 10
#define GAMEFRAME_WIDTH 64
#define FRAME_HEIGHTH 48
#define DATAFRAME_WIDTH 48
//关卡变量
int pass=1,passscore;
//随机变量
int randnumber=3543;
//数字1~9
IMAGE number[10];
//文件指针函数
FILE *fpRank;
FILE *fpRand;
FILE *fpSave;
//排行榜数组
int rankscore[10] = {0};
//难度变量
int level = 5;
//上：1  下：2  左：3  右：4     
int snakedir =4;
//循环变量
int i, j;
//蛇身的长度
int length=4;
//速度控制变量
int  sleeptime = 85-level*10;
//分数  基准分数为0   食物的基准分数为5  毒药基准分数为-10 
int score = 0,foodscore, poisonscore = -10;
//食物的结构体
typedef struct food
{
	int x;
	int y;
} food;
food food1; 
//毒药的结构体
typedef struct poison
{
	int x;
	int y;
	poison *next;
}poison;
poison *Poison,*temppoison,*headOfPoison;
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
typedef struct boom
{
	int x;
	int y;
	boom *next;
}boom;
boom *Boom,*tempboom;
//智慧草的结构体
typedef struct smartFood
{
	int x;
	int y;
	smartFood *next;
	smartFood *previous;
}smartfood;
smartFood smartfood1;
//函数声明
void startup();
int checkMove(snakenode *checkpoint);
int checkProp();
void dataShow();
void endGameUI();
void startGame();
void levelUI();
void writeRank();
void readRank();
void sortRank(int a[10]);
void biteItself();
void writeRand();
void readRand();
int main();
void secondStartup();
void thirdStartup();
void saveGameUI();
void creatPoison(poison *modelpt);
void creatBoom(boom *modelpt);
void freerom();
//蛇的初始化
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
//道具初始化
void iniProp()
{
	poison *poisonpt_1, *poisonpt_2;
	boom *boompt_1, *boompt_2;
	Poison = (poison*)malloc(sizeof(poison));
	headOfPoison = Poison;
	Boom = (boom *)malloc(sizeof(boom));
	poisonpt_2 = Poison;
	boompt_2 = Boom;
	creatPoison(Poison);
	creatBoom(Boom);
	for (i = 0; i < level / 2; i++)
	{
		poisonpt_1= (poison*)malloc(sizeof(poison));
		boompt_1 = (boom *)malloc(sizeof(boom));
		poisonpt_2->next = poisonpt_1;
		creatPoison(poisonpt_1);
		boompt_2->next = boompt_1;
		creatBoom(boompt_1);
		poisonpt_2 = poisonpt_1;
		boompt_2 = boompt_1;
	}
	poisonpt_2->next = NULL;
	boompt_2->next = NULL;
}
//毒药的生成
void creatPoison(poison *modelpt)
{
	srand(randnumber);
	modelpt->x= rand() % 48 + 15;
	modelpt->y= rand() % 37 + 10;
	setlinecolor(WHITE);
	setfillcolor(GREEN);
	fillcircle(modelpt->x*SIZE + SIZE / 2, modelpt->y*SIZE + SIZE / 2, SIZE / 2);
	randnumber += 24;
}
//毒草闪烁函数
void poisonTwinkle_1()
{
	Sleep(10);
	poison *temp;
	temp = headOfPoison;
	while (temp!=NULL)
	{
		setfillcolor(WHITE);
		setlinecolor(WHITE);
		fillrectangle(temp->x*SIZE, temp->y*SIZE, temp->x*SIZE + SIZE, temp->y*SIZE + SIZE);
		temp = temp->next;
	}
}
void poisonTwinkle_2()
{
	poison *temp;
	temp = headOfPoison;
	while (temp != NULL)
	{
		setfillcolor(GREEN);
		setlinecolor(WHITE);
		fillcircle(temp->x*SIZE + SIZE / 2, temp->y*SIZE + SIZE / 2, SIZE / 2);
		temp = temp->next;
	}
}
//食物的生成
void creatFood()
{
	srand(randnumber);
	food1.x = rand() % 56 + 7;
	food1.y = rand()  % 44 + 3;
	if (checkProp()==1||checkProp()==3||(food1.x == GAMEFRAME_WIDTH / 2 * SIZE&&food1.y == FRAME_HEIGHTH / 2 * SIZE))
	{
		randnumber += 54;
		creatFood();
	}
	setlinecolor(WHITE);
	setfillcolor(RED);
	fillcircle(food1.x*SIZE + SIZE / 2, food1.y*SIZE + SIZE / 2, SIZE / 2);
	randnumber += 23;
	foodscore = 5 + level / 2 + length / 3;
}
//炸弹的生成
void creatBoom(boom *modelpt)
{
	srand(randnumber);
	modelpt->x = rand() % 54 + 7;
	modelpt->y = rand() % 34 + 13;
	setlinecolor(WHITE);
	setfillcolor(LIGHTGRAY);
	fillcircle(modelpt->x*SIZE + SIZE / 2, modelpt->y*SIZE + SIZE / 2, SIZE / 2);
	randnumber += 12;
}
void creatSmartFood()
{
	srand((unsigned)time(NULL));
	smartfood1.x = rand()  % 54 + 7;
	smartfood1.y = rand()  % 46 + 1;
	setlinecolor(WHITE);
	setfillcolor(LIGHTCYAN);
	fillcircle(smartfood1.x*SIZE + SIZE / 2, smartfood1.y*SIZE + SIZE / 2, SIZE / 2);
}
void coverAndClear(snakenode *pt)
{
	IMAGE img1;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\游戏背景素材\\蛇身遮盖素材.png"));
	snakenode *temp;
	temp = pt;
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillrectangle(temp->x*SIZE, temp->y*SIZE, temp->x*SIZE + SIZE, temp->y*SIZE + SIZE);
}
void snakePaint()
{
	IMAGE headpicL, headpicR, headpicU, headpicD, nodepic;
	loadimage(&headpicL, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\蛇头及蛇身素材\\向左的蛇头.png"));
	loadimage(&headpicR, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\蛇头及蛇身素材\\向右的蛇头.png"));
	loadimage(&headpicU, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\蛇头及蛇身素材\\向上的蛇头.png"));
	loadimage(&headpicD, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\蛇头及蛇身素材\\向下的蛇头.png"));
	loadimage(&nodepic, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\蛇头及蛇身素材\\蛇身.png"));
	snakenode *point;
	point = head;
	//setlinestyle(PS_NULL);
	switch (snakedir)
	{
	case 1:
		putimage(point->x*SIZE, point->y*SIZE, &headpicU);
		break;
	case 2:
		putimage(point->x*SIZE, point->y*SIZE, &headpicD);
		break;
	case 3:
		putimage(point->x*SIZE, point->y*SIZE, &headpicL);
		break;
	case 4:
		putimage(point->x*SIZE, point->y*SIZE, &headpicR);
		break;
	default:
		break;
	}
	point = point->next;
	while (point!=NULL)
	{
		putimage(point->x*SIZE, point->y*SIZE, &nodepic);
		point = point->next;
	} 
}
void dataCenterUI();
//初始化界面--以及各种UI界面
void welcomeUI()
{
	IMAGE img1,img2,img3,img4,img5,img6;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\开始界面-1.png"));
	putimage(0, 0, &img1);
	loadimage(&img2, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\难度选择-1.png"));
	loadimage(&img3, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\开始界面素材\\开始游戏-1.png"));
	loadimage(&img4, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\开始界面素材\\继续游戏-1.png"));
	loadimage(&img5, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\开始界面素材\\退出游戏-1.png"));
	loadimage(&img6, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\开始界面素材\\数据中心-1.png"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 359 && m.x <= 697)
		{
			if (m.y >= 173 && m.y <= 240)//第1个按钮
			{
				putimage(0, 0, &img3);
				if (m.mkLButton)
				{
					putimage(0, 0, &img2);
					levelUI();
					break;
				}
			}
			if (m.y >= 269 && m.y <= 337)//第2个按钮
			{
				putimage(0, 0, &img4);
				if (m.mkLButton)
				{
					fopen_s(&fpSave, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\存档文件\\tempdata.txt", "r");
					fscanf_s(fpSave, "%d", &pass);
					fscanf_s(fpSave, "%d", &score);
					fscanf_s(fpSave, "%d", &sleeptime);
					fscanf_s(fpSave, "%d", &level);
					fscanf_s(fpSave, "%d", &length);
					readRand();
					fclose(fpSave);
					switch (pass)
					{
					case 1:
						startup();
						break;
					case 2:
						secondStartup();
							break;
					case 3:
						thirdStartup();
						break;
					default:
						break;
					}
					startGame();
				}
			}
			if (m.y >= 367 && m.y <= 434)//第3个按钮
			{
				putimage(0, 0, &img5);
				if (m.mkLButton)
				{
					exit(0);
				}
			}
		}
		if (m.x >= 920 && m.x <= 1120)
		{
			if (m.y <= 480 && m.y >= 413)//数据中心按钮
			{
				putimage(0, 0, &img6);
				if (m.mkLButton)
				{
					dataCenterUI();
					
				}
			}
		}
	}
}
void levelUI()
{
	IMAGE img1, img2, img3,mouse;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\难度关卡素材\\简单-1.png"));
	loadimage(&img2, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\难度关卡素材\\普通-1.png"));
	loadimage(&img3, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\难度关卡素材\\困难-1.png"));
	loadimage(&mouse, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\鼠标素材-3.png"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 359 && m.x <= 697)
		{
			if (m.y >= 173 && m.y <= 240)//第1个按钮
			{
				putimage(0, 0, &img1);
				if (m.mkLButton)
				{
					level = 4;
					startup();
					break;
				}
			}
			if (m.y >= 269 && m.y <= 337)//第2个按钮
			{
				putimage(0, 0, &img2);
				if (m.mkLButton)
				{
					level = 5;
					startup();
					break;
				}
			}
			if (m.y >= 367 && m.y <= 434)//第3个按钮
			{
				putimage(0, 0, &img3);
				if (m.mkLButton)
				{
					level = 8;
					startup();
					break;
				}
			}
		}
	}
}
void dataShow()
{
	IMAGE img1;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\游戏背景素材\\新的计分板.png"));
	putimage(640,0,&img1);
	loadimage(&number[0], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\0.png"));
	loadimage(&number[1], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\1.png"));
	loadimage(&number[2], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\2.png"));
	loadimage(&number[3], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\3.png"));
	loadimage(&number[4], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\4.png"));
	loadimage(&number[5], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\5.png"));
	loadimage(&number[6], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\6.png"));
	loadimage(&number[7], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\7.png"));
	loadimage(&number[8], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\8.png"));
	loadimage(&number[9], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\9.png"));
	int bit_1, bit_2, bit_3;
	//当前分数的显示
	if (score >= 0)
	{
		bit_1 = score / 100;
		bit_2 = (score / 10) % 10;
		bit_3 = score % 10;
		putimage(790, 436, &number[bit_1]);
		putimage(807, 436, &number[bit_2]);
		putimage(824, 436, &number[bit_3]);
	}
	else
	{
		endGameUI();
	}
	readRank();
	//最高分的显示
	bit_1 = rankscore[0] / 100;
	bit_2 = (rankscore[0] / 10) % 10;
	bit_3 = rankscore[0] % 10;
	putimage(790, 395, &number[bit_1]);
	putimage(807, 395, &number[bit_2]);
	putimage(824, 395, &number[bit_3]);
	//食物分数的显示
	bit_1 = foodscore / 100;
	bit_2 = (foodscore / 10) % 10;
	bit_3 = foodscore  % 10;
	putimage(1062, 395, &number[bit_1]);
	putimage(1079, 395, &number[bit_2]);
	putimage(1096, 395, &number[bit_3]);
	//通关分数的显示
	passscore = pass * 10;
	bit_1 = passscore / 100;
	bit_2 = (passscore / 10) % 10;
	bit_3 = passscore % 10;
	putimage(1062, 436, &number[bit_1]);
	putimage(1079, 436, &number[bit_2]);
	putimage(1096, 436, &number[bit_3]);
}
void dataCenterShow()
{
	loadimage(&number[0], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\0.png"));
	loadimage(&number[1], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\1.png"));
	loadimage(&number[2], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\2.png"));
	loadimage(&number[3], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\3.png"));
	loadimage(&number[4], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\4.png"));
	loadimage(&number[5], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\5.png"));
	loadimage(&number[6], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\6.png"));
	loadimage(&number[7], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\7.png"));
	loadimage(&number[8], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\8.png"));
	loadimage(&number[9], _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数字素材\\9.png"));
	readRank();
	int bit_1, bit_2, bit_3;
	for (i = 0; i < 3; i++)
	{
		bit_1 = rankscore[i] / 100;
		bit_2 = (rankscore[i] / 10) % 10;
		bit_3 = rankscore[i] % 10;
		putimage(505, 100 + i * 120, &number[bit_1]);
		putimage(525, 100 + i * 120, &number[bit_2]);
		putimage(545, 100 + i * 120, &number[bit_3]);
	}
}
void dataCenterUI()
{
	IMAGE img1,img2;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数据中心素材\\数据中心-1.png"));
	loadimage(&img2, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\数据中心素材\\数据中心-2.png"));
	putimage(0, 0, &img1);
	MOUSEMSG m;
	dataCenterShow();
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 461 && m.x <= 660)
		{
			if (m.y >= 413 && m.y <= 480)
			{
				//putimage(0, 0, &img2);
				if (m.mkLButton)
				{
					break;
				}
			}
			else
			{
				dataCenterShow();
			}
		}
		else
		{
			dataCenterShow();
		}
	}
}
void endGameUI()
{
	IMAGE img1;
	MOUSEMSG m;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\结束界面素材\\结束界面.png"));
	putimage(0, 0, &img1);
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 629 && m.x <= 971 && m.y >= 306 && m.y <= 373)
		{
			if (m.mkLButton)
			{
				writeRank();
				writeRand();
				freerom();
				closegraph();
				exit(0);
			}
		}
		else if (m.x >= 149 && m.x <= 488 && m.y >= 306 && m.y <= 373)
		{
			if (m.mkLButton)
			{
				length = 4;
				score = 0;
				pass = 0;
				randnumber += 10;
				main();
			}
		}
	}
}
void saveGameUI()
{
	IMAGE img1;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\存档文件\\存档界面.png"));
	putimage(0, 0, &img1);
	fopen_s(&fpSave, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\存档文件\\tempdata.txt", "w");
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 629 && m.x <= 971 && m.y >= 306 && m.y <= 373)
		{
			if (m.mkLButton)
			{
				exit(0);
			}
		}
		else if (m.x >= 149 && m.x <= 488 && m.y >= 306 && m.y <= 373)
		{
			if (m.mkLButton)
			{
				fprintf_s(fpSave, "%d\n", pass);
				fprintf_s(fpSave, "%d\n", score);
				fprintf_s(fpSave, "%d\n", sleeptime);
				fprintf_s(fpSave, "%d\n", level);
				fprintf_s(fpSave, "%d\n", length);
				writeRank();
				writeRand();
				exit(0);
			}
		}
	}
	fclose(fpSave);
}
//数据初始化函数
void startup()
{
	sleeptime = 85 - level * 5;
	IMAGE whitebackground;
	loadimage(&whitebackground,_T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\游戏背景素材\\纯白背景.png"));
	putimage(0, 0, &whitebackground);
	//打印边框
	for (i = 0; i < GAMEFRAME_WIDTH; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 0, (i + 1)*SIZE, SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, (FRAME_HEIGHTH - 1)*SIZE, (i + 1)*SIZE, (FRAME_HEIGHTH )*SIZE);
	}
	for (j = 0; j < FRAME_HEIGHTH; j++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(0,j*SIZE,SIZE,(j+1)*SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle((GAMEFRAME_WIDTH - 1)*SIZE, j*SIZE, GAMEFRAME_WIDTH*SIZE, (j + 1)*SIZE);
	}
	//初始化蛇身
	iniSnake();
	//打印蛇身
	snakePaint();
	//打印各类道具
	readRand();
	creatFood();
	creatSmartFood();
	iniProp();
	randnumber += 88;
}
//第二关的初始化
void secondStartup()
{
	randnumber += 26;
	sleeptime = 70 - level * 5;
	IMAGE whitebackground;
	loadimage(&whitebackground, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\游戏背景素材\\纯白背景.png"));
	putimage(0, 0, &whitebackground);
	//打印边框
	for (i = 0; i < GAMEFRAME_WIDTH; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 0, (i + 1)*SIZE, SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, (FRAME_HEIGHTH - 1)*SIZE, (i + 1)*SIZE, (FRAME_HEIGHTH)*SIZE);
	}
	for (j = 0; j < FRAME_HEIGHTH; j++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(0, j*SIZE, SIZE, (j + 1)*SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle((GAMEFRAME_WIDTH - 1)*SIZE, j*SIZE, GAMEFRAME_WIDTH*SIZE, (j + 1)*SIZE);
	}
	for (i = 5; i < GAMEFRAME_WIDTH-5; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 8 * SIZE, (i + 1)*SIZE, 8 * SIZE +SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 40*SIZE, (i + 1)*SIZE, 41*SIZE);
	}
	snakedir = 4;
	length = 4;
	//初始化蛇身
	iniSnake();
	//打印蛇身
	snakePaint();
	//打印各类道具
	readRand();
	creatFood();
	creatSmartFood();
	iniProp();
	randnumber += 88;
	
}
//第三关初始化
void thirdStartup()
{
	randnumber += 23;
	sleeptime = 65 - level * 5;
	IMAGE whitebackground;
	loadimage(&whitebackground, _T("G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\游戏背景素材\\纯白背景.png"));
	putimage(0, 0, &whitebackground);
	//打印边框
	for (i = 0; i < GAMEFRAME_WIDTH; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, 0, (i + 1)*SIZE, SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(i*SIZE, (FRAME_HEIGHTH - 1)*SIZE, (i + 1)*SIZE, (FRAME_HEIGHTH)*SIZE);
	}
	for (j = 0; j < FRAME_HEIGHTH; j++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(0, j*SIZE, SIZE, (j + 1)*SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle((GAMEFRAME_WIDTH - 1)*SIZE, j*SIZE, GAMEFRAME_WIDTH*SIZE, (j + 1)*SIZE);
	}
	for (i = 5; i < FRAME_HEIGHTH - 5; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(8*SIZE, i * SIZE, 9*SIZE, i * SIZE + SIZE);
		setlinecolor(WHITE);
		setfillcolor(BLUE);
		fillrectangle(56*SIZE, i * SIZE, 57*SIZE, (i+1) * SIZE);
	}
	snakedir = 4;
	length = 4;
	//初始化蛇身
	iniSnake();
	//打印蛇身
	snakePaint();
	//打印各类道具
	readRand();
	creatFood();
	creatSmartFood();
	iniProp();
	randnumber += 88;
}
//写入随机数
void writeRand()
{
	fopen_s(&fpRand, "C:\\Users\\Lenovo\\Desktop\\文档\\rand.txt", "w");
	fprintf_s(fpRand, "%d\n", randnumber);
	fclose(fpRand);
}
//读取随机数
void readRand()
{
	fopen_s(&fpRand, "C:\\Users\\Lenovo\\Desktop\\文档\\rand.txt", "r");
	fscanf_s(fpRand, "%d", &randnumber);
	fclose(fpRand);
}
//写入排行榜
void writeRank()
{
	fopen_s(&fpRank, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\rank.txt","w");
	rankscore[9] = score;
	sortRank(rankscore);
	for (i = 0; i < 10; i++)
	{
		fprintf_s(fpRank, "%d\n", rankscore[i]);
	}
	fclose(fpRank);
}
//读取排行榜
void readRank()
{
	fopen_s(&fpRank, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\rank.txt", "r");
	for (i = 0; i < 10; i++)
	{
		fscanf_s(fpRank, "%d", &rankscore[i]);
	}
	fclose(fpRank);
}
void sortRank(int a[10])
{
	int maxnumber,tempnumber;
	maxnumber = a[0];
	for (j = 0; j < 10; j++)
	{
		for (i = j; i < 10; i++)
		{
			if (a[i] > maxnumber)
			{
				tempnumber = a[i];
				a[i] = maxnumber;
				maxnumber = tempnumber;
			}
		}
		a[j] = maxnumber;
		maxnumber = -10000;
	}
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
		creatPoison(temppoison);
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
			_getch();
			exit(0);
		}
		for (i = 0; i <= len; i++)
		{
			coverAndClear(temp->next);
			free(temp->next);
			temp->next = NULL;
			temp = temp->previous;
		}
		creatBoom(tempboom);
	}
	else if (check == 4)
	{
		endGameUI();
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
						Sleep(sleeptime);
					}
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
						Sleep(sleeptime);
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
						Sleep(sleeptime);
					}
					while (head->y != food_y)
					{
						snakedir = 1;
						snakeMove();
						Sleep(sleeptime);
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
						Sleep(sleeptime);
					}
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
						Sleep(sleeptime);
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
						Sleep(sleeptime);
					}
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
						Sleep(sleeptime);
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
						Sleep(sleeptime);
					}
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
						Sleep(sleeptime);
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 3;
						snakeMove();
						Sleep(sleeptime);
					}
					while (head->y != food_y)
					{
						snakedir = 2;
						snakeMove();
						Sleep(sleeptime);
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
						Sleep(sleeptime);
					}
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
						Sleep(sleeptime);
					}
				}
				else
				{
					while (head->x != food_x)
					{
						snakedir = 4;
						snakeMove();
						Sleep(sleeptime);
					}
					while (head->y != food_y)
					{
						snakedir = 1;
						snakeMove();
						Sleep(sleeptime);
					}
				}
			}
		}

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
		biteItself();
	}
}
int checkMove(snakenode *checkpoint)//检查函数，判断蛇的移动是否合法
{
	poison *poisonpt;
	boom *boompt;
	poisonpt = Poison;
	boompt = Boom;
	while (boompt != NULL)
	{
		if (checkpoint->x == boompt->x&&checkpoint->y == boompt->y)
		{
			tempboom = boompt;
			score -= 2 * length;
			sleeptime += 2;
			return 3;
		}
		boompt = boompt->next;
	}
	while (poisonpt != NULL)
	{
		if (checkpoint->x == poisonpt->x&&checkpoint->y == poisonpt->y)
		{
			temppoison = poisonpt;
			score += poisonscore;
			sleeptime += 2;
			return 2;
		}
		poisonpt = poisonpt->next;
	}
	if (checkpoint->x == food1.x&&checkpoint->y == food1.y)
	{
		score += foodscore;
		sleeptime -= 4;
		return 1;
	}
	else if (checkpoint->x == 0 || checkpoint->x == 63 || checkpoint->y == 0 || checkpoint->y == 47)
	{
		writeRank();
		writeRand();
		return 4;
	}
	else if (pass == 2)
	{

		if (checkpoint->x >= 5 && checkpoint->x <= 59)
		{
			if (checkpoint->y == 8 || checkpoint->y == 40)
			{
				writeRank();
				writeRand();
				return 4;
			}
		}
	}
	else if (pass == 3)
	{
		if (checkpoint->y >= 5 && checkpoint->y <= 42)
		{
			if (checkpoint->x == 8 || checkpoint->x == 56)
			{
				writeRank();
				writeRand();
				return 4;
			}
		}
	}
	else if (checkpoint->x == smartfood1.x&&checkpoint->y ==smartfood1.y)
	{
		return 5;
	}
	else
	{
		return 0;//上面没有运行则到了这里肯定会结束，所以后面的代码会失效！！！！！！！！！
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
			return 0;
			break;
		}
		checkpoint = checkpoint->next;
	}
}
void biteItself()
{
	snakenode *tempnode;
	tempnode = head->next;
	while (tempnode!=NULL)
	{
		if (tempnode->x == head->x&&tempnode->y == head->y)
		{
			endGameUI();
		}
		tempnode = tempnode->next;
	}
}
//道具检查函数，检查是否生成在同一位置
int checkProp()
{
	return -1;
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
		else if(input==27)
		{
			saveGameUI();
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
		poisonTwinkle_1();
		snakePaint();
		dataShow();
		poisonTwinkle_2();
		biteItself();
		if (score >= passscore)
		{
			pass=pass+1;
			if (pass == 2)
			{
				secondStartup();
			}
			else if (pass == 3)
			{
				thirdStartup();
			}
		}
		if (score >= passscore && pass > 3)
		{
			endGameUI();
		}
		
	}
}
void freerom()
{
	while (head!=NULL)
	{
		free(head);
		head = head->next;
	}
}
//主函数
int main()
{
	initgraph(1120, 480);	
	welcomeUI();
	startGame();
}	
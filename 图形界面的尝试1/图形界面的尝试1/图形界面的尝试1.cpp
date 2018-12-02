// 图形界面的尝试1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>




int main()
{
	initgraph(640, 640);
	IMAGE img1;
	loadimage(&img1, _T("G:\\图片\\Saved Pictures\\test1.jpg"));
	putimage(0, 0, &img1);
	getchar();
	closegraph();
}
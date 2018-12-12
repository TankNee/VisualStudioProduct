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
	FILE *fp;
	fopen_s(&fp, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\道具素材\\text.txt", "w");
	int i;
	int s[3] = { 4,5,94564 };
	for (i = 0; i < 3; i++)
	{
		fprintf_s(fp, "%d\n", s[i]);
	}
	fclose(fp);
	fopen_s(&fp, "G:\\图片\\Saved Pictures\\贪吃蛇游戏素材\\道具素材\\text.txt", "r");
	int  n[3];
	for (i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%d", &n[i]);
	}
	for (i = 0; i < 3; i++)
	{
		printf_s("%d\n", n[i]);
	}
	fclose(fp);
}
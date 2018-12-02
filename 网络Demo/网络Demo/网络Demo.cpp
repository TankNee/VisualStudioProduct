#include"pch.h"
#include<stdio.h>
#include<graphics.h>
#include<conio.h>


int main()
{
	initgraph(640, 480);
	char s[10];
	InputBox(s,  20, "请输入半径");
	int r;
	sscanf_s(s, "%d", &r);
	circle(100, 100, r);
	getchar();
	closegraph();
}
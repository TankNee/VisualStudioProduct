#include"pch.h"
#include<stdio.h>
#include<graphics.h>
#include<conio.h>


int main()
{
	initgraph(640, 480);

	setlinecolor(WHITE);
	setfillcolor(RED);

	 BeginBatchDraw();
	for (int i = 50; i < 600; i++)
	{
		circle(i, 100, 40);
		floodfill(i, 100, WHITE);
		 FlushBatchDraw();
		Sleep(10);
		cleardevice();
	}

	EndBatchDraw();

	closegraph();

}
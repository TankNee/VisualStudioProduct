// 图形界面的尝试1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>




int main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	MOUSEMSG m;						// 定义鼠标消息
	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:		// 鼠标移动的时候画红色的小点
			putpixel(m.x, m.y, RED);
			break;

		case WM_LBUTTONDOWN:	// 如果点左键的同时按下了 Ctrl 键
			if (m.mkCtrl)		// 画一个大方块
				rectangle(m.x - 10, m.y - 10, m.x + 10, m.y + 10);
			else				// 画一个小方块
				rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			break;

		case WM_RBUTTONUP:
			return 0;				// 按鼠标右键退出程序
		}
	}

	// 关闭图形窗口
	closegraph();
}
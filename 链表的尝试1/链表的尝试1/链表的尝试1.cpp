

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TSIZE 45
struct film
{
	char title[TSIZE];
	int rating;
	struct film * next;
};
char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');//strchr的作用是可以查找字符串s中首次出现字符c的位置。
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (getchar() != '\n')
			{
				continue;
			}
		}
	}
	return ret_val;
}
char * s_gets(char * st, int n);
int main(void)
{
	struct film *head = NULL;
	struct film * prev=NULL, *current;
	char input[TSIZE];
	//收集并储存信息
	puts("Enter the first movie title :");
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		current = (struct film *) malloc(sizeof(struct film));
		if (head == NULL)
		{
			head = current;
		}
		else
		{
			prev->next = current;
		}
		current->next = NULL;
		strcpy_s(current->title, input);
		puts("Enter your rating <0-10>:");
		scanf_s("%d", &current->rating);
		while (getchar()!='\n')
		{
			continue;
		}
		puts("Enter next movie title (empty line to stop)");
		prev = current;
	}
	//显示电影列表
	if (head == NULL)
	{
		printf("No data entered");
	}
	else
	{
		printf("Here is the movie list:\n");
	}
	current = head;
	while (current!=NULL)
	{
		printf("Movies:%s Rating：%d\n", current->title, current->rating);
		current = current->next;
	}
	current = head;
	while (current != NULL)
	{
		current = head;
		head = current->next;
		free(current);
	}
	printf("Bye!\n");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Node
{
	char name[10];
	int score;
	struct Node *next;
};

typedef struct Node ListNode;

ListNode *CreateList(int n)
{
	int i;
	ListNode *head;
	ListNode *p, *pre;
	head = (ListNode *)malloc(sizeof(ListNode));
	head->next = NULL;
	pre = head;
	for (i = 1; i <=n; i++)
	{
		printf("input name of the %d student:", i);
		p = (ListNode *)malloc(sizeof(ListNode));
		scanf("%s", &p->name);
		printf("input score of the %d student:", i);
		scanf("%d", &p->score);
		pre->next = p;
		pre = p;
	}
	pre->next = NULL;
	return head;
}
void PrintList(ListNode *h)
{
	ListNode *p;
	p = h->next;
	while (p)
	{
		printf("%s,%d", p->name, p->score);
		p=p->next;
		printf("\n");
	}
}
void InsertList(ListNode *h, int i, char name[], int e, int n)
{
	ListNode *q, *p;
	int j;
	if (i<1 || i>n + 1)
		printf("Error!Please input again.\n");
	else
	{
		j = 0;
		p = h;
		while (j < i - 1)
		{
			p = p->next;
			j++;
		}
		q = (ListNode *)malloc(sizeof(ListNode));
		strcpy(q->name, name);
		q->score = e;
		q->next = p->next;
		p->next = q;
	}
}
void DeleteList(ListNode *h, int i, int n)
{
	ListNode *p, *q;
	int j;
	char name[10];
	int score;
	if (i<1 || i>n)
		printf("Error!Please input again.\n");
	else
	{
		j = 0;
		p = h;
		while (j < i - 1)
		{
			p = p->next;
			j++;
		}
		q = p->next;
		p->next = q->next;
		strcpy(name, q->name);
		score = q->score;
		free(q);
		printf("name=%s,score=%d", name, score);
	}
}
void main()
{
	ListNode *h;//h指向结构体NODE
	int i = 1, n, score;
	char name[10];

	while (i)
	{
		/*输入提示信息*/
		printf("1--建立新的链表\n");
		printf("2--添加元素\n");
		printf("3--删除元素\n");
		printf("4--输出当前表中的元素\n");
		printf("0--退出\n");

		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("n=");   /*输入创建链表结点的个数*/
			scanf("%d", &n);
			h = CreateList(n);/*创建链表*/
			printf("list elements is : \n");
			PrintList(h);
			break;

		case 2:
			printf("input the position. of insert element:");
			scanf("%d", &i);
			printf("input name of the student:");
			scanf("%s", name);
			printf("input score of the student:");
			scanf("%d", &score);
			InsertList(h, i, name, score, n);
			printf("list elements is:\n");
			PrintList(h);
			break;

		case 3:
			printf("input the position of delete element:");
			scanf("%d", &i);
			DeleteList(h, i, n);
			printf("list elements in : \n");
			PrintList(h);
			break;

		case 4:
			printf("list element is : \n");
			PrintList(h);
			break;
		case 0:
			return;
			break;
		default:
			printf("ERROR!Try again!\n");
		}
	}
	system("pause");
	return;
}
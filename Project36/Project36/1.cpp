#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Node {
	char name[10];
	int score;
	struct Node *next;
};

typedef struct Node ListNode;


//在链表的末端插入新的节点，建立链表
ListNode *CreateList(int n)
{
	ListNode *head;//指向头节点指针
	ListNode *p=NULL, *pre;
	int i;
	head = (ListNode *)malloc(sizeof(ListNode));//为头节点分配内存空间
	head->next = NULL;//将头节点的指针域清空
	pre = head;//先将头节点首地址赋给中间变量pre
	for (i = 1; i <= n; i++)
	{
		printf("input name of the %d student:", i);//打印出第几个人的名字
		p = (ListNode *)malloc(sizeof(ListNode));//为要插入的节点分配内存空间p指向新插入节点的首地址
		scanf("%s", &p->name);//输入姓名
		printf("input score of the %d student:", i);
		scanf("%d", &p -> score);//输入分数
		pre->next = p;
		pre = p;
	}
	p->next = NULL;
	return head;
}

void PrintList(ListNode *h)
{
	ListNode *p;
	p = h->next;
	while (p)
	{
		printf("%s,%d", p->name, p->score);
		p = p->next;
		printf("\n");
	}
}

/*----------------------插入链表结点--------------------------*/
/*--------------------------------------------------------------------
函数名称:InsertList(ListNode *h,int i,char name[],int e,int n)
函数功能:插入链表结点
入口参数: h: 头结点地址 i:插入到第几个结点 name:插入
结点的姓名 e:插入结点的分数 n:
链表中结点的个数
除下头结点外的个数

出口参数:
--------------------------------------------------------------------*/
void InsertList(ListNode *h, int i, char name[], int e, int n)
{
	ListNode *q, *p;
	int j;
	if (i<1 || i>n + 1)
		printf("Error:please input again.\n");
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
/*--------------------------------------------------------------------
函数名称:DeleteList(ListNode *h, int i, int n)
函数功能:删除链表结点
入口参数: h: 头结点地址 i:要删除的结点所在位置
n:
链表中结点的个数除下头结点外的个数

出口参数:
--------------------------------------------------------------------*/

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
		printf("name=%s,score=%d\n", name, score);
	}
}


void main()
{
	ListNode *h=NULL;
	int i = 1, n, score;
	char name[10];
	while (i) {
		printf("1--建立新的链表\n");
		printf("2--添加元素\n");
		printf("3--删除元素\n");
		printf("4--输出当前表中的元素\n");
		printf("0--退出\n");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("n=");
			scanf("%d", &n);
			h = CreateList(n);
			printf("list elements is:\n");
			PrintList(h);
			break;

		case 2:
			printf("input the position.of insert element:");
			scanf("%d", &i);
			printf("input name of the student:");
			scanf("%d", &score);
			InsertList(h, i, name, score, n);
			break;
		case 3:
			printf("input the position of delete element:");
			scanf("%d", &i);
			DeleteList(h, i, n);
			printf("list elements in:\n");
			PrintList(h);
			break;
		case 4:
			printf("list element is:\n");
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
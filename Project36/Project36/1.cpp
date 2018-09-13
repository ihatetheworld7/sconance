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


//�������ĩ�˲����µĽڵ㣬��������
ListNode *CreateList(int n)
{
	ListNode *head;//ָ��ͷ�ڵ�ָ��
	ListNode *p=NULL, *pre;
	int i;
	head = (ListNode *)malloc(sizeof(ListNode));//Ϊͷ�ڵ�����ڴ�ռ�
	head->next = NULL;//��ͷ�ڵ��ָ�������
	pre = head;//�Ƚ�ͷ�ڵ��׵�ַ�����м����pre
	for (i = 1; i <= n; i++)
	{
		printf("input name of the %d student:", i);//��ӡ���ڼ����˵�����
		p = (ListNode *)malloc(sizeof(ListNode));//ΪҪ����Ľڵ�����ڴ�ռ�pָ���²���ڵ���׵�ַ
		scanf("%s", &p->name);//��������
		printf("input score of the %d student:", i);
		scanf("%d", &p -> score);//�������
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

/*----------------------����������--------------------------*/
/*--------------------------------------------------------------------
��������:InsertList(ListNode *h,int i,char name[],int e,int n)
��������:����������
��ڲ���: h: ͷ����ַ i:���뵽�ڼ������ name:����
�������� e:������ķ��� n:
�����н��ĸ���
����ͷ�����ĸ���

���ڲ���:
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
��������:DeleteList(ListNode *h, int i, int n)
��������:ɾ��������
��ڲ���: h: ͷ����ַ i:Ҫɾ���Ľ������λ��
n:
�����н��ĸ�������ͷ�����ĸ���

���ڲ���:
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
		printf("1--�����µ�����\n");
		printf("2--���Ԫ��\n");
		printf("3--ɾ��Ԫ��\n");
		printf("4--�����ǰ���е�Ԫ��\n");
		printf("0--�˳�\n");
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
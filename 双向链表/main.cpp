#include <stdio.h>
#include <stdlib.h>

typedef struct line {
	struct line *prior;
	int data;
	struct line *next;
}line;

line *initLine(line *head);
line *insertLine(line *head, int data, int add);
line *delLine(line *head, int data);
int selectElem(line *head, int elem);
line *amendElem(line *p, int add, int newElem);
void display(line *head);
int main()
{
	line *head = nullptr;
	head = initLine(head);
	display(head);
	head = insertLine(head, 7, 3);
	display(head);
	head = delLine(head, 1);
	display(head);
	printf("元素3的位置是：%d\n", selectElem(head, 3));
	head = amendElem(head, 3, 6);
	display(head);
	getchar();
	return 0;
}

line *initLine(line *head)
{
	head = new line();
	head->prior = nullptr;
	head->next = nullptr;
	head->data = 1;
	line *list = head;
	for (int i = 2; i <= 5; ++i)
	{
		line *body = new line();
		body->prior = nullptr;
		body->data = i;
		body->next = nullptr;

		list->next = body;
		body->prior = list;
		list = list->next;
	}
	return head;
}

line *insertLine(line *head, int data, int add)
{
	line *temp = new line();
	temp->data = data;
	temp->prior = nullptr;
	temp->next = nullptr;
	if (add == 1)
	{
		temp->next = head;
		head->prior = temp;
		head = temp;
	}
	else {
		line *body = head;
		for (int i = 1; i < add - 1; ++i)
		{
			body = body->next;
		}
		if (body->next == nullptr)
		{
			body->next = temp;
			temp->prior = body;
		}
		else
		{
			body->next->prior = temp;
			temp->next = body->next;
			body->next = temp;
			temp->prior = body;
		}
	}
	return head;
}

line *delLine(line *head, int data)
{
	line *temp = head;
	int i = 1;
	while (temp)
	{
		if ((i == 1) && (temp->data == data))
		{
			temp->next->prior = nullptr;
			temp = temp->next;
			head = temp;
			return head;
		}
		else if (temp->data == data)
		{
			temp->prior->next = temp->next;
			temp->next->prior = temp->prior;
			free(temp);
			return head;
		}
		temp = temp->next;
		++i;
	}
	printf("链表中无该数据");
	return head;
}

int selectElem(line *head, int elem)
{
	line *t = head;
	int i = 1;
	while (t)
	{
		if (t->data == elem)
		{
			return i;
		}
		i++;
		t = t->next;
	}
	return -1;
}

line *amendElem(line *p, int add, int newElem)
{
	line *temp = p;
	for (int i = 1; i < add; i++)
	{
		temp = temp->next;
	}
	temp->data = newElem;
	return p;
}

void display(line *head)
{
	line *temp = head;
	while (temp)
	{
		if (temp->next == nullptr)
		{
			printf("%d\n", temp->data);
		}
		else
		{
			printf("%d->", temp->data);
		}
		temp = temp->next;
	}
}
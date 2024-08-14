#ifndef __QLIST_H__
#define __QLIST_H__

typedef struct list_t list;

struct list_t
{
	int data;
	list *next;
};

int push_qlist(int val, list **pin, list **pout);

int pop_qlist(list **pin, list **pout);

void print_qlist(list **pin, list **pout);

#endif
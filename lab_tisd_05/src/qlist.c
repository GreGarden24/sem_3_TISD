#include <stdio.h>
#include <stdlib.h>
#include "qlist.h"
#include "error.h"

int push_qlist(int val, list **pin, list **pout)
{
	list *node = malloc(sizeof(list));
	if (!node)
		return ERR_MEMORY;
	node->data = val;
	node->next = NULL;
	if (!*pin)
	{
		*pin = node;
		*pout = node;
	}
	else
	{
		(*pin)->next = node;
		*pin = (*pin)->next;
	}
	return EXIT_SUCCESS;
}

int pop_qlist(list **pin, list **pout)
{
	if (!*pout)
		return ERR_EMPTY;
	if (*pin == *pout)
		*pin = NULL;
	int rc = (*pout)->data;
	list *tmp = *pout;
	*pout = (*pout)->next;
	free(tmp);
	return rc;
}

void print_qlist(list **pin, list **pout)
{
	if (!*pout)
	{
		printf("Queue is empty!\n");
		return;
	}
	
	list *tpin = NULL, *tpout = NULL;
	while (*pout)
	{
		void *addr = *pout;
		int tmp = pop_qlist(pin, pout);
		printf("%d\t%p\n", tmp, addr);
		push_qlist(tmp, &tpin, &tpout);
	}
	while (tpout)
		push_qlist(pop_qlist(&tpin, &tpout), pin, pout);
}

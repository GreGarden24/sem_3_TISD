#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

node_t *create_node(int data) 
{
    node_t *node = malloc(sizeof(node_t));
    
    if (node)
    {
        node->data = data;
        node->next = NULL;
    }
    
    return node;
}

queue_t* push_back(queue_t *queue, node_t *node)
{
    if (!queue->top)
    {
        queue->top = node;
        queue->bot = node;
    }
    else
    {
        queue->bot->next = node;
        queue->bot = queue->bot->next;
    }

    return queue;
}

queue_t* pop_front(queue_t *queue)
{
    node_t *temp = queue->top->next;

    free(queue->top);
    queue->top = temp;

    return queue;
}

void init_queue(queue_t *queue)
{
    queue->bot = NULL;
    queue->top = NULL;
}

void free_queue(queue_t *queue)
{
    while (queue->top)
    {
        node_t *temp = queue->top;
        queue->top = queue->top->next;
        free(temp);
    }
}

void print_queue(queue_t queue)
{
    while (queue.top)
    {
        printf("%d ", queue.top->data);
        queue.top = queue.top->next;
    }
}

#ifndef __QUEUE__STRUCT__H__
#define __QUEUE__STRUCT__H__

typedef struct node node_t;

struct node
{
    int data;
    struct node *next;
};

typedef struct queue
{
    node_t *top;
    node_t *bot;
} queue_t;


#endif //__QUEUE__STRUCT__H__


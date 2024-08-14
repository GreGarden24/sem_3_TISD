#ifndef __QUEUE__H__
#define __QUEUE__H__

#include "queue_struct.h"

node_t* create_node(int data);
queue_t* push_back(queue_t *queue, node_t *node);
queue_t* pop_front(queue_t *queue);

void init_queue(queue_t *queue);
void free_queue(queue_t *queue);
void print_queue(queue_t queue);

#endif //__QUEUE__H__


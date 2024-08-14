#ifndef __GRAPH__H__
#define __GRAPH__H__

typedef struct graph
{
    int size;

    int** matrix;
    int** transpos_matrix;
} graph_t;

int create_graph(graph_t *graph);

void init_graph(graph_t *graph);
void free_graph(graph_t *graph);

void print_graph_matrix(graph_t graph);
void print_graph(graph_t *graph);

int is_connected(graph_t *graph);

#endif //__GRAPH__H__

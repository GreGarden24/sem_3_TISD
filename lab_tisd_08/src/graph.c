#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"
#include "queue.h"

static int** allocate_matrix(size_t n, size_t m)
{
    int **data = malloc(n * sizeof(int*) + n * m * sizeof(int));
    
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; ++i)
    {
        data[i] = (int*)((char*) data + n * sizeof(int*) + i * m * sizeof(int));
        for (size_t j = 0; j < m; ++j)
            data[i][j] = 0;
    }
    
    return data;
}

void free_graph(graph_t *graph)
{
    if (graph->matrix)
    {
        free(graph->matrix);
        graph->matrix = NULL;
    }
    if (graph->transpos_matrix)
    {
        free(graph->transpos_matrix);
        graph->transpos_matrix = NULL;
    }
}

void init_graph(graph_t *graph)
{
    graph->matrix = NULL;
    graph->transpos_matrix = NULL;
    graph->size = 0;
}

int create_graph(graph_t *graph)
{
    printf("Введите количество вершин в графе: ");

    if (scanf("%d", &(graph->size)) != 1 || graph->size < 1)
    {
        printf("\nНекорректное значение\n\n");
        fflush(stdin);
        return ERR_SIZE;
    }
    fflush(stdin);
    
    graph->matrix = allocate_matrix(graph->size, graph->size);
    graph->transpos_matrix = allocate_matrix(graph->size, graph->size);
    
    if (!graph->matrix || !graph->transpos_matrix)
    {
        free_graph(graph);
        
        return ERR_MEMORY;
    }
    
    int path;
    
    for (size_t i = 0; i < (size_t)graph->size; ++i)
    {
        printf("\n - Вершина %zu -\n", i);
        for (int j = 0; j < graph->size; ++j)
        {
            printf("\tПуть в вершину %d: ", j);
            if (scanf("%d", &path) != 1 || path < 0)
            {
                fflush(stdin);
                printf("Некорректное значение.\n");
                j--;
            }
            fflush(stdin);
            (graph->matrix)[i][j] = path;
            (graph->transpos_matrix)[j][i] = path;
        }
    }
    fflush(stdin);
    
    return OK;
}

void print_graph_matrix(graph_t graph)
{
    for (size_t i = 0; i < (size_t)graph.size; ++i)
    {
        for (size_t j = 0; j < (size_t)graph.size; ++j)
            printf("%d ", graph.matrix[i][j]);
        printf("\n");
    }
}

void print_graph(graph_t *graph)
{
    FILE *f = fopen("graph.gv", "w");

    fprintf(f, "digraph graph_pic {\n");

    for (size_t i = 0; i < (size_t)graph->size; ++i)
        for (size_t j = 0; j < (size_t)graph->size; ++j)
            if (graph->matrix[i][j] != 0)
                fprintf(f, "%zu -> %zu [label=\"%.1d\"];\n",
                        i, j, graph->matrix[i][j]);
    fprintf(f, "}\n");
    
    fclose(f);
}
    
static int dfs(graph_t *graph, int **matrix) // Поиск в глубину 
{
    int *visited = calloc(graph->size ,sizeof(int));

    if (!visited)
        return ERR_MEMORY;

    queue_t points;
    init_queue(&points);
    node_t* point = create_node(0);
    points = *push_back(&points, point);
    
    size_t index =  points.top->data;
    visited[index] = 1;
    
    while (points.top)
    {
        for (size_t i = 0; i < (size_t)graph->size; ++i)
        {
            if (i != index && matrix[index][i] && matrix[i][index] && !visited[i])
            {
                visited[i] = 1;
                point = create_node(i);
                points = *push_back(&points, point);

            }
            if (i != index && matrix[index][i] && !visited[i])
            {
                visited[i] = 1;
                point = create_node(i);
                points = *push_back(&points, point);
            }
        }
        points = *pop_front(&points);
        
        if (points.top)
            index = points.top->data;
    }
    
    if (points.top)
        free_queue(&points);
    
    int type = 0;
    
    for (size_t i = 0; i < (size_t)graph->size; ++i)
        if (visited[i] == 0)
            type = 1;
    free(visited);
    
    return type;
}

int is_connected(graph_t *graph)
{
    int connected = dfs(graph, graph->transpos_matrix);
    
    if (!connected)
        printf("\nГраф  является связным.\n\n");
    else if (connected == ERR_MEMORY)
        printf("\nОшибка выделения памяти.\n");
    else
        printf("\nГраф  не является связным.\n\n");
    
    return connected;
}


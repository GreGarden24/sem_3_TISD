#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "graph.h"

void get_cmd(short int *cmd);

int main(void)
{
    setbuf(stdout, NULL);
    
    print_info();
    print_menu();
    
    short int cmd = 1, rc = 0;
    int graph_created = 0;
    
    graph_t graph;
    init_graph(&graph);
    
    while (cmd)
    {
        print_note();
        get_cmd(&cmd);
        switch(cmd)
        {
            case(0):
                if (graph_created)
                    free_graph(&graph);
                printf("\nПрограмма завершена.\n");
                break;
            case(1):
                if (graph_created)
                    free_graph(&graph);
                if ((rc = create_graph(&graph)))
                    printf("\nНе удалось считать матрицу смежностей.\n");
                else
                {
                    graph_created = 1;
                    printf("\nМатрица успешно смежностей считана.\n");
                }
                break;
            case(2):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                    print_graph_matrix(graph);
                break;
            case(3):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                {
                    print_graph(&graph);
                    system("dot -Tpng graph.gv > graph.png");
                    system("open graph.png");
                }
                break;
            case(4):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                    is_connected(&graph);
                break;
            case(5):
                print_menu();
                break;
            default:
                printf("\nНекорректный номер команды.\n\n");
        }
    }
    return rc;
}

void get_cmd(short int *cmd)
{
    printf("%s", "\nВведите номер команды: ");
    int rc = fscanf(stdin, "%hd", cmd);
    if (rc != 1)
    {
        fflush(stdin);
        printf("%s", "\nВведите номер комманды: ");
        rc = fscanf(stdin, "%hd", cmd);
    }
    fflush(stdin);
}

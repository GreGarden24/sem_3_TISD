#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "list_proc.h"
#include "array_proc.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int push_list_stack(list_stack** head, char* word)
{
    list_stack* stack_elem = (list_stack*) malloc(sizeof(list_stack));
    if (stack_elem == NULL)
        return MEMORY_ERROR;

    stack_elem->previous = *head;
    strcpy(stack_elem->word, word);
    *head = stack_elem;

    return EXIT_SUCCESS;
}

int pop_list_stack(list_stack** head, char* word)
{
    if (*head == NULL)
        return MEMORY_ERROR;

    strcpy(word, (*head)->word);

    list_stack* stack_elem = *head;
    *head = (*head)->previous;
    free(stack_elem);
    
    return EXIT_SUCCESS;
}

int print_list_stack(list_stack* head)
{
    if (head == NULL)
        return EXIT_FAILURE;
    
    list_stack* stack_elem = head;
    printf("\n-----------------------------------------\n");
    printf("|                 LIST                  |\n");
    printf("-----------------------------------------\n");
    while (stack_elem != NULL)
    {
        printf("| %-20s | %p |\n", stack_elem->word, (void *) stack_elem); 
        stack_elem = stack_elem->previous;
    }
    
    printf("-----------------------------------------\n\n");
    return EXIT_SUCCESS;
}

int print_method_list_stack(list_stack** head, int mode)
{
    if (*head == NULL)
        return EXIT_FAILURE;

    char word_tmp[MAX_LENGHT + 1];
    if (mode)
        printf("List containment method:\n");
    while (*head != NULL)
    {
        pop_list_stack(head, word_tmp);
        for (int i = strlen(word_tmp) - 1; i >= 0; i--)
        {
            if (mode)
                printf("%c", word_tmp[i]);
        }
        if (mode)
            printf(" ");
    }
    if (mode)
            printf("\n");
    return EXIT_SUCCESS;
}

int print_free_memory(free_spaces free_memory)
{
    int size = free_memory.lenght;
    if (size == 0)
        return EXIT_FAILURE;

    printf("\n------------------\n");
    printf("|  FREED MEMORY  |\n");
    printf("------------------\n");
    while (size)
    {
        size--;
        printf("| %p |\n", (void*) free_memory.free[size]);
    }
    
    printf("------------------\n\n");
    return EXIT_SUCCESS;
}

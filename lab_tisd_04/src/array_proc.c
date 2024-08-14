#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "array_proc.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

int push_arr_stack(arr_stack* stack, char* word)
{
    if (stack->ptr_cur == stack->ptr_end)
        return MEMORY_ERROR;
    
    stack->ptr_cur += MAX_LENGHT + 1;
    strcpy(stack->ptr_cur, word);
    return EXIT_SUCCESS;
}

int pop_arr_stack(arr_stack* stack, char* word)
{
    if (stack->ptr_cur < stack->ptr_beg)
        return MEMORY_ERROR;

    strcpy(word, stack->ptr_cur);

    stack->ptr_cur -= MAX_LENGHT + 1;
    return EXIT_SUCCESS;
}

int print_arr_stack(arr_stack stack)
{
    if (stack.ptr_cur < stack.ptr_beg)
        return EXIT_FAILURE;
    
    char word_tmp[MAX_LENGHT + 1];
    printf("\n------------------------\n");
    printf("|        ARRAY         |\n");
    printf("------------------------\n");
    for (char* ptr_i = stack.ptr_cur; ptr_i >= stack.ptr_beg; ptr_i -= MAX_LENGHT + 1)
    {
        strcpy(word_tmp, ptr_i);
        printf("| %-20s |\n", ptr_i);
    }
    printf("------------------------\n\n");
    return EXIT_SUCCESS;
}

int print_method_arr_stack(arr_stack* stack, int mode)
{
    if (stack->ptr_cur < stack->ptr_beg)
        return EXIT_FAILURE;

    char word_tmp[MAX_LENGHT + 1];
    if (mode)
        printf("Array containment method:\n");
    while (stack->ptr_cur >= stack->ptr_beg)
    {
        pop_arr_stack(stack, word_tmp);
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
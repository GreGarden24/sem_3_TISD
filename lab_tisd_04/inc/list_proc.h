#ifndef __LIST_PROC_H__
#define __LIST_PROC_H__

#include "array_proc.h"

void input_flush(void);
void print_menu(void);

typedef struct list_stack
{
    struct list_stack* previous;
    char word[MAX_LENGHT];
} list_stack;

typedef struct
{
    size_t lenght;
    void* free[MAX_WORDS];
} free_spaces;


int push_list_stack(list_stack** head, char* word);
int pop_list_stack(list_stack** head, char* word);
int print_list_stack(list_stack* head);
int print_method_list_stack(list_stack** head, int mode);
int print_free_memory(free_spaces free_memory);

#endif // __LIST_PROC_H__
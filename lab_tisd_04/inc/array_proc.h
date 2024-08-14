#ifndef __ARRAY_PROC_H__
#define __ARRAY_PROC_H__

#define MAX_WORDS 10000
#define MAX_LENGHT 20


typedef struct
{
    char* ptr_beg;
    char* ptr_end;
    char* ptr_cur;
    char words[MAX_WORDS][MAX_LENGHT + 1];
} arr_stack;

int push_arr_stack(arr_stack* stack, char* word);
int pop_arr_stack(arr_stack* stack, char* word);
int print_arr_stack(arr_stack stack);
int print_method_arr_stack(arr_stack* stack, int mode);

#endif // __ARRAY_PROC_H__
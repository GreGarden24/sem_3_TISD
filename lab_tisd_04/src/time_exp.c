#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include "general_funcs.h"
#include "tree_funcs.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

tick_t tick(void)
{
	tick_t d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
void create_rand_words_txt(FILE* fsrc, int size)
{
    char temp_word[MAX_LENGHT + 1];
    int word_size = rand() % MAX_LENGHT + 1;
    int rand_char = 33;
    for (int i = 0; i < size; i++)
	{

        for (int j = 0; j < word_size; j++)
        {
            rand_char = rand() % ('z' - 'A') + 'A';
            temp_word[j] = (char) rand_char;
        }
        temp_word[word_size] = '\0';
        fprintf(fsrc, "%s\n", temp_word);
	    word_size = rand() % MAX_LENGHT + 1;
    }
}

void time_experiment_stack(int size, arr_stack* arr, list_stack** stack_head)
{
    int mem_array = sizeof(arr_stack);
    int mem_list = size * sizeof(list_stack) + sizeof(list_stack*);
    struct timespec t_beg, t_end;
    unsigned long long array_push_time = 0, list_push_time = 0;
	unsigned long long array_print_time, list_print_time;

    FILE* fsrc = fopen("rand_words.txt", "w");
    create_rand_words_txt(fsrc, size);
    fclose(fsrc);

    fsrc = fopen("rand_words.txt", "r");
    char tmp_word[MAX_LENGHT + 1];
    for (int i = 0; i < size; i++)
    {
        fscanf(fsrc, "%s", tmp_word);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
        push_arr_stack(arr, tmp_word);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	
        array_push_time += calc_elapsed_time(&t_beg, &t_end);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		push_list_stack(stack_head, tmp_word);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	
        list_push_time += calc_elapsed_time(&t_beg, &t_end);


    }
    fclose(fsrc);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
    print_method_arr_stack(arr, 0);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	
    array_print_time = calc_elapsed_time(&t_beg, &t_end);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
	print_method_list_stack(stack_head, 0);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	
    list_print_time = calc_elapsed_time(&t_beg, &t_end);
    
	printf("\nFor array method was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_array, (mem_array) / 1024.0, (mem_array) / 1024.0 / 1024.0);
    printf("\nFor list method was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_list, (mem_list) / 1024.0, (mem_list) / 1024.0 / 1024.0);

	printf("\nTime that was used to push stack in microseconds:\n");
	printf("| array: %15lld | list: %15lld |\n", array_push_time ,list_push_time);

    printf("\nTime that was used to print stack in microseconds:\n");
	printf("| array: %15lld | list: %15lld |\n", array_print_time ,list_print_time);

    
	FILE *fdst_arr, *fdst_list;
	fdst_arr = fopen("time_for_array.txt", "a+");
	fdst_list = fopen("time_for_list.txt", "a+");
	fprintf(fdst_arr, "%d %lld %d\n", size, array_print_time, mem_array);
	fprintf(fdst_list, "%d %lld %d\n", size, list_print_time, mem_list);
	fclose(fdst_arr);
	fclose(fdst_list);
}

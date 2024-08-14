#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "general_funcs.h"
#include "array_proc.h"
#include "list_proc.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int main(void)
{
	print_menu();
	int menu;
	arr_stack stack_array;
	stack_array.ptr_beg = *(stack_array.words);
	stack_array.ptr_end = *(stack_array.words + MAX_WORDS - 1);
	stack_array.ptr_cur = *(stack_array.words - 1);
	list_stack* stack_head = NULL;
	size_t list_len = 0;

	free_spaces free_memory;
	free_memory.lenght = 0;


	char word_tmp[MAX_LENGHT + 2];

	while(1)
	{	
		printf("Input command number: ");
		if (scanf("%d", &menu) != 1)
		{
			input_flush();
			printf("\nWrong menu option, try one more time!\n");
			continue;
		}
		input_flush();
		switch (menu)
		{
			case 0:                                                                  //выход
			{	
				print_method_list_stack(&stack_head, 0);
				printf("Shutting down program...\n");
				return EXIT_SUCCESS;
			}
			case 1:                                                                  //добавление слова
			{
				printf("Input word (<= 20 symbols): ");
				scanf("%s", word_tmp);
				input_flush();
				while (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\nTry one more time: ");
					scanf("%s", word_tmp);
					input_flush();
				}

				if (push_arr_stack(&stack_array, word_tmp) != EXIT_SUCCESS)
					printf("Array stack is overflowed!\n");

				if (list_len > MAX_WORDS)
				{
					printf("List stack is overflowed!\n");
					break;
				}
				else if (push_list_stack(&stack_head, word_tmp) != EXIT_SUCCESS)
					printf("Cant allocate more words!\n");
				else
				{
					list_len++;

					if (free_memory.lenght)
						(free_memory.lenght)--;
				}
				break;
			}
			case 2:                                                                  //удаление слова
			{
				void* tmp_ptr = (void*) stack_head;
				if (pop_arr_stack(&stack_array, word_tmp) != EXIT_SUCCESS)
					printf("Stack is empty!\n");
				
				else if (pop_list_stack(&stack_head, word_tmp) != EXIT_SUCCESS)
					printf("Stack is empty!\n");
				
				else
				{
					list_len--;
					(free_memory.lenght)++;

					free_memory.free[(free_memory.lenght) - 1] = tmp_ptr;
					printf("Freed memory : %p\n", free_memory.free[(free_memory.lenght) - 1]);
				}
				
				break;
			}
			case 3:                                                                  //печать всех слов
			{
				if (print_arr_stack(stack_array) != EXIT_SUCCESS)
					printf("Stack is empty!\n");

				else if (print_list_stack(stack_head) != EXIT_SUCCESS)
					printf("Stack is empty!\n");

				print_free_memory(free_memory);

				break;
			}
			case 4:                                                                  //Вывод слов в обратном порядке 
			{
				if (print_method_arr_stack(&stack_array, 1) != EXIT_SUCCESS)
					printf("Stack is empty!\n");
				
				else if (print_method_list_stack(&stack_head, 1) != EXIT_SUCCESS)
					printf("Stack is empty!\n");
					
				list_len = 0;
				free_memory.lenght = 0;

				break;
			}
			case 5:                                                                  //Сравнение времени
			{
				arr_stack stack_arr_time;
				stack_arr_time.ptr_beg = *(stack_arr_time.words);
				stack_arr_time.ptr_end = *(stack_arr_time.words + MAX_WORDS - 1);
				stack_arr_time.ptr_cur = *(stack_arr_time.words - 1);
				list_stack* stack_head_time = NULL;

				printf("Input words amount (<= 10000): ");
				while (scanf("%d", &menu) != 1 || menu <= 0 || menu > 10000)
				{
					input_flush();
					printf("\nWrong menu option, try one more time!\n");
				}
				input_flush();


				

				time_experiment_stack(menu, &stack_arr_time, &stack_head_time);

				

				break;
			}
			default:                                                                //Обработчик ошибочного меню
			{
				printf("\nWrong menu option, try one more time!\n");
				continue;
			}
		}
	}

	return EXIT_SUCCESS;
}

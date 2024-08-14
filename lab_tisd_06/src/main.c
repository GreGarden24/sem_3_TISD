#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "general_funcs.h"
#include "tree_funcs.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int main(void)
{
	print_menu();
	int menu;

	struct tree_node* init_tree = NULL;
	char word_tmp[MAX_LENGHT + 2];

	while(1)
	{	
		printf("\nInput command number: ");
		if (scanf("%d", &menu) != 1)
		{
			input_flush();
			printf("\nWrong menu option, try one more time!\n");
			continue;
		}
		input_flush();
		switch (menu)
		{
			case 0:                                                                  //Выход
			{	
				tree_free(init_tree);
				printf("Shutting down...\n");
				return EXIT_SUCCESS;
			}
			case 1:                                                                  //Считывание дерева из файла
			{	
				tree_free(init_tree);

				printf("Input file directory (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong file directory lenght!\n");
					continue;
				}

				FILE *fsrc = fopen(word_tmp, "r");
				if (fsrc == NULL)
				{
					printf("Cant open file!\n");
					continue;
				}

				init_tree = tree_file_read(fsrc);
				if (init_tree == NULL)
				{
					printf("File is damaged!\n");
					return FILE_ERROR;
				}
				fclose(fsrc);

				printf("File was succesfully readed.\n");
				
				break;
			}
			case 2:                                                                  //Добавление слова
			{
				struct tree_node* tmp_node;
				printf("Input word (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}

				char *new_word = malloc((strlen(word_tmp) + 1) * sizeof(char));
				if (new_word == NULL)
				{
					printf("Can't allocate new word!\n");
					return MEMORY_ERROR;
				}
				strncpy(new_word, word_tmp, strlen(word_tmp) + 1);

				tmp_node = node_create(new_word);
				if (tmp_node == NULL)
				{
					printf("Can't allocate new node!\n");
					return MEMORY_ERROR;
				}

				init_tree = node_insert(init_tree, tmp_node);
				printf("Word was successfully added.\n");
				break;
			}
			case 3:                                                                  //Удаление слова
			{
				if (init_tree == NULL)
				{
					printf("Can't delete elemnt from empty tree!\n");
					continue;
				}
				printf("Input word for delete (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}

				init_tree = node_delete(init_tree, word_tmp);
				printf("Word was successfully deleted.\n");

				break;
			}
			case 4:                                                                  //Поиск слова
			{
				struct tree_node* tmp_node = NULL;
				printf("Input word (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}

				tmp_node = node_search(init_tree, word_tmp);
				if (tmp_node != NULL)
				{
					printf("There's word in the tree.\n");
				}
				else
					printf("There's no such word in the tree.\n");

				break;
			}
			case 5:                                                                  //Печать всех слов
			{
				printf("\n");
				node_print(init_tree);
				printf("\n");
				break;
			}
			case 6:                                                                  //Поиск кол-ва слов начинающихся на букву
			{
				char c;
				int n = 0;
				printf("Input character for search: ");
				scanf("%c", &c);
				input_flush();
				printf("\n");
				tree_words_char_find(init_tree, c, &n, 1);
				printf("\n");
				printf("%d words was found.\n", n);
				continue;
			}
			case 7:                                                                  //Нарисовать дерево
			{
				char c;
				printf("Do you want to color words that start witch char?\n(input y/n): ");
				scanf("%c", &c);
				input_flush();
				if (c == 'y')
				{	
					printf("Input character for search: ");
					scanf("%c", &c);
					input_flush();
				}
				else
					c = 0;
				FILE* dot_f = fopen("words_tree.gv", "w+");
				tree_export_to_dot(dot_f, init_tree, c);
				fclose(dot_f);
				continue;
			}
			case 8:                                                                  //Сравнение времени
			{
				time_experiment();
				continue;
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "general_funcs.h"
#include "tree_funcs.h"
#include "time_exp.h"
#include "avl_funcs.h"
#include "ht_close_funcs.h"
#include "ht_open_funcs.h"


#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

#define STD_LEN 23

int main(void)
{
	print_menu();
	int menu;

	hash_t ht_close[1000];		// закрытая хэш-таблица
	int close_size = STD_LEN;	

	open_hash_t ht_open[1000];		// открытая хэш-таблица
	int open_size = STD_LEN;	

	node_t* init_tree = NULL;
	node_t* avl_tree = NULL;
	char word_tmp[MAX_LENGHT + 2];
	int choose = 0;

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
				tree_free(avl_tree);
				free_open_ht(ht_open, open_size);
				printf("Shutting down...\n");
				return EXIT_SUCCESS;
			}
			case 1:                                                                  //Считывание дерева из файла
			{	
				tree_free(init_tree);
				tree_free(avl_tree);

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

				fsrc = fopen(word_tmp, "r");
				if (fsrc == NULL)
				{
					printf("Cant open file!\n");
					continue;
				}

				avl_tree = tree_file_read(fsrc);
				if (avl_tree == NULL)
				{
					printf("File is damaged!\n");
					return FILE_ERROR;
				}
				avl_tree = tree_balance(avl_tree);
				fclose(fsrc);

				printf("File was succesfully readed.\n");
				
				break;
			}
			case 2:                                                                  //Добавление слова
			{
				node_t* tmp_node;
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


				tmp_node = node_create(new_word);
				if (tmp_node == NULL)
				{
					printf("Can't allocate new node!\n");
					return MEMORY_ERROR;
				}
				
				avl_tree = node_insert(avl_tree, tmp_node);
				avl_tree = tree_balance(avl_tree);
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
				avl_tree = avl_remove(avl_tree, word_tmp);
				printf("Word was successfully deleted.\n");

				break;
			}
			case 4:                                                                  //Поиск слова
			{
				node_t* tmp_node = NULL;
				printf("Input word (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}
				
				int bin_cmp = 0, avl_cmp = 0;
				tmp_node = node_search(init_tree, word_tmp, &bin_cmp);
				tmp_node = node_search(avl_tree, word_tmp, &avl_cmp);
				if (tmp_node != NULL)
				{
					printf("Word was found with:\n%d compares in bibary tree\n%d compares in AVL tree.\n", bin_cmp, avl_cmp);
				}
				else
				{
					printf("There's no such word in the tree.\n");
					printf("Do you want to add it? Type y/n:\n");
					char c;
					scanf("%c", &c);
					input_flush();
					if (c == 'y')
					{	
						tmp_node = node_create(word_tmp);
						if (tmp_node == NULL)
						{
							printf("Can't allocate new node!\n");
							return MEMORY_ERROR;
						}

						init_tree = node_insert(init_tree, tmp_node);


						tmp_node = node_create(word_tmp);
						if (tmp_node == NULL)
						{
							printf("Can't allocate new node!\n");
							return MEMORY_ERROR;
						}
						
						avl_tree = node_insert(avl_tree, tmp_node);
						avl_tree = tree_balance(avl_tree);
						printf("Word was successfully added.\n");
					}
				}

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
				int bin_cmp = 0, avl_cmp = 0;
				tree_words_char_find(init_tree, c, &n, 1, &bin_cmp);
				n = 0;
				tree_words_char_find(avl_tree, c, &n, 0, &avl_cmp);
				printf("\n");
				printf("%d words was found with:\n%d compares in bibary tree\n%d compares in AVL tree.\n", n, bin_cmp, avl_cmp);
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
				FILE* dot_f = fopen("bin_tree.gv", "w+");
				tree_export_to_dot(dot_f, init_tree, c);
				fclose(dot_f);

				dot_f = fopen("avl_tree.gv", "w+");
				tree_export_to_dot(dot_f, avl_tree, c);
				fclose(dot_f);

				continue;
			}
			case 11:                                                                  //Считывание таблиц из файла
			{
				init_close_ht(ht_close, close_size);
				close_size = STD_LEN;

				free_open_ht(ht_open, open_size);
				open_size = STD_LEN;

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

				printf("What hash function do you want? Type 1 or 2: ");
				scanf("%d", &choose);
				if (choose != 1 && choose != 2)
				{
					printf("Wrong function number, choosed 1.\n");
					choose = 1;
				}
				int old_close_size = close_size;
				int old_open_size = open_size;
				if (choose == 1)
				{
					if (hread_close_ht(fsrc, ht_close, &close_size, hash_func_1) != EXIT_SUCCESS)
					{
						printf("Cant read close hash table from the file!\n");
						fclose(fsrc);
						return FILE_ERROR;
					}
					rewind(fsrc);
					if (hread_open_ht(fsrc, ht_open, &open_size, hash_func_1) != EXIT_SUCCESS)
					{
						printf("Cant read open hash table from the file!\n");
						fclose(fsrc);
						return FILE_ERROR;
					}
				}
				else
				{
					if (hread_close_ht(fsrc, ht_close, &close_size, hash_func_2) != EXIT_SUCCESS)
					{
						printf("Cant read close hash table from the file!\n");
						fclose(fsrc);
						return FILE_ERROR;
					}
					rewind(fsrc);
					if (hread_open_ht(fsrc, ht_open, &open_size, hash_func_2) != EXIT_SUCCESS)
					{
						printf("Cant read open hash table from the file!\n");
						fclose(fsrc);
						return FILE_ERROR;
					}
				}
				if (old_close_size != close_size)
					printf("Close hash table was restructurized from %d to %d size!\n", old_close_size, close_size);
				if (old_open_size != open_size)
					printf("Open hash table was restructurized from %d to %d size!\n", old_open_size, open_size);
					
				printf("Hash tables was successfully readed!\n");
				fclose(fsrc);
				continue;
			}
			case 12:                                                                  //Печать таблиц
			{
				if (choose == 0)
					printf("Table is not readed!\n");

				int table = 0;
				printf("What table do you want to print? Type 1 (close) or 2 (open): ");
				scanf("%d", &table);
				if (table != 1 && table != 2)
				{
					printf("Wrong table number, choosed close table.\n");
					table = 1;
				}


				if (table == 1)
					hprint_close_ht(ht_close, close_size);
				else
					hprint_open_ht(ht_open, open_size);
				continue;
			}
			case 13:                                                                  //Поиск в таблицах
			{
				if (choose == 0)
				{
					printf("Table is not readed!\n");
					continue;
				}

				printf("Input word for search (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}

				int kcmp = 0;
				if (choose == 1)
				{
					if (hsearch_close_ht(word_tmp, ht_close, close_size, &kcmp, hash_func_1) != -1)
						printf("Word was found in close table for %d compares!\n", kcmp);
					else
						printf("Word is not in close hash table!\n");
					
					if (hsearch_open_ht(word_tmp, ht_open, open_size, &kcmp, hash_func_1) != -1)
						printf("Word was found in open table for %d compares!\n", kcmp);
					else
						printf("Word is not in open hash table!\n");
				}
				else
				{
					if (hsearch_close_ht(word_tmp, ht_close, close_size, &kcmp, hash_func_2) != -1)
						printf("Word was found in close table for %d compares!\n", kcmp);
					else
						printf("Word is not in close hash table!\n");

					if (hsearch_open_ht(word_tmp, ht_open, open_size, &kcmp, hash_func_2) != -1)
						printf("Word was found in open table for %d compares!\n", kcmp);
					else
						printf("Word is not in open hash table!\n");
				}
				continue;
			}
			case 14:                                                                  //Удаление из таблиц
			{
				if (choose == 0)
				{
					printf("Table is not readed!\n");
					continue;
				}

				printf("Input word to delete (<= 20 chars): ");
				scanf("%s", word_tmp);
				if (strlen(word_tmp) > MAX_LENGHT)
				{
					printf("Wrong word lenght!\n");
					continue;
				}

				if (choose == 1)
				{
					if (hremove_close_ht(word_tmp, ht_close, close_size, hash_func_1) != -1)
						printf("Word was deleted from close table!\n");
					else
						printf("Word is not in close hash table!\n");

					if (hremove_open_ht(word_tmp, ht_open, open_size, hash_func_1) != -1)
						printf("Word was deleted from open table!\n");
					else
						printf("Word is not in open hash table!\n");
				}
				else
				{
					if (hremove_close_ht(word_tmp, ht_close, close_size, hash_func_2) != -1)
						printf("Word was deleted from close table!\n");
					else
						printf("Word is not in close hash table!\n");

					if (hremove_open_ht(word_tmp, ht_open, open_size, hash_func_2) != -1)
						printf("Word was deleted from open table!\n");
					else
						printf("Word is not in open hash table!\n");
				}
				continue;
			}
			case 21:                                                                //Эксперимент по времени
			{
				/* int size;
				printf("Input file words size: ");
				if (scanf("%d", &size) != 1)
				{
					printf("Wrong size!\n");
					continue;
				} */
				time_experiment();
				return EXIT_SUCCESS;
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

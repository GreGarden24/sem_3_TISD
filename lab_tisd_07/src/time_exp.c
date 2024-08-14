#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include "general_funcs.h"
#include "tree_funcs.h"
#include "time_exp.h"
#include "avl_funcs.h"
#include "ht_close_funcs.h"
#include "ht_open_funcs.h"

#define STD_LEN 23

typedef long long int tick_t;

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

void create_rand_words(FILE *fsrc, int size, char *search_word)
{
    char temp_word[MAX_LENGHT + 1];
    int word_size = rand() % MAX_LENGHT + 1;
    int rand_char = 33;
	int search = rand() % size;
    for (int i = 0; i < size; i++)
	{

        for (int j = 0; j < word_size; j++)
        {
            rand_char = rand() % ('z' - 'A') + 'A';
            temp_word[j] = (char) rand_char;
        }
        temp_word[word_size] = '\0';
        fprintf(fsrc, "%s\n", temp_word);
		if (i == search)
			strcpy(search_word, temp_word);

	    word_size = rand() % MAX_LENGHT + 1;
    }
}

void time_experiment(void)
{
	printf("\n                TIME EXPERIMENT FOR SERCHING WORDS IN STRUCTURES DEPENDS ON WORDS QUANTITY     \n");
	printf("------------------------------------------------------------------------------------------------------\n");
	printf("                 |     binary tree     |      avl tree     |     close table    |     open table     |\n");
	printf("------------------------------------------------------------------------------------------------------\n");
	
	FILE *f;

	hash_t ht_close[10000];		// закрытая хэш-таблица
	int close_size = STD_LEN;	

	open_hash_t ht_open[10000];		// открытая хэш-таблица
	int open_size = STD_LEN;	

	node_t* init_tree = NULL;
	node_t* avl_tree = NULL;
	char search_word[MAX_LENGHT + 2];

	tick_t start, end;
	
	tick_t t_add_tree = 0, t_add_avl = 0, t_add_close = 0, t_add_open = 0;
	tick_t t_find_tree = 0, t_find_avl = 0, t_find_close = 0, t_find_open = 0;
	int cmp_tree = 0, cmp_avl = 0, cmp_close = 0, cmp_open = 0;

	int sizes[] = { 10, 50, 100, 250, 500 };

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 1; j++)
		{
			f = fopen("rand_words.txt", "w+");
			create_rand_words(f, sizes[i], search_word);
			fclose(f);

			f = fopen("rand_words.txt", "r");
												// Добавление

			start = tick();
			init_tree = tree_file_read(f);
			end = tick();
			t_add_tree += end - start;
			rewind(f);

			start = tick();
			avl_tree = tree_file_read(f);
			avl_tree = tree_balance(avl_tree);
			end = tick();
			t_add_avl += end - start;
			rewind(f);

			start = tick();
			hread_close_ht(f, ht_close, &close_size, hash_func_1);
			end = tick();
			t_add_close += end - start;
			rewind(f);

			start = tick();
			hread_open_ht(f, ht_open, &open_size, hash_func_1);
			end = tick();
			t_add_open += end - start;
			rewind(f);
													//Поиск

			start = tick();
			node_search(init_tree, search_word, &cmp_tree);
			end = tick();
			t_find_tree += end - start;
			rewind(f);

			start = tick();
			node_search(avl_tree, search_word, &cmp_avl);
			end = tick();
			t_find_avl += end - start;
			rewind(f);

			start = tick();
			hsearch_close_ht(search_word, ht_close, close_size, &cmp_close, hash_func_1);
			end = tick();
			t_find_close += end - start;
			rewind(f);

			start = tick();
			hsearch_open_ht(search_word, ht_open, open_size, &cmp_open, hash_func_1);
			end = tick();
			t_find_open += end - start;
			rewind(f);
		}
		/* t_add_tree /= 10;
		t_add_avl /= 10;
		t_add_close /= 10;
		t_add_open /= 10;
		t_find_tree /= 10;
		t_find_avl /= 10;
		t_find_close /= 10;
		t_find_open /= 10;
		cmp_tree = (int) floor(cmp_tree * 1.0 / 10);
		cmp_avl = (int) floor(cmp_avl * 1.0 / 10); */
		
		printf("                                                 -%d-\n", sizes[i]);
		printf("------------------------------------------------------------------------------------------------------\n");
		printf("Compares:        |%20d%20d%20d%20d   |\n", cmp_tree, cmp_avl, cmp_close, cmp_open);
		printf("Time to add:     |%20lld%20lld%20lld%20lld   |\n", t_add_tree, t_add_avl, t_add_close, t_add_open);
		printf("Time to search:  |%20lld%20lld%20lld%20lld   |\n", t_find_tree, t_find_avl, t_find_close, t_find_open);
		printf("Memory:          |%20ld%20ld%20ld%20ld   |\n", sizes[i] * sizeof(node_t), sizes[i] * sizeof(node_t), close_size * sizeof(hash_t), open_size * sizeof(open_hash_t));
		printf("------------------------------------------------------------------------------------------------------\n");

		t_add_tree = 0;
		t_add_avl = 0;
		t_add_close = 0;
		t_add_open = 0;
		t_find_tree = 0;
		t_find_avl = 0;
		t_find_close = 0;
		t_find_open = 0;
		tree_free(init_tree);
		tree_free(avl_tree);
		init_close_ht(ht_close, close_size);
		close_size = STD_LEN;

		free_open_ht(ht_open, open_size);
		open_size = STD_LEN;
	}
}

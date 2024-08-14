#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include "general_funcs.h"
#include "tree_funcs.h"
#include "time_exp.h"

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
tick_t create_rand_words(FILE *fsrc, struct tree_node *tree, int size)
{
    char temp_word[MAX_LENGHT + 1];
    int word_size = rand() % MAX_LENGHT + 1;
    int rand_char = 33;
	struct tree_node* tmp_node;
	tick_t start = 0, end = 0;
	tick_t sum = 0;
    for (int i = 0; i < size; i++)
	{

        for (int j = 0; j < word_size; j++)
        {
            rand_char = rand() % ('z' - 'A') + 'A';
            temp_word[j] = (char) rand_char;
        }
        temp_word[word_size] = '\0';
        fprintf(fsrc, "%s\n", temp_word);

		start = tick();
		tmp_node = node_create(temp_word);
		node_insert(tree, tmp_node);
		end = tick();
		sum += end - start;

	    word_size = rand() % MAX_LENGHT + 1;
    }
	return sum;
}

void time_experiment(void)
{
	printf("\n         TIME EXPERIMENT FOR SERCHING WORDS IN TREE AND FILE WITH DIFF LENGHT\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("  size   | add to tree | find in tree | sum for tree | find in file |    time dif    \n");
	printf("-------------------------------------------------------------------------------------\n");
	
	FILE *f;
	struct tree_node* init_tree = NULL;

	tick_t start = 0, end = 0;
	
	tick_t t_add = 0;
	tick_t tfind_tree = 0, tfind_file = 0;

	int sizes[] = { 100, 500, 1000, 2500, 5000, 7500, 10000 };
	int rand_char = 33;
	int n = 0;

	char word_tmp[MAX_LENGHT + 2];
	int tmp;
	for (size_t i = 0; i < 7; i++)
	{
		for (size_t j = 0; j < 100; j++)
		{
			f = fopen("rand_words.txt", "w+");
			t_add += create_rand_words(f, init_tree, sizes[i]);
			fclose(f);

			rand_char = rand() % ('z' - 'A') + 'A';

			start = tick();
			tree_words_char_find(init_tree, rand_char, &n, 1);
			end = tick();
			tfind_tree += end - start;
			n = 0;

			f = fopen("rand_words.txt", "r");
			start = tick();
			tmp = fscanf(f, "%s", word_tmp);
			while (tmp == 1)   
			{
				if (word_tmp[0] == rand_char)
					n++;
				tmp = fscanf(f, "%s", word_tmp);
			}
			end = tick();
			n = 0;
			tfind_file += end - start;
			fclose(f);
		}
		t_add /= 100;
		tfind_tree /= 100;
		tfind_file /= 100;
		printf("%9d|%13lld|%14lld|%14lld|%14lld|%15f%%\n", sizes[i], t_add, tfind_tree, tfind_tree + t_add, tfind_file, (tfind_file - t_add - tfind_tree) * 1.0 / tfind_file * 100);
		t_add = 0;
		tfind_tree = 0;
		tfind_file = 0;
	}
	printf("-------------------------------------------------------------------------------------\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ht_close_funcs.h"
#include "ht_open_funcs.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


void free_open_ht(open_hash_t *ht, int n)
{
	hash_node_t *tmp = NULL;
	hash_node_t *tmp_next = NULL;
	for (int i = 0; i < n; i++)
	{
		ht[i].flag = 0;
		if (ht[i].value)
			tmp_next = ht[i].value;

		while(tmp_next)
		{
			tmp = tmp_next;
			tmp_next = tmp_next->next;
			if (tmp)
				free(tmp);
		}
	}
}

hash_node_t *create_hash_node(char *str)
{
	hash_node_t *node = malloc(sizeof(hash_node_t));
	if (!node)
		return NULL;
	strcpy(node->data, str);
	node->next = NULL;
	return node;
}

int rehash_open_ht(open_hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	open_hash_t *ht_old = malloc((*n) * sizeof(open_hash_t));
	if (!ht_old)
		return MEMORY_ERROR;

	for (int i = 0; i < *n; i++)
		ht_old[i] = ht[i];

	//printf("ht_old was created:\n");
	//hprint_open_ht(ht_old, *n);
	int nn = *n;
	*n = *n * 2 + 1;
	while (!is_prime(*n))
		*n += 2;

	if (*n > MAX_SIZE)
	{
		free(ht_old);
		return MEMORY_ERROR;
	}
	//printf("New size is %d\n", *n);

	for (int i = 0; i < (*n); i++)
	{
		ht[i].flag = 0;
		ht[i].value = NULL;
	}
	//printf("New table was initialized with NULLS\n");
	for (int i = 0; i < nn; i++)
	{
		if (ht_old[i].flag != 0)
		{
			hash_node_t *tmp_node = NULL;
			hash_node_t *cur_node = NULL;
			
			cur_node = ht_old[i].value;
			while (cur_node)       
			{
				//printf("Found replacable word %s\n", cur_node->data);
				int hashval = hashf(cur_node->data, *n);
				int j = hashval;
				//printf("its hash number is %d\n", hashval);
				if (ht[j].flag == 0)
				{
					//printf("Place is empty, add new node!\n");
					tmp_node = create_hash_node(cur_node->data);
					if (!(tmp_node))
						return MEMORY_ERROR;
					//printf("Created node: %s and %p!\n", tmp_node->data, (void*) tmp_node->next);
					ht[j].flag++;
					ht[j].value = tmp_node;
					cur_node = cur_node->next;
					//printf("Node added!\n\n");
				}
				else if (ht[j].flag < MAX_SEARCH)
				{
					//printf("Adding to place with < 4 elements!\n");
					tmp_node = ht[j].value;
					while (tmp_node->next)
						tmp_node = tmp_node->next;

					tmp_node->next = create_hash_node(cur_node->data);
					if (!(tmp_node->next))
						return MEMORY_ERROR;
					//printf("Node for new word created!\n");
					ht[j].flag++;

					cur_node = cur_node->next;
					//printf("Node added!\n\n");
				}
				else if (ht[j].flag == MAX_SEARCH)
				{
					//printf("\nNEED TO REHASH TABLE!\n");
					int sc = rehash_open_ht(ht, n, hashf);
					if (sc != EXIT_SUCCESS)
					{
						free(ht_old);
						return sc;
					}
				}
				//hprint_open_ht(ht, *n);
			}
		}
	}

	//free_open_ht(ht_old, nn);
	return EXIT_SUCCESS;
}

int hread_open_ht(FILE *f, open_hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	if (*n <= 0)
		return EXIT_FAILURE;
	
	char word_tmp[MAX_LENGHT + 2];

	if (fscanf(f, "%s", word_tmp) == EOF)
		return EXIT_FAILURE;
	rewind(f);
	
	int sc = 1;
	int new = 1;
	int hashval;
	int i;
	while (sc == 1)
	{
		if (new)
		{
			sc = fscanf(f, "%s", word_tmp);
			//printf("word %s was scanned ", word_tmp);
			if (sc == EOF)
				return EXIT_SUCCESS;
			if (sc != 1)
				return EXIT_FAILURE;

			hashval = hashf(word_tmp, *n);
			//printf("its hash number is %d\n", hashval);
			i = hashval;				// текущий индекс
		}
		hash_node_t *tmp_node = NULL;
		hash_node_t *cur_node = NULL;
		if (ht[i].flag == 0)
		{
			new = 1;
			//printf("Place is empty, add new node!\n");
			tmp_node = create_hash_node(word_tmp);
			if (!tmp_node)
				return MEMORY_ERROR;
			ht[i].value = tmp_node;
			ht[i].flag++;
		}
		else if (ht[i].flag < MAX_SEARCH)	// не больше максимума коллизий
		{
			new = 1;
			//printf("Adding to place with < 4 elements!\n");
			cur_node = ht[i].value;
			if (! strcmp(cur_node->data, word_tmp))
			{
				//printf("Its already added.\n");

				continue;
			}
			int exist = 0;
			while (cur_node->next)                       // значение уже добавлено
			{
				cur_node = cur_node->next;
				if (! strcmp(cur_node->data, word_tmp))
				{
					//printf("Its already added.\n");
					exist = 1;
					break;
				}
			}
			if (!exist)
			{
				tmp_node = create_hash_node(word_tmp);
				if (!tmp_node)
					return MEMORY_ERROR;
				//printf("Node for new word created!\n");
				cur_node->next = tmp_node;
				//printf("Node added!\n\n");
				ht[i].flag++;
			}
		}
		else if (ht[i].flag == MAX_SEARCH)
		{
			new = 1;
			cur_node = ht[i].value;
			if (! strcmp(cur_node->data, word_tmp))
			{
				//printf("Its already added.\n");
				continue;
			}
			int exist = 0;
			while (cur_node->next)                       // значение уже добавлено
			{
				cur_node = cur_node->next;
				if (! strcmp(cur_node->data, word_tmp))
				{
					//printf("Its already added.\n");
					exist = 1;
					break;
				}
			}
			if (!exist)
			{
				//printf("\nNEED TO REHASH TABLE!\n");
				int rc = rehash_open_ht(ht, n, hashf);
				if (rc != EXIT_SUCCESS)
					return rc;
				hashval = hashf(word_tmp, *n);
				i = hashval;
				new = 0;
			}
		}
	}
	return EXIT_SUCCESS;
}

int hsearch_open_ht(char *key, open_hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ))
{
	int hashval = hashf(key, n);		// вычисление значения хэш-функции
	*kcmp = 0;							// количество сравнений
	int i = hashval;					// текущий индекс
	hash_node_t *cur_node = NULL;

	if (ht[i].flag == 0)
		return -1;
	else
	{
		cur_node = ht[i].value;
		while (cur_node)
		{
			(*kcmp)++;
			if (!strcmp(cur_node->data, key))
				return i;
			cur_node = cur_node->next;
		}
	}
	return -1;
}

int hremove_open_ht(char *key, open_hash_t *ht, int n, int (*hashf) (char *, int ))
{
	int kcmp = 0;
	int ind = hsearch_open_ht(key, ht, n, &kcmp, hashf);	//индекс элемента
	if (ind != -1)	//элемент существует
	{
		ht[ind].flag--;
		hash_node_t *cur_node = ht[ind].value;
		hash_node_t *prev_node = ht[ind].value;
		while (cur_node)
		{
			if (!strcmp(cur_node->data, key))
			{
				if (prev_node != cur_node)
					prev_node->next = cur_node->next;
				else
					ht[ind].value = cur_node->next;
				
				free(cur_node);
				break;
			}
			prev_node = cur_node;
			cur_node = cur_node->next;
		}
		return ind;
	}
	return -1;
}

void hprint_open_ht(open_hash_t *ht, int n)
{
	printf("Open hash table:\n");
	hash_node_t *cur_node = NULL;
	for (int i = 0; i < n; i++)
	{
		if (ht[i].flag > 0)
		{
			printf("%4d  ->  ", i);
			cur_node = ht[i].value;
			while (cur_node)
			{
				printf("%s  ", cur_node->data);
				cur_node = cur_node->next;
			}
			printf("\n");
		}
		else
			printf("%4d  ->  --\n", i);
	}
}
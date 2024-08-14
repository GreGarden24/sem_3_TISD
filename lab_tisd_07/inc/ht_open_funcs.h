#ifndef __HT_OPEN_FUNCS__H__

#define __HT_OPEN_FUNCS__H__

typedef struct hash_node hash_node_t;

struct hash_node
{
	char data[MAX_LENGHT + 2];
	hash_node_t *next;
};


typedef struct open_hash
{
	hash_node_t *value;
	char flag;
} open_hash_t;

void free_open_ht(open_hash_t *ht, int n);

hash_node_t *create_hash_node(char *str);

int rehash_open_ht(open_hash_t *ht, int *n, int (*hashf) (char *, int ));

int hread_open_ht(FILE *f, open_hash_t *ht, int *n, int (*hashf) (char *, int ));

int hsearch_open_ht(char *key, open_hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ));

int hremove_open_ht(char *key, open_hash_t *ht, int n, int (*hashf) (char *, int ));

void hprint_open_ht(open_hash_t *ht, int n);


#endif // __HT_OPEN_FUNCS__H__
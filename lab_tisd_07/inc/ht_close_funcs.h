#ifndef __HT_CLOSE_FUNCS__H__

#define __HT_CLOSE_FUNCS__H__

#define MAX_LENGHT 20
#define MAX_SIZE 10000
#define MAX_SEARCH 4

typedef struct hash
{
	char value[MAX_LENGHT + 2];
	char flag;
} hash_t;

void init_close_ht(hash_t *ht, int n);

int hash_func_1(char *key, int p);

int hash_func_2(char *key, int p);

int is_prime(int x);

int rehash_close_ht(hash_t *ht, int *n, int (*hashf) (char *, int ));

int hread_close_ht(FILE *f, hash_t *ht, int *n, int (*hashf) (char *, int ));

int hsearch_close_ht(char *key, hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ));

int hremove_close_ht(char *key, hash_t *ht, int n, int (*hashf) (char *, int ));

void hprint_close_ht(hash_t *ht, int n);

#endif // __HT_CLOSE_FUNCS__H__
#ifndef __TREE_FUNCS_H__
#define __TREE_FUNCS_H__

#define MAX_LENGHT 20

typedef struct tree_node node_t;

struct tree_node
{
    char *name;
    node_t *left;
    node_t *right;
};

node_t* node_create(char *name);
node_t* node_insert(node_t *tree, node_t *node);
node_t* node_search(node_t *tree, const char *name, int *q_cmp);
void node_print(node_t *tree);
void tree_free(node_t *tree);
node_t* tree_file_read(FILE *fsrc);
void tree_words_char_find(node_t *tree, char c, int *n, int mode, int *q_cmp);
void tree_min_elem(node_t *tree, char **min_elem);
node_t* node_delete(node_t *tree, const char *name);
void tree_export_to_dot(FILE *f, node_t *tree, char c);


#endif // __TREE_FUNCS_H__
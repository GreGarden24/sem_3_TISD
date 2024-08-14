#ifndef __TREE_FUNCS_H__
#define __TREE_FUNCS_H__

#define MAX_LENGHT 20

struct tree_node
{
    char *name;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* node_create(char *name);
struct tree_node* node_insert(struct tree_node *tree, struct tree_node *node);
struct tree_node* node_search(struct tree_node *tree, const char *name);
void node_print(struct tree_node *tree);
void tree_free(struct tree_node *tree);
struct tree_node* tree_file_read(FILE *fsrc);
void tree_words_char_find(struct tree_node *tree, char c, int *n, int mode);
void tree_min_elem(struct tree_node *tree, char **min_elem);
struct tree_node* node_delete(struct tree_node *tree, const char *name);
void tree_export_to_dot(FILE *f, struct tree_node *tree, char c);


#endif // __TREE_FUNCS_H__
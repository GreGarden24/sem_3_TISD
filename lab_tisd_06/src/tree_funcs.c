#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree_funcs.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

struct tree_node* node_create(char *name)
{
    struct tree_node *node = malloc(sizeof(struct tree_node));
    if (node)
    {
        node->name = name;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct tree_node* node_insert(struct tree_node *tree, struct tree_node *node)
{
    if (tree == NULL)
        return node;
    
    int cmp = strcmp(node->name, tree->name);
    if (cmp < 0)
        tree->left = node_insert(tree->left, node);
    if (cmp > 0)
        tree->right = node_insert(tree->right, node);
    
    return tree;
}

struct tree_node* node_search(struct tree_node *tree, const char *name)
{
    int cmp;

    while (tree != NULL)
    {
        cmp = strcmp(name, tree->name);
        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}

void node_print(struct tree_node *tree)
{
    if (tree == NULL)
        return;

    node_print(tree->left);
    printf("%s ", tree->name);
    node_print(tree->right);
}

void tree_free(struct tree_node *tree)
{
    if (tree == NULL)
        return;

    node_print(tree->left);
    node_print(tree->right);
    free(tree->name);
    free(tree);
}

struct tree_node* tree_file_read(FILE *fsrc)
{
    struct tree_node* init_tree = NULL;
    char word_tmp[MAX_LENGHT + 2];
	int tmp = fscanf(fsrc, "%s", word_tmp);
	if (strlen(word_tmp) > MAX_LENGHT)
		return NULL;

    while (tmp == 1)   
    {
        struct tree_node* tmp_node = NULL;
        char *new_word = malloc((strlen(word_tmp) + 1) * sizeof(char));
        if (new_word == NULL)
            return NULL;

        strncpy(new_word, word_tmp, strlen(word_tmp) + 1);
        tmp_node = node_create(new_word);
        if (tmp_node == NULL)
            return NULL;

        init_tree = node_insert(init_tree, tmp_node);

        tmp = fscanf(fsrc, "%s", word_tmp);
        if (strlen(word_tmp) > MAX_LENGHT)
		    return NULL;
    }

    return init_tree;
}

void tree_words_char_find(struct tree_node *tree, char c, int *n, int mode)
{
/*     if (tree == NULL)
        return;

    tree_words_char_find(tree->left, c, n, mode);
    if (memchr(tree->name, c, sizeof(char)) != NULL)
    {
        (*n)++;
        if (mode)
            printf("%s ", tree->name);
    }
    tree_words_char_find(tree->right, c, n, mode); */
    if (tree == NULL)
        return;
    
    if (tree->name[0] == c)
    {
        (*n)++;
        if (mode)
            printf("%s ", tree->name);
        tree_words_char_find(tree->left, c, n, mode);
        tree_words_char_find(tree->right, c, n, mode);
    }
    else if (tree->name[0] > c)
        tree_words_char_find(tree->left, c, n, mode);
    else
        tree_words_char_find(tree->right, c, n, mode);

}

void tree_words_char_find_arr(struct tree_node *tree, char c, int *n, char *words_arr[])
{
    if (tree == NULL)
        return;

    tree_words_char_find_arr(tree->left, c, n, words_arr);
    if (memchr(tree->name, c, sizeof(char)) != NULL)
    {
        (*n)++;
        char *tmp_word = malloc((strlen(tree->name) + 1) * sizeof(char));
        strcpy(tmp_word, tree->name);
        words_arr[*n - 1] = tmp_word;
    }
    tree_words_char_find_arr(tree->right, c, n, words_arr);
}

struct tree_node* node_delete(struct tree_node *tree, const char *name)
{
    int cmp, flag = 0;
    struct tree_node *parent = tree;
    struct tree_node *del_node = tree;
    struct tree_node *tmp_node = NULL;

    while (del_node != NULL)
    {
        cmp = strcmp(name, del_node->name);
        if (cmp == 0)
            break;
        else if (cmp < 0)
        {    
            parent = del_node;
            del_node = del_node->left;
        }
        else
        {
            parent = del_node;
            del_node = del_node->right;
        }
    }

    if (del_node == NULL)
        return tree;

    
    if (del_node->left == NULL && del_node->right == NULL)
    {
        if (del_node == tree)
            flag = 1;

        if (parent->left == del_node)
            parent->left = NULL;
        else
            parent->right = NULL;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = NULL;
    }

    else if (del_node->left == NULL || del_node->right == NULL)
    {
        if (del_node == tree)
            flag = 1;

        if (del_node->left != NULL)
            tmp_node = del_node->left;
        else
            tmp_node = del_node->right;


        if (parent->left == del_node)
            parent->left = tmp_node;
        else
            parent->right = tmp_node;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = tmp_node;
    }
    
    else
    {
        if (del_node == tree)
            flag = 1;

        struct tree_node *parent_min = del_node;
        struct tree_node *min_elem = del_node->right;
        while (min_elem->left != NULL)
        {
            parent_min = min_elem;
            min_elem = min_elem->left;
        }


        if (parent_min->left == min_elem)
            parent_min->left = min_elem->right;
        else
            parent_min->right = min_elem->right;
        
        min_elem->left = del_node->left;
        min_elem->right = del_node->right;
        
        if (parent->left == del_node)
            parent->left = min_elem;
        else
            parent->right = min_elem;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = min_elem;
    }

    return tree;
}


void node_to_dot(struct tree_node *tree, FILE *f)
{
    if (tree == NULL)
        return;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);

    node_to_dot(tree->left, f);
    node_to_dot(tree->right, f);
}

void tree_export_to_dot(FILE *f, struct tree_node *tree, char c)
{
    fprintf(f, "digraph Words {\n");

    if (c != 0)
    {
        char *words_arr[100];
        int n = 0;
        tree_words_char_find_arr(tree, c, &n, words_arr);
        fprintf(f, "subgraph tier1\n{\nnode [color=\"lightgreen\",style=\"filled\",group=\"tier1\"]\n");
        for (int i = 0; i < n; i++)
        {
            fprintf(f, "%s\n", words_arr[i]);
            free(words_arr[i]);
        }
        n = 0;
        fprintf(f, "}\n");
    }

    node_to_dot(tree, f);

    fprintf(f, "}\n");
}
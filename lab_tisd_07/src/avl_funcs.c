#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_funcs.h"
#include "avl_funcs.h"

node_t *rotate_left(node_t *node)
{
	node_t *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	return tmp;
}

node_t *rotate_right(node_t *node)
{
	node_t *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}

int height(node_t *root)
{
	if (!root)
		return 0;
	int hleft = 0, hright = 0;
	if (root && root->left)
		hleft = height(root->left);
	if (root && root->right)
		hright = height(root->right);
	return (hleft < hright) ? hright + 1 : hleft + 1;
}

node_t *balance(node_t *tree)
{
	if (!tree)
		return NULL;
	int bfactor = height(tree->right) - height(tree->left);
	if (bfactor < -1)
	{
		bfactor = height(tree->left->right) - height(tree->left->left);
		if (bfactor > 0)
			tree->left = rotate_left(tree->left);
		return rotate_right(tree);
		
	}
	else if (bfactor > 1)
	{
		bfactor = height(tree->right->right) - height(tree->right->left);
		if (bfactor < 0)
			tree->right = rotate_right(tree->right);
		return rotate_left(tree);
	}
	return tree;
}

node_t *tree_balance(node_t *tree)
{
	if (!tree)
		return NULL;
	
	if (tree->left)
		tree->left = tree_balance(tree->left);
	
	if (tree->right)
		tree->right = tree_balance(tree->right);
	
	while (abs(height(tree->right) - height(tree->left)) > 1)
		tree = balance(tree);
	
	if (tree->left)
		tree->left = tree_balance(tree->left);
		
	if (tree->right)
		tree->right = tree_balance(tree->right);
	
	return tree;
}

node_t *avl_remove(node_t *tree, char *data)
{
	if (!tree)
		return NULL;

	if (strcmp(data, tree->name) < 0)
		tree->left = avl_remove(tree->left, data);
	else if (strcmp(data, tree->name) > 0)
		tree->right = avl_remove(tree->right, data);
	else
	{

		node_t *tmpl = tree->left;
		node_t *tmpr = tree->right;
		free(tree);

		if (!tmpl)
			return tmpr;

		node_t *tmax = tmpl;
		while (tmax->right)
			tmax = tmax->right;
		if (tmax == tmpl)
		{
			tmax->right = tmpr;
			return balance(tmax);
		}

		node_t *tmp = tmpl;
		while (tmp->right)
			tmp = tmp->right;
		tmpl->right = tmp->left;

		tmax->left = balance(tmpl);
		tmax->right = tmpr;
		return balance(tmax);
	}
	return balance(tree);
}

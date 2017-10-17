//
// Created by vasya on 17.10.2017.
//

#include <stdlib.h>
#include "random.h"

#ifndef RAVEGENERATOR_INT_TREE_H
#define RAVEGENERATOR_INT_TREE_H
#endif


typedef struct {
    long int number;
    void *pointer;
    void *left, *right;
} Int_Tree;

Int_Tree *new_node(long int number, void *pointer) {
    Int_Tree *result = malloc(sizeof(Int_Tree));
    result->number = number;
    result->pointer = pointer;
    result->left = 0;
    result->right = 0;
    return result;
}

Int_Tree *new_tree() {
    return new_node(get_rand(0, 1000000), 0);
}

void add_to_tree(Int_Tree *tree, long int number, int *pointer) {
    if (tree->number == number) {
        tree->pointer = pointer;
        return;
    }
    if (number > tree->number) {
        if (tree->right)
            add_to_tree(tree->right, number, pointer);
        else
            tree->right = new_node(number, pointer);
    }
    if (number < tree->number) {
        if (tree->left)
            add_to_tree(tree->left, number, pointer);
        else
            tree->left = new_node(number, pointer);
    }
}

void free_tree(Int_Tree *tree) {
    if (tree->right) {
        free_tree(tree->right);
    }
    if (tree->left) {
        free_tree(tree->left);
    }
    free(tree);
}

void *find_in_tree(Int_Tree *tree, int number) {
    if (tree->number == number)
        return tree->pointer;
    void *result = 0;
    if (number > tree->number) {
        if (tree->right)
            result = find_in_tree(tree->right, number);
        else
            result = 0;
    }

    if (number < tree->number) {
        if (tree->left)
            result = find_in_tree(tree->left, number);
        else
            result = 0;
    }

    return result;
}
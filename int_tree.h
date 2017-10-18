//
// Created by vasya on 17.10.2017.
//

#include <stdlib.h>
#include "random.h"

#ifndef RAVEGENERATOR_INT_TREE_H
#define RAVEGENERATOR_INT_TREE_H


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

Int_Tree *new_int_tree() {
    return new_node(get_rand(0, 1000000), 0);
}

void add_to_tree(Int_Tree *tree, long int number, void *pointer) {
    if (tree->number == number) {
        if (tree->pointer == 0)
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

void free_int_tree(Int_Tree *tree) {
    if (tree->right) {
        free_int_tree(tree->right);
    }
    if (tree->left) {
        free_int_tree(tree->left);
    }
    free(tree);
}

void *find_int_tree(Int_Tree *tree, long int number) {
    if (tree->number == number)
        return tree->pointer;
    void *result = 0;
    if (number > tree->number) {
        if (tree->right)
            result = find_int_tree(tree->right, number);
        else
            result = 0;
    }

    if (number < tree->number) {
        if (tree->left)
            result = find_int_tree(tree->left, number);
        else
            result = 0;
    }

    return result;
}

void *find_next_in_tree(Int_Tree *tree, long int *number) {
    if (*number < tree->number) {
        void *res = 0;
        if (tree->left)
            res = find_next_in_tree(tree->left, number);
        if (!res) {
            *number = tree->number;
            return tree->pointer;
        }
        return res;
    }
    if (*number == tree->number) {
        return tree->pointer;
    }
    if (*number > tree->number) {
        if (tree->right)
            return find_next_in_tree(tree->right, number);
        return 0;
    }
}

#endif
//
// Created by vasya on 17.10.2017.
//

#ifndef RAVEGENERATOR_DICTIONARY_H
#define RAVEGENERATOR_DICTIONARY_H

#include <stdio.h>
#include "int_tree.h"
#include "random.h"

typedef struct {
    int id;
    Int_Tree *next;
} DictTree;

DictTree *new_dict_tree_node() {
    DictTree *result;
    result = malloc(sizeof(DictTree));
    result->id = get_pseudo_random();
    result->next = new_tree();
    return result;
}

long int add_word_to_dict_tree(DictTree *tree, char *word) {
    if (word[0] == 0)
        return tree->id;
    DictTree *next = find_in_tree(tree->next, word[0]);
    if (next == 0) {
        next = new_dict_tree_node();
        add_to_tree(tree->next, word[0], next);
        return add_word_to_dict_tree(next, word + 1);
    }
    add_word_to_dict_tree(next, word + 1);
}

DictTree *make_dictionary(char **words) {
    long int i = 0;
    DictTree *result = new_dict_tree_node();
    while (words[i]) {
        add_word_to_dict_tree(result, words[i]);
        i++;
    }
    return result;
}

void print_dictionary_secondary(DictTree *tree, int tdepth, char *currentword) {
    currentword[tdepth] = 0;
    printf("%s ", currentword);
    printf("%i\n", tree->id);
    long int tchar = 1;
    DictTree *next = find_next_in_tree(tree->next, &tchar);
    while (next) {
        currentword[tdepth] = tchar;
        print_dictionary_secondary(next, tdepth + 1, currentword);
        tchar++;
        next = find_next_in_tree(tree->next, &tchar);
    }
}

void print_dictionary(DictTree *tree) {
    char *currentword = malloc(sizeof(char) * 10000);
    print_dictionary_secondary(tree, 0, currentword);
    free(currentword);
}



#endif

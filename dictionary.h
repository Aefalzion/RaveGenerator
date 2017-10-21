//
// Created by vasya on 17.10.2017.
//

#ifndef RAVEGENERATOR_DICTIONARY_H
#define RAVEGENERATOR_DICTIONARY_H

#include <stdio.h>
#include "int_tree.h"
#include "random.h"
#include "stdlib.h"

long int nwords = 0;

typedef struct {
    int id;
    int real;
    Int_Tree *next;
    void *anscestor;
    char symbol;
} DictTree;

DictTree *new_dict_tree_node(DictTree *anscestor, char symbol, int real) {
    nwords++;
    DictTree *result;
    result = malloc(sizeof(DictTree));
    result->id = get_pseudo_random();
    result->next = new_int_tree();
    result->anscestor = anscestor;
    result->symbol = symbol;
    result->real = real;
    return result;
}

//function that takes word and returns its id(if there is no word in dictionary, it adds it)
long int add_word_or_get_id(DictTree *tree, char *word) {
    if (word[0] == 0) {
        tree->real = 1;
        return tree->id;

    }
    DictTree *next = find_int_tree(tree->next, word[0]);
    if (next == 0) {
        next = new_dict_tree_node(tree, word[0], 0);
        add_to_tree(tree->next, word[0], next);
        return add_word_or_get_id(next, word + 1);
    }
    add_word_or_get_id(next, word + 1);
}

DictTree *make_dictionary(char **words) {
    long int i = 0;
    DictTree *result = new_dict_tree_node(0, 0, 0);
    while (words[i]) {
        add_word_or_get_id(result, words[i]);
        i++;
    }
    return result;
}

long int pd = 0;

void print_dictionary_secondary(DictTree *tree, int tdepth, char *currentword) {
    currentword[tdepth] = 0;
    if (tree->real) {
        printf("%li %s ", pd, currentword);
        pd++;
        printf("%i\n", tree->id);
    }
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
    pd = 0;
    char *currentword = malloc(sizeof(char) * 10000);
    print_dictionary_secondary(tree, 0, currentword);
    free(currentword);
}

void free_dict_tree(DictTree *tree) {
    long int tchar = 1;
    DictTree *next = find_next_in_tree(tree->next, &tchar);
    while (next) {
        free_dict_tree(next);
        tchar++;
        next = find_next_in_tree(tree->next, &tchar);
    }
    free_int_tree(tree->next);
    free(tree);
    nwords--;
}

typedef struct {
    long int id;
    DictTree *last_character;
} Word;

Word *make_word(long int id, DictTree *last_character) {
    Word *result;
    result = malloc(sizeof(Word));
    result->id = id;
    result->last_character = last_character;
    return result;
}

void make_words_list_from_dict_tree_secondary(DictTree *tree, Word **word_list, long int *current_position) {
    if (tree->real) {
        word_list[*current_position] = make_word(tree->id, tree);
        *current_position += 1;
    }
    long int tchar = 0;
    DictTree *next = find_next_in_tree(tree->next, &tchar);
    while (next) {
        make_words_list_from_dict_tree_secondary(next, word_list, current_position);
        tchar++;
        next = find_next_in_tree(tree->next, &tchar);
    }
}

int compare(const Word **a1, const Word **b1) {
    return (*a1)->id - (*b1)->id;

}

Word **make_words_list_from_dict_tree(DictTree *tree) {
    Word **result;
    result = malloc(sizeof(Word *) * (1000000));
    long int i = 0;
    make_words_list_from_dict_tree_secondary(tree, result, &i);
    qsort(result, (size_t) i, sizeof(Word *), (int (*)(const void *, const void *)) compare);
    result[i] = 0;
    printf("%li\n", i);
    /* printf("%i\n", compare(result, result + 1));
     printf("%i\n", compare(result + 1, result + 2));
     printf("%i\n", compare(result + 2, result + 3));
     printf("%i\n", compare(result + 3, result + 4));
     printf("%i\n", compare(result + 4, result + 5));
 */
    return result;
}

long int depth_in_dict_tree(DictTree *tree) {
    if (tree->anscestor == 0)
        return 0;
    return 1 + depth_in_dict_tree(tree->anscestor);
}

void get_word_from_last_character_secondary(DictTree *tree, char *word, long int *pos) {
    word[*pos] = tree->symbol;
    if (tree->anscestor) {
        *pos += 1;
        get_word_from_last_character_secondary(tree->anscestor, word, pos);
    }
}

char *get_word_from_last_character(DictTree *tree) {
    char *result;
    result = malloc(2000);
    long int length = 0;
    get_word_from_last_character_secondary(tree, result, &length);
    char *cutted_result;
    cutted_result = malloc(sizeof(char) * (length + 1));
    int i;
    for (i = 0; i < length; i++) {
        cutted_result[i] = result[length - i - 1];
        cutted_result[length] = 0;
    }
    free(result);
    return cutted_result;
}

char *get_word_from_id(Word **sorted_word_list, long int id) {
    long int min = 0, max = 0;
    while (sorted_word_list[max])
        max++;
    max--;
    while (max > min) {
        long int mid = (min + max) / 2;
        if (id <= sorted_word_list[mid]->id)
            max = mid;
        else
            min = mid + 1;
    }
    return get_word_from_last_character(sorted_word_list[max]->last_character);
}



#endif

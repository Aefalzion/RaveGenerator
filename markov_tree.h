//
// Created by vasya on 07.11.2017.
//

#ifndef RAVEGENERATOR_MARKOV_TREE_H
#define RAVEGENERATOR_MARKOV_TREE_H

typedef struct {
    long int n;
    Int_Tree *next_nodes;
    Int_Tree *word_probabilities;
} MarkovNode;

MarkovNode *make_new_markov_node(long int n) {
    MarkovNode *result;
    result = malloc(sizeof(MarkovNode));
    result->n = n;
    result->next_nodes = new_int_tree();
    result->word_probabilities = new_int_tree();
    return result;
}

void add_probability(Int_Tree *word_probabilities, long int word) {
    long int *prob = find_int_tree(word_probabilities, word);
    if (prob) {
        *prob += 1;
        return;
    }
    prob = malloc(sizeof(long int));
    *prob = 1;
    add_to_tree(word_probabilities, word, prob);

}

void add_word_sequence_to_markov_tree(MarkovNode *tree, long int *first, long int *last, long int *next) {
    add_probability(tree->word_probabilities, *next);
    tree->n += 1;
    if (last < first)
        return;
    MarkovNode *next_tree = find_int_tree(tree->next_nodes, *last);
    if (next_tree)
        add_word_sequence_to_markov_tree(next_tree, first, last - 1, next);
    else {
        next_tree = make_new_markov_node(0);
        add_to_tree(tree->next_nodes, *last, next_tree);
        add_word_sequence_to_markov_tree(next_tree, first, last - 1, next);
    }
}

void free_markov_tree(MarkovNode *tree) {
    MarkovNode *next = 0;
    long int curint = 0;
    next = find_next_in_tree(tree->next_nodes, &curint);
    while (next) {
        curint++;
        free_markov_tree(next);
        next = find_next_in_tree(tree->next_nodes, &curint);
    }
    free_int_tree(tree->next_nodes);

    long int *next1;
    next1 = 0;
    curint = 0;
    next1 = find_next_in_tree(tree->word_probabilities, &curint);
    while (next1) {
        curint++;
        free(next1);
        next1 = find_next_in_tree(tree->word_probabilities, &curint);
    }

    free_int_tree(tree->word_probabilities);
    free(tree);
}

#include "int_tree.h"

#endif //RAVEGENERATOR_MARKOV_TREE_H

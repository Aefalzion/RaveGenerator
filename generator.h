//
// Created by vasya on 17.10.2017.
//

#ifndef RAVEGENERATOR_GENERATOR_H
#define RAVEGENERATOR_GENERATOR_H

#include "int_tree.h"
#include "dictionary.h"

typedef struct {
    int n;
    Int_Tree *next_nodes;
    Int_Tree *word_probabilities;
} MarkovNode;

MarkovNode *make_new_markov_node(int n) {
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
    } else {
        prob = malloc(sizeof(long int));
        *prob = 1;
        add_to_tree(word_probabilities, word, prob);
    }
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

long int procent_of_randomness = 0, depth_of_accuracy = 0;

long int get_random_word(MarkovNode *tree, long int *first, long int *last, long int depth) {
    if ((last >= first) && (get_rand(0, 100) >= procent_of_randomness || (depth <= depth_of_accuracy))) {
        MarkovNode *next_node = find_int_tree(tree->next_nodes, *last);
        if (next_node) {
            return get_random_word(next_node, first, last - 1, depth + 1);
        }


    }
    Int_Tree *probs = tree->word_probabilities;
    long int max = tree->n;
    int t = get_rand(1, max);
    long int curword = 1;
    long int *curprob;
    while (t > 0) {
        curword++;
        curprob = find_next_in_tree(probs, &curword);
        t -= *curprob;
    }
    return curword;
}

void process_sequence(MarkovNode *tree, long int *first, long int *last, long int max_depth) {
    long int *cur = first;
    while (cur < last) {
        if (cur - first < max_depth) {
            add_word_sequence_to_markov_tree(tree, first, cur, cur + 1);
        } else {
            add_word_sequence_to_markov_tree(tree, cur - max_depth, cur, cur + 1);
        }
        cur++;
    }
}

char dot[2] = {'.', 0};

char *make_sequence(DictTree *dict_tree, MarkovNode *markov_tree, Word **sorted_word_list, long int length) {
    char *result;
    char *current_word;
    result = malloc(sizeof(char) * (length + 1000));

    long int cur_pos_in_result = 0;
    long int *sequence = malloc(sizeof(long int) * length);

    sequence[0] = add_word_or_get_id(dict_tree, dot);
    long int cur_pos_in_sequence = 1;
    while (cur_pos_in_result < length) {
        sequence[cur_pos_in_sequence] = get_random_word(markov_tree, sequence, sequence + cur_pos_in_sequence - 1, 0);
        current_word = get_word_from_id(sorted_word_list, sequence[cur_pos_in_sequence]);
        //    printf("%s\n", current_word);
        long int current_pos_in_word = 0;
        while (current_word[current_pos_in_word]) {
            result[cur_pos_in_result] = current_word[current_pos_in_word];
            cur_pos_in_result += 1;
            current_pos_in_word += 1;
        }
        result[cur_pos_in_result] = ' ';
        cur_pos_in_result += 1;
        cur_pos_in_sequence += 1;
        free(current_word);
    }
    free(sequence);
    result[cur_pos_in_result] = 0;
    return result;
}
#endif


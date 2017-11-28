//
// Created by vasya on 18.10.2017.
//

#ifndef RAVEGENERATOR_STRINGS_H
#define RAVEGENERATOR_STRINGS_H

#include "int_tree.h"

Int_Tree *SEPARATORS;
Int_Tree *PUNCTUATION;
Int_Tree *LETTERS;

const long int MAX_WORDS = 1000000;

void init_symbol_trees() {
    SEPARATORS = new_int_tree();
    PUNCTUATION = new_int_tree();
    LETTERS = new_int_tree();
    add_to_tree(SEPARATORS, ' ', (void *) 1);
    add_to_tree(SEPARATORS, ' ', (void *) 1);
    add_to_tree(SEPARATORS, '\n', (void *) 1);
    add_to_tree(SEPARATORS, '\t', (void *) 1);
    add_to_tree(PUNCTUATION, '.', (void *) 1);
    add_to_tree(PUNCTUATION, '(', (void *) 1);
    add_to_tree(PUNCTUATION, ')', (void *) 1);
    add_to_tree(PUNCTUATION, ',', (void *) 1);
    add_to_tree(PUNCTUATION, '!', (void *) 1);
    add_to_tree(PUNCTUATION, '?', (void *) 1);
    add_to_tree(PUNCTUATION, ':', (void *) 1);
    add_to_tree(PUNCTUATION, '"', (void *) 1);
    add_to_tree(PUNCTUATION, ';', (void *) 1);
    long int i;
    for (i = 0; i <= 'z' - 'a'; i++) {
        add_to_tree(LETTERS, 'a' + (17 * i) % ('z' - 'a'), (void *) 1);
        add_to_tree(LETTERS, 'A' + (17 * i) % ('z' - 'a'), (void *) 1);
    }
    add_to_tree(LETTERS, '\'', (void *) 1);

}

char *copy_string(char *string) {
    int length = 0;
    while (string[length])
        length++;
    char *result = malloc(sizeof(char) * (length + 1));
    result[length] = 0;
    int i;
    for (i = 0; i < length; i++)
        result[i] = string[i];
    return result;
}

char **split_string_into_words(char *string) {
    char **result = malloc(sizeof(char *) * MAX_WORDS);
    char *current_word;
    long int current_word_position = 0;
    long int current_n = 0;
    current_word = malloc(sizeof(char) * 2000);
    long int current_symbol = 0;
    while (string[current_symbol]) {
        if (find_int_tree(SEPARATORS, string[current_symbol])) {
            if (current_word_position > 0) {
                current_word[current_word_position] = 0;
                result[current_n] = copy_string(current_word);
                current_word_position = 0;
                current_n++;
            }
        } else if (find_int_tree(PUNCTUATION, string[current_symbol])) {
            if (current_word_position > 0) {
                current_word[current_word_position] = 0;
                result[current_n] = copy_string(current_word);
                current_word_position = 0;
                current_n++;
            }
            current_word[0] = string[current_symbol];
            current_word[1] = 0;
            result[current_n] = copy_string(current_word);
            current_word_position = 0;
            current_n++;
        } else if (find_int_tree(LETTERS, string[current_symbol])) {
            current_word[current_word_position] = string[current_symbol];
            current_word_position++;
        }
        current_symbol++;
    }
    if (current_word_position > 0) {
        current_word[current_word_position] = 0;
        result[current_n] = copy_string(current_word);
        current_word_position = 0;
        current_n++;
    }
    result[current_n] = 0;
    char **cutted_result = malloc(sizeof(char *) * (current_n + 1));
    cutted_result[current_n] = 0;
    int i;
    for (i = 0; i < current_n; i++)
        cutted_result[i] = result[i];
    free(result);
    return cutted_result;
}

void space_clean(char * string, size_t size){
    
}

#endif //RAVEGENERATOR_STRINGS_H

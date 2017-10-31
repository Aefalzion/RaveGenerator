#include <stdio.h>
#include <locale.h>
#include "int_tree.h"
#include "dictionary.h"
#include "logs.h"
#include "files.h"
#include "strings.h"
#include "generator.h"

DictTree *dictionary;
Word **dictionary_list;
MarkovNode *markov_tree;
long int ch_length = 10;

void input_file(char *filename) {
    char *text = read_text_from_file(100000, filename);
    // printf("%s", text);
    char **words = split_string_into_words(text);
    free(text);
    long int *sequence;
    sequence = malloc(sizeof(long int) * 1000000);
    int i = 0;
    while (words[i]) {
        sequence[i] = add_word_or_get_id(dictionary, words[i]);
        i++;
    }
    process_sequence(markov_tree, sequence, sequence + i - 1, ch_length);
    for (i = 0; words[i]; i++)
        free(words[i]);
    free(words);
    free(dictionary_list);
    free(sequence);
    dictionary_list = make_words_list_from_dict_tree((dictionary));

}

int main() {
    setlocale(LC_ALL, "Rus");
    markov_tree = make_new_markov_node(0);
    init_symbol_trees();
    dictionary = new_dict_tree_node(0, 0, 0);
    log("program started", "logs.txt");
    printf("Hello! This is the Rave Generator. You can use following commands:\n"
                   "i <filename> <chains' length>  to import file with text\n"
                   "g <number> <procent_of_randomness> <depth_of_accuracy>   to generate a text of <number> length\n"
                   "e              to close program\n");

    char command[100];
    while (command[0] != 'e') {
        printf(">");

        scanf("%s", command);
        char filename[1000];
        char *res;
        long int length, i;
        switch (command[0]) {
            case 'e':
                break;
            case 'i':
                //  printf("Please, enter name of the file with text:\n");
                scanf("%s", filename);
                scanf("%li", &ch_length);
                input_file(filename);
                //print_dictionary(dictionary);
                break;
            case 'g':
                scanf("%li", &length);
                scanf("%li", &procent_of_randomness);
                scanf("%li", &depth_of_accuracy);
                res = make_sequence(dictionary, markov_tree, dictionary_list, length);
                printf("%s", res);
                break;
            case 'w':
                scanf("%li", &i);
                printf("%s", get_word_from_id(dictionary_list, i));
                break;
            case 'l':
                for (i = 0; dictionary_list[i]; i++)
                    printf("%i %s %li\n", i, get_word_from_last_character(dictionary_list[i]->last_character),
                           dictionary_list[i]->id);
                break;
            case 'd':
                print_dictionary(dictionary);
                break;
            default:
                printf("Sorry, but there is no '%s' command!\n", command);
                log("user is dumb", "logs.txt");
                break;
        }
    }
    log("program succesfully closed", "logs.txt");
    return 0;

    /*
    DictTree *tree = new_dict_tree_node(0, 0);
    char s[1000];
    scanf("%s", s);
    while (s[0] != '.') {
        printf("%li\n", add_word_or_get_id(tree, s));
        scanf("%s", s);
    }
    print_dictionary(tree);
    Word **array = make_words_list_from_dict_tree(tree);
    int t = 0;
    while (array[t]) {
        printf("%li %i\n", array[t]->id, (int) array[t]->last_character);
        t++;
    }

    printf("%li\n", nwords);
    Word **word_list = make_words_list_from_dict_tree(tree);
    long int request;

    scanf("%li", &request);
    while (request) {

        printf("%s", get_word_from_id(word_list, request));
        scanf("%li", &request);
    }
     */
}

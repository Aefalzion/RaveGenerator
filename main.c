#include <stdio.h>
#include "int_tree.h"
#include "dictionary.h"
#include "logs.h"
#include "files.h"
#include "strings.h"

DictTree *dictionary;
Word **dictionary_list;

void input_file(char *filename) {
    char *text = read_text_from_file(100000, filename);
    printf("%s", text);
    char **words = split_string_into_words(text);
    free(text);
    int i = 0;
    while (words[i]) {
        long int a = add_word_or_get_id(dictionary, words[i]);
        printf("%li\n", a);
        i++;
    }
    for (i = 0; words[i]; i++)
        free(words[i]);
    free(words);
    free(dictionary_list);
    dictionary_list = make_words_list_from_dict_tree((dictionary));

}

int main() {
    init_symbol_trees();
    dictionary = new_dict_tree_node(0, 0);
    log("program started", "logs.txt");
    printf("Hello! This is the Rave Generator. You can use following commands:\n"
                   "i <filename>   to import file with text\n"
                   "g <number>     to generate a text of <number> length\n"
                   "e              to close program\n");

    char command[100];
    while (command[0] != 'e') {
        printf(">");

        scanf("%s", command);
        char filename[1000];

        switch (command[0]) {
            case 'e':
                break;
            case 'i':
                printf("Please, enter name of the file with text:\n");
                scanf("%s", filename);
                input_file(filename);
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

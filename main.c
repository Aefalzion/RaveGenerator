#include <stdio.h>
#include <locale.h>
#include "int_tree.h"
#include "dictionary.h"
#include "files.h"
#include "strings.h"
#include "generator.h"

DictTree *dictionary;
Word **dictionary_list;
MarkovNode *markov_tree;
long int ch_length = 5;

void input_file(char *filename) {
    char *text = read_text_from_file(10000000, filename);
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

typedef struct {
    long int id, prob;
} WordProb;

WordProb *variants;
long int nvariants;

int compvariants(WordProb *a, WordProb *b) {
    if (a->prob == b->prob)
        return 0;
    if (a->prob > b->prob)
        return -1;
    if (a->prob < b->prob)
        return 1;
}

void print_variants_secondary(MarkovNode *tree, long int *words, long int n) {
    MarkovNode *next_node = 0;
    if (n)
        next_node = find_int_tree(tree->next_nodes, words[0]);
    if (next_node) {
        print_variants_secondary(next_node, words - 1, n - 1);
        return;
    }
    if (n)
        return;
    Int_Tree *probs = tree->word_probabilities;
    long int curword = 0;
    long int *curprob;
    long int t = tree->n;
    printf("%li\n", tree->n);
    while (t > 0) {
        curword++;
        curprob = find_next_in_tree(probs, &curword);
        t -= *curprob;
        variants[nvariants].prob = *curprob;
        variants[nvariants].id = curword;
        nvariants += 1;
    }
}

void print_variants(long int n) {
    variants = malloc(sizeof(WordProb) * 100000);
    nvariants = 0;
    long int *ar;
    ar = malloc(sizeof(long int) * n);
    char s[10000];
    long int i;
    for (i = 0; i < n; i++) {
        scanf("%s", s);
        ar[i] = add_word_or_get_id(dictionary, s);
    }
    free(dictionary_list);
    dictionary_list = make_words_list_from_dict_tree((dictionary));
    print_variants_secondary(markov_tree, ar + n - 1, n);
    qsort(variants, (size_t) nvariants, sizeof(WordProb), (void *) compvariants);
    for (i = 0; i < nvariants; i++)
        printf("%s %li\n", get_word_from_id(dictionary_list, variants[i].id), variants[i].prob);
    free(variants);
    free(ar);
}

void import_list(char *filename) {
    FILE *fp = fopen(filename, "r");
    char filename1[1000];

    while (fgetc(fp) != EOF) {
        fscanf(fp, "%s", filename1);
        input_file(filename1);
        printf("%s\n", filename1);
    }
    fclose(fp);
}

void display_help() {
    printf("Hello! This is the Rave Generator. You can use following commands:\n"
                   "i <filename> <chains' length>  to import file with sample text\n"
                   "g <length of a text> <procent_of_randomness> <depth_of_accuracy>   to generate a text\n"
                   "e to close program\n"
                   "d to print the dictionary\n"
                   "p <filename> to save the last generated text to a file\n"
                   "s <number of words> <words> to search for an sequence of words\n"
                   "l <name of file with list of files> to import files with sample texts from a list\n"
                   "w <id> to search a word from its id\n"
                   "h to display help\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    markov_tree = make_new_markov_node(0);
    init_symbol_trees();
    dictionary = new_dict_tree_node(0, 0, 0);
    mylog("program started", "logs.txt");
    display_help();

    char command[100];
    char filename[1000];
    char *res = 0;
    long int length, i, n;
    do {
        printf("\n>");

        scanf("%s", command);
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
            case 'l':
                //  printf("Please, enter name of the file with text:\n");
                scanf("%s", filename);
                import_list(filename);
                //print_dictionary(dictionary);
                break;
            case 'g':
                if (res)
                    free(res);
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
            case 'd':
                print_dictionary(dictionary);
                break;
            case 's':
                scanf("%li", &n);
                print_variants(n);
                break;
            case 'p':
                scanf("%s", filename);
                if (res == 0) {
                    printf("Generate something first!\n");
                    break;
                }
                FILE *fp = fopen(filename, "w");
                fprintf(fp, res);
                fclose(fp);
                break;
            case 'h':
                display_help();
                break;
            default:
                printf("Sorry, but there is no '%s' command!\n", command);
                mylog("user is dumb", "logs.txt");
                break;
        }
    } while (command[0] != 'e');
    free_dict_tree(dictionary);
    long int j = 0;
    if (dictionary_list) {
        while (dictionary_list[j]) {
            free(dictionary_list[j]);
            j++;
        }
        free(dictionary_list);
    }
    free_markov_tree(markov_tree);
    mylog("program succesfully closed", "logs.txt");
    return 0
};

#include <stdio.h>
#include "int_tree.h"
#include "dictionary.h"
#include "logs.h"
#include "files.h"

int main() {
    log("program started", "logs.txt");
    printf("Hello! This is the Rave Generator. You can use following commands:\n"
                   "i <filename>   to import file with text\n"
                   "g <number>     to generate a text of <number> length\n"
                   "e              to close program\n");

    char command[100];
    while (command[0] != 'e') {
        printf(">");

        scanf("%s", command);

        switch (command[0]) {
            case 'e':
                break;
            default:
                printf("Sorry, but there is no '%s' command!\n", command);
                log("user is dumb", "logs.txt");
                break;
        }
    }
    log("program succesfully closed", "logs.txt");
    return 0;
}

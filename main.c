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
                   "e              to close program");

    return 0;
}

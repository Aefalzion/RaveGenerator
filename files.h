//
// Created by vasya on 17.10.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include "logs.h"


#ifndef RAVEGENERATOR_FILES_H
#define RAVEGENERATOR_FILES_H
#endif

unsigned char *read_text_from_file(int maxsize, char *filename) {
    FILE *f = fopen(filename, "rb");
    unsigned char c = fgetc(f);
    long int i = 1;
    unsigned char *result = malloc(sizeof(unsigned char) * (maxsize + 1));
    result[0] = 0;
    while (i < maxsize && c != (unsigned char) EOF) {
        result[i] = c;
        i++;
        //  printf("%i ", i);
        c = fgetc(f);
        if (c == ' ' || c == '\r' || c == '\n') {
            result[i] = ' ';
            i++;
            while (c == ' ' || c == '\r' || c == '\n')
                c = fgetc(f);
        }
    }
    result[i] = 0;
    log("file was succesfully read", "logs.txt");
    return result;
}
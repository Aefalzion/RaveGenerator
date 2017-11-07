//
// Created by vasya on 17.10.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include "logs.h"

#ifndef RAVEGENERATOR_FILES_H
#define RAVEGENERATOR_FILES_H
#endif

char *read_text_from_file(long int maxsize, char *filename) {
    FILE *f = fopen(filename, "rb");
    char c = (char) fgetc(f);
    long int i = 0;
    char *result = malloc(sizeof(char) * (maxsize + 1));
    while (i < maxsize && c != (char) EOF) {
        result[i] = c;
        i++;
        //  printf("%i ", i);
        c = (char) fgetc(f);
        if (c == ' ' || c == '\r' || c == '\n') {
            result[i] = ' ';
            i++;
            while (c == ' ' || c == '\r' || c == '\n')
                c = (char) fgetc(f);
        }
    }
    result[i] = 0;
    char *cutted_result = malloc(sizeof(char) * (i + 1));
    int j = 0;
    for (j = 0; j <= i; j++)
        cutted_result[j] = result[j];
    free(result);
    mylog("file was succesfully read", "logs.txt");
    return cutted_result;
}
//
// Created by vasya on 17.10.2017.
//
#ifndef  RAVEGENERATOR_LOGS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifndef RAVEGENERATOR_LOGS_H
#define RAVEGENERATOR_LOGS_H
#endif //RAVEGENERATOR_LOGS_H

void mylog(char *log, char *filename) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    FILE *f = fopen(filename, "a");
    fputs(asctime(timeinfo), f);
    fputs(log, f);
    fputs("\n", f);
    fclose(f);
}

#endif
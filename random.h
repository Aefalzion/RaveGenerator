//
// Created by vasya on 17.10.2017.
//

#ifndef RAVEGENERATOR_RANDOM_H
#define RAVEGENERATOR_RANDOM_H

#include <stdlib.h>
#include <time.h>
#include "logs.h"

int RANDOMIZED = 0;

void randomize() {
    RANDOMIZED = 1;
    srand(clock());
}

long int get_rand(long int from, long int to) {
    if (!RANDOMIZED)
        randomize();
    if (to >= from)
        return from + rand() % (to - from + 1);
    log("!!! from < to !!!", "logs.txt");
}

#endif //RAVEGENERATOR_RANDOM_H

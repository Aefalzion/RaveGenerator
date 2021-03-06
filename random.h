//
// Created by vasya on 17.10.2017.
//

#ifndef RAVEGENERATOR_RANDOM_H
#define RAVEGENERATOR_RANDOM_H

#include <stdlib.h>
#include <time.h>
#include "logs.h"

int RANDOMIZED = 0;

long int CUR_RND = 0;

void randomize() {
    RANDOMIZED = 1;
    srand((unsigned int) clock());
}

long int get_rand(long int from, long int to) {
    if (!RANDOMIZED)
        randomize();
    if (to >= from)
        return from + rand() % (to - from + 1);
    mylog("!!! from < to !!!", "logs.txt");
}

long int get_pseudo_random() {
    CUR_RND++;
    return get_rand(0, 10000) * 100000 + CUR_RND;
};


#endif //RAVEGENERATOR_RANDOM_H

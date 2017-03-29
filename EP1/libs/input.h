#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Struct to keep input data organized
typedef struct {
    int ti, tj;
    int si, sj;
    Graph *g;
} Input;

Input* fileload(const char *filename);

#endif

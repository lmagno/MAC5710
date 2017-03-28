#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Struct to keep input data organized
typedef struct {
    int ti, tj;
    int si, sj;
    Matrix *M;
} Input;

Input* fileload(const char *filename);

#endif

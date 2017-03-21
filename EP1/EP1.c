#include <stdio.h>
#include "matrix.h"

int main() {
    Matrix M;

    M = matrix(10, 11);
    printf("%f\n", M.M[1][1]);
    return 0;
}

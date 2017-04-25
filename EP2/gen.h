#ifndef GEN_H
#define GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"

void letters_random(uint8_t letters[26], int length);
void letters_print(uint8_t letters[26]);
void word_random(char *word, uint8_t letters[26], int length);
Queue* permutations(uint8_t letters[26], int wordlen, int partlen);
Queue* npermutations(uint8_t letters[26], int wordlen, int partlen, int n);

#endif

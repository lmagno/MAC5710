#ifndef GEN_H
#define GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

void letters_random(uint8_t letters[26], int length);
void letters_print(uint8_t letters[26]);
void word_random(char *word, uint8_t letters[26], int length);

#endif

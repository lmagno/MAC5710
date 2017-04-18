#include "generator.h"


int main(int argc, char const *argv[]) {
    uint8_t letters[26];
    int i, j;
    char word[100];
    Queue *q;

    for(i = 0; i < 10; i++) {
        q = queue_create();
        letters_random(letters, 10);
        letters_print(letters);
        for(j = 0; j < 5; j++) {
            word_random(word, letters, 10);
            queue_push(q, word);
        }
        queue_print(q);
        queue_free(q);
    }

    return 0;
}

void word_random(char *word, uint8_t letters[26], int length) {
    int i, j, l, r;

    for(i = 0; i <= length; i++)
        word[i] = '\0';

    for(l = 0; l < 26; l++) {
        for(j = 0; j < letters[l]; j++) {
            do
                r = rand()%length;
            while(word[r]);

            word[r] = 'a' + l;
        }
    }

}

void letters_random(uint8_t letters[26], int length) {
    int i;

    /* Initialize array */
    for(i = 0; i < 26; i++)
        letters[i] = 0;

    /* Randomly distribute the letters */
    for(i = 0; i < length; i++)
        letters[rand()%26] += 1;
}

void letters_print(uint8_t letters[26]) {
    int i;

    for(i = 0; i < 26; i++) printf("%c ", 'a' + i);    printf("\n");
    for(i = 0; i < 26; i++) printf("%d ", letters[i]); printf("\n\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isamino(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;

    if(c == '*' || c == '-')
        return true;

    return false;
}
typedef struct {
    char comment[81];
    char *string;
    size_t length;
} Sequence;

/* Remove trailing newline */
void remove_newline(char *s) {
    if(s[strlen(s)-1] == '\n')
        s[strlen(s)-1] = '\0';
}

Sequence* sequence_read(FILE *file) {
    char line[81], *tmp;
    Sequence *s;

    s = (Sequence*)malloc(sizeof(Sequence));

    /* Read comment */
    while(1) {
        fgets(line, 80, file);
        remove_newline(line);

        if(line[0] == '>') break;
    }


    strcpy(s->comment, line+1);
    s->string = (char*)malloc(129*sizeof(char));
    s->length = 128;

    s->string[0] = '\0';

    /* Read string */
    while(1) {
        fgets(line, 80, file);
        remove_newline(line);

        /* Stop if end of file or end of sequence */
        if(feof(file) || !isamino(line[0]))
            break;

        /* Increase length of string to accommodate the sequence */
        if(strlen(s->string)+strlen(line) > s->length) {
            while(strlen(s->string)+strlen(line) > s->length)
                s->length *= 2;

            tmp = (char*)malloc((s->length+1)*sizeof(char));
            strcpy(tmp, s->string);
            free(s->string);
            s->string = tmp;
        }

        strcat(s->string, line);

    }

    return s;
}

void sequence_print(Sequence *s) {
    int i;

    printf("%s\n", s->comment);
    for(i = 0; i < 80; i++) printf("=");
    printf("\n");
    printf("%s\n", s->string);
}

void sequence_free(Sequence *s) {
    free(s->string);
    free(s);
}

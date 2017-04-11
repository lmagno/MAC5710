#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
char* lower(char *l, char *s);

int main(int argc, char const *argv[]) {
    FILE *file;
    char s[MAX], l[MAX];

    file = fopen(argv[1], "r");
    if(!file) {
        fprintf(stderr, "Couldn't open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while(1) {
        fscanf(file, "%s", s);
        // printf("%s\n", s);
        lower(l, s);
        printf("%s\n", l);
        if(feof(file)) break;
    }
    fclose(file);
    return 0;
}

/* Copy string 's' to string 'l', converting every letter to lowercase */
char* lower(char *l, char *s) {
    int i, n = strlen(s);
    char c;

    for(i = 0; i < n; i++) {
        c = s[i];
        if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
        l[i] = c;
    }
    l[i] = '\0';

    return l;
}

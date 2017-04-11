#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX 100

int max(int a, int b);
char* lower(char *l, char *s);
void count(int *cnt, char *l);
uint64_t hash(char *l);

int main(int argc, char const *argv[]) {
    FILE *file;
    int i, cnt[26];
    int maxlen = 0, maxcount = 0;
    char s[MAX], l[MAX];
    uint64_t h;

    file = fopen(argv[1], "r");
    printf("%lu\n", UINT64_MAX);
    if(!file) {
        fprintf(stderr, "Couldn't open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while(1) {
        fscanf(file, "%s", s);
        // printf("%s\n", s);
        lower(l, s);
        maxlen = max(maxlen, strlen(l));
        count(cnt, l);
        for(i = 0; i < 26; i++) maxcount = max(maxcount, cnt[i]);

        printf("%s\n", l);
        h = hash(l);
        if(feof(file)) break;
    }
    printf("maxlen = %d\n", maxlen);
    printf("maxcount = %d\n", maxcount);
    fclose(file);
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void count(int *cnt, char *l) {
    int i, n = strlen(l);
    int a = 'a' - 'a';
    int z = 'z' - 'a';
    char c;

    for(i = a; i <= z; i++) cnt[i] = 0;

    for(i = 0; i < n; i++) {
        c = l[i];
        cnt[c - 'a'] += 1;
    }

}
uint64_t hash(char *l) {
    int i, n = strlen(l);
    int a = 'a' - 'a';
    int z = 'z' - 'a';
    int count[26] = {0};
    char c;
    uint64_t h;

    for(i = 0; i < n; i++) {
        c = l[i];
        count[c - 'a'] += 1;
    }

    for(i = a; i <= z; i++) printf("%c ", i + 'a');
    printf("\n");

    for(i = a; i <= z; i++) {
        printf("%d ", count[i]);
    }
    printf("\n\n");
    return h;
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

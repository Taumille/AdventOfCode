#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define LEN 19999
#define clear() printf("\033[H\033[J")

void parse_file(const char *filename,char initstring[LEN]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < LEN; i++) {
        char c = fgetc(file);
        initstring[i] = c;
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    char initstring[LEN];

    parse_file("input.txt", initstring);

    long long totallen = 0;
    for (int i = 0; i < LEN; i++){
        totallen += (initstring[i] - '0');
    }
    printf("Total length : %lld\n", totallen);

    int *arr = malloc(totallen * sizeof(int));

    int index = 0;
    int cursor = 0;
    bool isfile = true;

    for (int i = 0; i<LEN; i++) {
        for (int j = 0; j<(initstring[i] - '0'); j++) {
            if (isfile) {
                arr[cursor] = index;
            }
            else {
                arr[cursor] = -1;
            }
            cursor++;
        }
        if (isfile) {
            index++;
        }
        isfile = !isfile;
    }

    for (long long i = 0; i<totallen; i++) {
        printf("%c",(arr[i] == -1) ? '.':arr[i]+'0');
    }
    printf("\n\n");

    long long cursor_a = 0;
    long long cursor_d = totallen-1;

    while (cursor_a < cursor_d) {
        if (arr[cursor_d] == -1)
            cursor_d--;
        else{
            while (arr[cursor_a] != -1) {
                cursor_a++;
            }
            if (cursor_a < cursor_d) {
                arr[cursor_a] = arr[cursor_d];
                arr[cursor_d] = -1;
            }
        }
    }

    for (long long i = 0; i<totallen; i++) {
        printf("%c",(arr[i] == -1) ? ' ':arr[i]+'0');
    }
    printf("\n\n");

    long long result = 0;
    for (long long i = 0; i<totallen; i++) {
        if (arr[i] != -1) {
            result += i*arr[i];
        }
    }

    printf("Result : %lld\n", result);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define LEN 50
#define clear() printf("\033[H\033[J")

struct vec{
    int x;
    int y;
};

int parse_file(const char *filename,char map[LEN][LEN], char dc[256]) {
    FILE *file = fopen(filename, "r");
    int different_char=0;
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            char c = fgetc(file);
            map[i][j] = c;
            // is different ?
            if (c != '.'){
                for (int k = 0; k<different_char; k++) {
                    if (c == dc[k]) {
                        goto not_different;
                    }
                }
                dc[different_char] = c;
                different_char++;
            not_different:
            }
        }
        // Read the newline character at the end of each line
        fgetc(file);
    }

    fclose(file);
    return different_char;
}

void printarr(char map[LEN][LEN],bool antinodes[LEN][LEN]){
    for (int i = 0; i<LEN; i++) {
        for (int j = 0; j<LEN; j++) {
            printf("%c", antinodes[i][j]?'#':map[i][j]);
        }
        printf("\n");
    }
}

bool inarr(int x, int y){
    if (x >= 0 && y>= 0 && x<LEN && y<LEN) {
        return true;
    }
    return false;
}

int findallcombination(char map[LEN][LEN], char c, bool antinodes[LEN][LEN]){
    int len_allant = 1;
    struct vec *allant = malloc(sizeof(struct vec));

    for (int y = 0; y<LEN; y++) {
        for (int x = 0; x<LEN; x++) {
            if (map[y][x] == c){
                allant[len_allant-1].x = x;
                allant[len_allant-1].y = y;
                len_allant++;
                allant = realloc(allant, (len_allant)*sizeof(struct vec));
            }
        }
    }

    int x,y;

    for (int i = 0; i<len_allant-1; i++) {
        for (int j = 0; j<len_allant-1; j++) {
            if (i==j)
                continue;
            x = allant[i].x + (allant[i].x - allant[j].x);
            y = allant[i].y + (allant[i].y - allant[j].y);
            if (inarr(x, y)) {
                antinodes[y][x] = true;
                //printf("Processing %c found (%d,%d) :\n",c,x,y);
                //printf("using %d(%d,%d) and %d(%d,%d) :\n",i,allant[i].x,allant[i].y,j,allant[j].x,allant[j].y);
                //printarr(map, antinodes);
            }
        }
    }
    free(allant);

    return 0;
}
int findallcombination2(char map[LEN][LEN], char c, bool antinodes[LEN][LEN]){
    int len_allant = 1;
    struct vec *allant = malloc(sizeof(struct vec));

    for (int y = 0; y<LEN; y++) {
        for (int x = 0; x<LEN; x++) {
            if (map[y][x] == c){
                allant[len_allant-1].x = x;
                allant[len_allant-1].y = y;
                len_allant++;
                allant = realloc(allant, (len_allant)*sizeof(struct vec));
            }
        }
    }

    int x,y;

    for (int i = 0; i<len_allant-1; i++) {
        for (int j = 0; j<len_allant-1; j++) {
            if (i==j)
                continue;
            x = allant[i].x;
            y = allant[i].y;
            while (inarr(x, y)) {
                antinodes[y][x] = true;
                //printf("Processing %c found (%d,%d) :\n",c,x,y);
                //printf("using %d(%d,%d) and %d(%d,%d) :\n",i,allant[i].x,allant[i].y,j,allant[j].x,allant[j].y);
                //printarr(map, antinodes);
                x += (allant[i].x - allant[j].x);
                y += (allant[i].y - allant[j].y);
            }
            //printf("(%d,%d) not in arr\n", x, y);
        }
    }
    free(allant);

    return 0;
}

int main(int argc, char *argv[])
{
    char map[LEN][LEN];
    bool antinodes[LEN][LEN] = {false};
    char dc[256];
    int nbdc = parse_file("input.txt", map, dc);

    printarr(map, antinodes);
    char c;

    for (int i=0; i<nbdc; i++) {
        c = dc[i]; // Frequency of the processed antenna
        findallcombination(map, c, antinodes);
    }

    printf("\n");

    printarr(map, antinodes);
    int uniquefreq = 0;

    for (int i = 0; i<LEN; i++) {
        for (int j = 0; j<LEN; j++) {
            if (antinodes[i][j])
                uniquefreq++;
        }
    }

    printf("Part 1 : %d\n", uniquefreq);

    uniquefreq = 0;
    bool antinodes2[LEN][LEN] = {false};
    for (int i=0; i<nbdc; i++) {
        c = dc[i]; // Frequency of the processed antenna
        findallcombination2(map, c, antinodes2);
    }

    for (int i = 0; i<LEN; i++) {
        for (int j = 0; j<LEN; j++) {
            if (antinodes2[i][j])
                uniquefreq++;
        }
    }

    printf("Part 2 : %d\n", uniquefreq);

    return EXIT_SUCCESS;
}

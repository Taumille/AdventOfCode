#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define nbR 8
#define nbC 8

struct position{
    int x;
    int y;
};

void parse_file(const char *s, int array[nbR][nbC])
{
    FILE *file = fopen(s, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char c;
    for (int i = 0; i < nbR; i++) {
        for (int j = 0; j < nbC; j++) {
            c = fgetc(file);
            array[i][j] = c-'0';
        }
        fgetc(file);
    }

    fclose(file);
}

struct chain{
    struct position nine;
    struct chain* prev;
    struct chain* next;
};

bool isinarr(struct position p){
    if (p.x >= 0 && 
        p.y >= 0 &&
        p.y < nbR && 
        p.x < nbC) {
        return true;
    }
    return false;
}

struct chain* recurs_find(int tab[nbR][nbC], struct position p){
    struct chain* maill;
    struct chain* initmaill = maill;
    struct position newp;
    if (tab[p.y][p.x] == 9) {
        maill = malloc(sizeof(struct chain));
        maill->nine.x = p.x;
        maill->nine.y = p.y;
        return maill;
    }
    else {
        for (int i = -1; i<=1; i++){
            for (int j = -1; j<=1; j++){
                if (i==0 && j==0) {
                    continue;
                }
                newp.x = p.x + i;
                newp.y = p.y + j;

                if (isinarr(newp) && tab[p.y][p.x]+1 == tab[newp.y][newp.x] ) {
                    maill = recurs_find(tab, newp);
                    while (maill != NULL) {
                        maill = maill->next;
                    }
                }
            }
        }
        return initmaill;
    }
}

int main(int argc, char *argv[])
{
    int tab[nbR][nbC];
    struct position trailhead[nbR*nbC];
    int nbth = 0;

    parse_file("input_test.txt", tab);

    for (int i = 0; i<nbR; i++) {
        for (int j = 0; j<nbC; j++) {
            if (tab[i][j] == 0) {
                trailhead[nbth].x = j;
                trailhead[nbth].y = i;
                nbth++;
                printf("%d,%d\n", i,j);
            }
        }
    }


}

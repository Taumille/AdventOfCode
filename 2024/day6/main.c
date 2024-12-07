#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define nbR 130
#define nbL 130
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void printarr(char (*tab)[nbR][nbL]){
    for (int i = 0; i < nbR; i++) {
        for (int j = 0; j < nbL; j++) {
            printf("%c", (*tab)[i][j]);
        }
        printf("\n");
    }
}

int parse_file(const char *s, int (*guard)[2], char (*tab)[nbR][nbL])
{
    char c = '?';
    int i = 0;
    int j = 0;
    FILE *f = fopen(s, "r");

    if (f == NULL) {
        perror("Failed to open file");
        return -1;
    }

    // Initialize the tab array with '.'
    for (int k = 0; k < nbR; k++) {
        for (int l = 0; l < nbL; l++) {
            (*tab)[k][l] = '.';
        }
    }

    while ((c = fgetc(f)) != EOF) {
        switch (c) {
            case '#':
                (*tab)[j][i] = '#';
                i += 1;
                break;
            case '.':
                (*tab)[j][i] = '.';
                i += 1;
                break;
            case '^':
                (*guard)[0] = j;
                (*guard)[1] = i;
                (*tab)[j][i] = 'X';
                i += 1;
                break;
            case '\n':
                i = 0;
                j += 1;
                break;
            default:
                // Ignore other characters
                break;
        }
    }

    fclose(f);
    return 0;
}

int transform(int (*pos)[2], char (*tab)[nbR][nbL], int *direction, int mod){
    // 0 change pos
    // 1 out of the map
    // 2 Touch rock   
    switch (*direction) {
        case UP:
            if ((*pos)[0] == 0)
                return 1;
            else if ((*tab)[(*pos)[0]-1][(*pos)[1]] == '#'){
                *direction = RIGHT;
                return 2;
            }
            else {
                (*pos)[0] = (*pos)[0] - 1;
                if (mod)
                    (*tab)[(*pos)[0]][(*pos)[1]] = 'X';
                return 0;
            }
        break;
        case RIGHT:
            if ((*pos)[1] == nbL - 1)
                return 1;
            else if ((*tab)[(*pos)[0]][(*pos)[1]+1] == '#'){
                *direction = DOWN;
                return 2;
            }
            else {
                (*pos)[1] = (*pos)[1] + 1;
                (*tab)[(*pos)[0]][(*pos)[1]] = 'X';
                return 0;
            }
        break;
        case DOWN:
            if ((*pos)[0] == nbR - 1)
                return 1;
            else if ((*tab)[(*pos)[0]+1][(*pos)[1]] == '#'){
                *direction = LEFT;
                return 2;
            }
            else {
                (*pos)[0] = (*pos)[0] + 1;
                (*tab)[(*pos)[0]][(*pos)[1]] = 'X';
                return 0;
            }
        break;
        case LEFT:
            if ((*pos)[1] == 0)
                return 1;
            else if ((*tab)[(*pos)[0]][(*pos)[1]-1] == '#'){
                *direction = UP;
                return 2;
            }
            else {
                (*pos)[1] = (*pos)[1] - 1;
                (*tab)[(*pos)[0]][(*pos)[1]] = 'X';
                return 0;
            }
        break;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    char tab[nbR][nbL];
    int guard[2];

    if (parse_file("input.txt", &guard, &tab) != 0) {
        return EXIT_FAILURE;
    }

    int direction = UP;

    int init_guard[2];
    init_guard[0] = guard[0];
    init_guard[1] = guard[1];

    while (transform(&guard, &tab, &direction, 1) != 1) {
        //printarr(&tab);
        //usleep(5000);
        //printf("\033[H\033[J");
    }

    printarr(&tab);
    // Count X
    int result = 0;
    
    for (int i = 0; i<nbR ; i++) {
        for (int j = 0; j<nbL; j++) {
            if (tab[i][j] == 'X')
                result ++;
        }
    }
    printf("Result : %d\n", result);

    // Part 2
    
    result = 0;
    int nb_turn;
    int got_out = 0;

    for (int i = 0; i<nbR ; i++) {
        for (int j = 0; j<nbL; j++) {
            if (tab[i][j] == '#')
                continue;
            else{
                printf("\rStudying pos %d/%d number of valid : %d",i*j,nbR*nbL, result);
                guard[0] = init_guard[0];
                guard[1] = init_guard[1];
                direction = UP;

                tab[i][j] = '#';
                for (nb_turn = 0; nb_turn < nbR*nbL; nb_turn++){
                    got_out = transform(&guard, &tab, &direction, 0);
                    if (got_out == 1)
                        break;
                }
                if (got_out != 1)
                    result++;
                tab[i][j] = '.';
            }
        }
    }

    printf("\nBrute forced result : %d\n", result);

    return EXIT_SUCCESS;
}

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 140
#define LINES 140
#define ASCENDING true
#define DESCENDING false

struct coord {
    int x,y;
};



void parse_file(const char *s, char (*tab)[ROWS][LINES])
{
    char c = '?';
    int i = 0;
    int j = 0;
    FILE *f = fopen(s, "r");

    while (c != EOF) {
        c = fgetc(f);
        switch (c) {
            case '\n':
                i++;
                j=0;
                break;
            case EOF:
                fclose(f);
                return;
            default:
                switch (c) {
                    case 'X':
                        (*tab)[i][j] = 0;
                    break;
                    case 'M':
                        (*tab)[i][j] = 1;
                    break;
                    case 'A':
                        (*tab)[i][j] = 2;
                    break;
                    case 'S':
                        (*tab)[i][j] = 3;
                    break;
                }
                j++;
                break;
        }
    }
    fclose(f);
}

bool intab(int i, int j){
    return i >= 0 && j >= 0 && i <= ROWS && j <= LINES;
}

int r_isxmas(int i, int j, int di, int dj, char (*tab)[ROWS][LINES], char letter){
    if (letter == 4)
        return 1;
    else if (intab(i+di, j+dj) && (*tab)[i+di][j+dj] == letter)
        return r_isxmas(i+di, j+dj, di, dj, tab, letter+1);
    else
        return 0;
}

int isxmas(int i, int j, char (*tab)[ROWS][LINES]){
    // Find direction
    int di,dj;
    int result = 0;
    for (di = -1; di<=1; di++){
        for (dj = -1; dj<=1; dj++) {
            if ((di != 0 || dj != 0) && intab(i+di, j+dj)) {
                if ((*tab)[i + di][j + dj] == 1) {
                    result += r_isxmas(i + di, j + dj, di, dj, tab, 2);
                }
            }
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    char tab[ROWS][LINES] = {0};
    parse_file("input.txt", &tab);
    
    int result = 0;

    // Part 1
    
    for (int i = 0; i<ROWS; i++) {
        for (int j = 0; j<LINES; j++) {
            if (tab[i][j] == 0){
                result += isxmas(i, j, &tab);
            }
        }
    }
    printf("Result : %d\n", result);

    // Part 2
    result = 0;

    for (int i = 1; i < ROWS-1; i++){
        for (int j = 1; j<LINES-1; j++) {
            if (tab[i][j] == 2 &&
                tab[i-1][j-1] == tab[i-1][j+1] &&
                tab[i+1][j-1] == tab[i+1][j+1] &&
                tab[i+1][j-1] != tab[i-1][j-1] &&
                tab[i+1][j-1] != 0 &&
                tab[i+1][j-1] != 2 &&
                tab[i-1][j+1] != 0 &&   
                tab[i-1][j+1] != 2   
            ){
                    //printf("Atype : %d,%d\n",i,j);
                    result++;
                }
            else if (tab[i][j] == 2 &&
                tab[i-1][j-1] == tab[i+1][j-1] &&
                tab[i-1][j+1] == tab[i+1][j+1] &&
                tab[i+1][j-1] != tab[i+1][j+1] &&
                tab[i+1][j-1] != 0 &&
                tab[i+1][j-1] != 2 &&
                tab[i-1][j+1] != 0 &&   
                tab[i-1][j+1] != 2   
                ){
                    //printf("Btype : %d,%d\n",i,j);
                   result++;
            }

        }
    }
    printf("Result : %d\n", result);

    return 0;
}

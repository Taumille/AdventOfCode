#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 1024
#define ASCENDING true
#define DESCENDING false

void print_tab(int len, int *tab){
    printf("\n");
    for (int i=0; i<len; i++) {
        printf("%d", tab[i]);
        if (i!=len-1)
            printf(", ");
    }
}

int parse_file(const char *s, int *cursor, int *tab)
{
    char c = '?';
    int i = 0;
    int written_number = 0;
    FILE *f = fopen(s, "r");
    fseek(f, *cursor, SEEK_SET);

    while (c != EOF) {
        c = fgetc(f);
        *cursor += 1;
        if (c >= '0' && c <= '9') {
            written_number = written_number * 10 + (c - '0');
        } else if (written_number != 0) {
            tab[i] = written_number;
            i++;
            if (c == '\n')
                goto endparse;
            written_number = 0;
        }
    }

  endparse:
    fclose(f);
    return i;
}

bool satisfied(bool direction, int x0, int x1)
{
    if ((direction && x0 >= x1) || (!direction && x1 >= x0))
        return false;
    if ((direction && (x1 - x0) > 3) || (!direction && (x0 - x1) > 3))
        return false;
    return true;
}

int** cut_list(int len, int *tab){
    int** cutted = malloc(len * sizeof(int*));
    for (int j=0; j<len; j++){
        cutted[j] = malloc((len - 1) * sizeof(int));
        for (int k=0; k<len; k++) {
            if (k<j)
                cutted[j][k] = tab[k];
            else if (k>j)
                cutted[j][k-1] = tab[k];
        }
    }
    return cutted;
}

int main(int argc, char *argv[])
{

    int tab[MAX_LEN] = { 0 };
    int cursor = 0;
    int len;
    int result = 0;
    bool direction = ASCENDING;

    while ((len = parse_file("input.txt", &cursor, tab))) {
        if (tab[1] < tab[0])
            direction = DESCENDING;
        for (int j = 0; j < len - 1; j++) {
            if (!satisfied(direction, tab[j], tab[j + 1]))
                goto endwhile;
        }
        result++;
      endwhile:
        direction = ASCENDING;
    }

    printf("Part 1 : %d\n", result);

    /*
     * Part 2
     */
    cursor = 0;
    result = 0;
    int** error_margin_tab;

    while ((len = parse_file("input.txt", &cursor, tab))) {
        if (tab[1] < tab[0])
            direction = DESCENDING;
        for (int j = 0; j < len - 1; j++) {
            if (!satisfied(direction, tab[j], tab[j + 1])){
                // Examine error margin
                error_margin_tab = cut_list(len, tab);
                for (int k =0; k < len; k++){ // For each cutted list
                    direction = error_margin_tab[k][1] > error_margin_tab[k][0];
                    for (int l = 0; l < len - 2; l++) {
                        if (!satisfied(direction, error_margin_tab[k][l], error_margin_tab[k][l + 1]))
                            goto nextcutted_list;
                    }
                    // One cutted list survived
                    result++;
                    goto freetable;
                    nextcutted_list:
                }
            freetable:
                for (int k = 0; k < len; k++) {
                    free(error_margin_tab[k]);
                }
                free(error_margin_tab);
                goto endwhile2;
            }
        }
        result++;
      endwhile2:
        direction = ASCENDING;
    }

    printf("\n");
    printf("Part 2 : %d\n", result);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define nbR 55
#define nbC 55

struct position{
    int x;
    int y;
};

struct chain* first_elem;

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
    struct chain* next;
};

bool isinarr(int x, int y){
    if (x >= 0 && 
        y >= 0 &&
        y < nbR && 
        x < nbC) {
        return true;
    }
    return false;
}

struct position recurs_find(int tab[nbR][nbC], struct position p){
    //printf("\tTrying (%d,%d)\n", p.x, p.y);
    struct position tmp;
    struct position *result;
    struct chain *tmpchain;
    // Try up
    if (isinarr(p.x, p.y-1) && tab[p.y][p.x] == tab[p.y-1][p.x] - 1) {
        tmp.x = p.x;
        tmp.y = p.y-1;
        result = malloc(sizeof(struct position));
        *result = recurs_find(tab, tmp);
        if (tab[result->y][result->x] == 9) {
            //printf("Found 9 in (%d,%d)\n", result->x, result->y);
            tmpchain = first_elem;
            first_elem = malloc(sizeof(struct chain));
            first_elem->nine.x = tmp.x;
            first_elem->nine.y = tmp.y;
            first_elem->next = tmpchain;
        }
        free(result);
    }
    // Try right
    if (isinarr(p.x+1, p.y) && tab[p.y][p.x] == tab[p.y][p.x+1] - 1) {
        tmp.x = p.x+1;
        tmp.y = p.y;
        result = malloc(sizeof(struct position));
        *result = recurs_find(tab, tmp);
        if (tab[result->y][result->x] == 9) {
            //printf("Found 9 in (%d,%d)\n", result->x, result->y);
            tmpchain = first_elem;
            first_elem = malloc(sizeof(struct chain));
            first_elem->nine.x = tmp.x;
            first_elem->nine.y = tmp.y;
            first_elem->next = tmpchain;
        }
        free(result);
    }
    // Try down
    if (isinarr(p.x, p.y+1) && tab[p.y][p.x] == tab[p.y+1][p.x] - 1) {
        tmp.x = p.x;
        tmp.y = p.y+1;
        result = malloc(sizeof(struct position));
        *result = recurs_find(tab, tmp);
        if (tab[result->y][result->x] == 9) {
            //printf("Found 9 in (%d,%d)\n", result->x, result->y);
            tmpchain = first_elem;
            first_elem = malloc(sizeof(struct chain));
            first_elem->nine.x = tmp.x;
            first_elem->nine.y = tmp.y;
            first_elem->next = tmpchain;
        }
        free(result);
    }
    // Try left
    if (isinarr(p.x-1, p.y) && tab[p.y][p.x] == tab[p.y][p.x-1] - 1) {
        tmp.x = p.x-1;
        tmp.y = p.y;
        result = malloc(sizeof(struct position));
        *result = recurs_find(tab, tmp);
        if (tab[result->y][result->x] == 9) {
            //printf("Found 9 in (%d,%d)\n", result->x, result->y);
            tmpchain = first_elem;
            first_elem = malloc(sizeof(struct chain));
            first_elem->nine.x = tmp.x;
            first_elem->nine.y = tmp.y;
            first_elem->next = tmpchain;
        }
        free(result);
    }

    return p;
}

void removeDuplicates(struct chain* head) {
    if (head == NULL) return;

    struct chain* current = head;
    struct chain* runner;
    struct chain* prev;

    while (current != NULL && current->next != NULL) {
        runner = current;
        while (runner->next != NULL) {
            if (current->nine.x == runner->next->nine.x && current->nine.y == runner->next->nine.y) {
                prev = runner;
                struct chain* toDelete = runner->next;
                prev->next = toDelete->next;
                free(toDelete);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

int main(int argc, char *argv[])
{
    int tab[nbR][nbC];
    struct position tmp;
    first_elem = malloc(sizeof(struct chain));
    first_elem->nine.x = -1;
    first_elem->nine.y = -1;
    first_elem->next = NULL;
    struct chain* nextnode;

    parse_file("input.txt", tab);

    int result = 0;
    for (int i = 0; i<nbR; i++) {
        for (int j = 0; j<nbC; j++) {
            if (tab[i][j] == 0) {
                printf("Found 0 in (%d,%d)\n", j,i);
                tmp.x = j;
                tmp.y = i;
                recurs_find(tab, tmp);
                //removeDuplicates(first_elem);
                while (first_elem->next != NULL) {
                    result++;
                    //printf("(%d,%d)\n", first_elem->nine.x, first_elem->nine.y);
                    nextnode = first_elem->next;
                    free(first_elem);
                    first_elem = nextnode;
                }
                free(first_elem);
                first_elem = malloc(sizeof(struct chain));
                first_elem->nine.x = -1;
                first_elem->nine.y = -1;
                first_elem->next = NULL;
                printf("Result so far %d\n", result);
            }
        }
    }


}

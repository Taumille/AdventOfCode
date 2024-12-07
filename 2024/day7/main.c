#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define LEN 850
#define ADD 0
#define MUL 1

struct equation {
    long test;
    long vals[128];
    int len;
};


int parse_file(const char *filename, struct equation eq[LEN]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    char line[100];
    int i = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ": ");
        eq[i].test = atol(token);
        eq[i].len = 0;

        while ((token = strtok(NULL, ": ")) != NULL) {
            eq[i].vals[eq[i].len++] = atol(token);
        }

        i++;
    }

    fclose(file);
    return 0;
}

long concat(long a, long b){
    unsigned pow = 10;
    while(b >= pow)
        pow *= 10;
    return a * pow + b;
}

int recurs(int i, struct equation e, long res, bool part2){
    if (i == e.len)
        return res == e.test ? 1 : 0;
    else if (res > e.test)
        return 0;
    else {
        if (part2)
            return recurs(i+1, e, res+e.vals[i], part2) ||
                   recurs(i+1, e, res*e.vals[i], part2) ||
                   recurs(i+1, e, concat(res, e.vals[i]), part2);
        else
            return recurs(i+1, e, res+e.vals[i], part2) ||
                   recurs(i+1, e, res*e.vals[i], part2);
    }
    }

int main(int argc, char *argv[])
{
    struct equation eq[LEN];

    parse_file("input.txt", eq);
    
    long nb_correct = 0;
    for (int i = 0; i < LEN; i++) {
        printf("Processing equation[%d]",i);
        if (recurs(1, eq[i], eq[i].vals[0], false)){
            nb_correct+=eq[i].test;
        }
        printf("\rProcessed  equation[%d]\n",i);
    }

    printf("Part 1 nb correct : %ld\n", nb_correct);
 
    nb_correct = 0;
    for (int i = 0; i < LEN; i++) {
        printf("Processing equation[%d]",i);
        if (recurs(1, eq[i], eq[i].vals[0], true)){
            nb_correct+=eq[i].test;
        }
        printf("\rProcessed  equation[%d]\n",i);
    }

    printf("Part 2 nb correct : %ld\n", nb_correct);


    return EXIT_SUCCESS;
}

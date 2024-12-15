#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define NBDIGIT(x) ((long)floor(log10 (x)) + 1)

struct stone{
    long val;
    struct stone* next;
};

struct stone* parse_file(const char *s){
    FILE* file = fopen(s, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    struct stone* head = NULL;
    struct stone* tail = NULL;
    long number;

    while (fscanf(file, "%ld", &number) == 1) {
        struct stone* newNode = (struct stone*)malloc(sizeof(struct stone));
        if (newNode == NULL) {
            perror("Error allocating memory");
            return NULL;
        }
        newNode->val = number;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(file);
    return head;
}

struct stone* _blink_atom(struct stone* elem){
    //printf("Processing %d nbdigit : %d\n", elem->val, NBDIGIT(elem->val)%2);
    if (elem->val == 0) {
        //printf("Equal 0\n");
        elem->val = 1;
    }
    else if (NBDIGIT(elem->val) % 2 == 0) {
        //printf("Even number of digit\n");
        long right, left;
        left = elem->val / ((long)pow(10,NBDIGIT(elem->val)/2));
        right = elem->val - left * pow(10, NBDIGIT(elem->val)/2);

        struct stone* tmp = elem->next;
        //printf("Data : %d, left %d, right %d\n", elem->val, left, right);
        elem->val = left;
        elem->next = malloc(sizeof(struct stone));
        elem->next->val = right;
        elem->next->next = tmp;
        elem = elem->next;
    }
    else {
        //printf("Else *2024\n");
        elem->val *= 2024;
    }
    return elem;
}

void blink(struct stone* elem){
    while (elem != NULL) {
        elem = _blink_atom(elem);
        elem = elem->next;
    }
}

int main(int argc, char *argv[])
{
    struct stone* first_stone = parse_file("input.txt");
    struct stone* curr_stone = first_stone;

    while (curr_stone != NULL) {
        printf("%ld ", curr_stone->val);
        curr_stone = curr_stone->next;
    }
        printf("\n");
    for (int i = 0; i<25; i++) {
        blink(first_stone);
        curr_stone = first_stone;
        while (curr_stone != NULL) {
            //printf("%ld ", curr_stone->val);
            curr_stone = curr_stone->next;
        }
        //printf("\n");
    }
    
    long nbstone = 0;
    curr_stone = first_stone;
    while (curr_stone != NULL) {
        curr_stone = curr_stone->next;
        nbstone++;
    }
    
    printf("[PART 1] Number of stone : %ld\n", nbstone);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define LEN 19999
#define MAXLEN 1048576
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

struct space{
    int size;
    int content;
    struct space* next;
    struct space* prev;
};

void print_disk(struct space* first_sect, struct space* end_sect){
    struct space* curr_sect = first_sect;
    while (curr_sect!=end_sect) {
        for (int i = 0; i<curr_sect->size; i++) {
            printf("%c",(curr_sect->content == -1)?'.':curr_sect->content+'0');
        }
        curr_sect = curr_sect->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char initstring[LEN];

    parse_file("input.txt", initstring);

    struct space first_sect;
    struct space *current_sect = &first_sect;
    struct space *last_sect;

    int index = 0;
    bool isfile = true;

    for (int i = 0; i<LEN; i++) {
        if (isfile){
            current_sect->size = initstring[i]-'0';
            current_sect->content = index;
            index++;
        }
        else {
            current_sect->size = initstring[i]-'0';
            current_sect->content = -1;
        }

        isfile = !isfile;
        current_sect->next = malloc(sizeof(struct space));
        current_sect->next->prev = current_sect;
        current_sect = current_sect->next;
    }
    last_sect = current_sect;
    free(last_sect->next);

    print_disk(&first_sect, last_sect);

    struct space *beg_sect;
    struct space *end_sect = last_sect;
    struct space *tmp;

    while (end_sect != &first_sect) { // For all sect starting from the end 
        if (end_sect->content!=-1) { // If the sect contains a file
            //printf("\tTrying to empty a sect of size %d containing %d\n", end_sect->size, end_sect->content);
            beg_sect = &first_sect;
            while (beg_sect->next != end_sect &&
                   !(beg_sect->content == -1 && 
                   beg_sect->size >= end_sect->size)) {
                //printf("Sect of size %d/%d containing %d\n",beg_sect->size,end_sect->size,beg_sect->content);
                //print_disk(&first_sect, last_sect);
                beg_sect = beg_sect->next;
            } // While the beg sect isn't big enough search the next one

            // If the beg_sect is big enough
            if (beg_sect->size >= end_sect->size && beg_sect->content == -1) {
                //printf("Found sect of size %d\n", beg_sect->size);
                // ....|AAA -> AAA|.|...
                if (beg_sect->next->content == -1) {
                    beg_sect->next->size += beg_sect->size - end_sect->size;
                    beg_sect->size = end_sect->size;
                    beg_sect->content = end_sect->content;
                    end_sect->content = -1;
                    //printf("Option 1 : Now of size %d and contains %d\n", beg_sect->size, beg_sect->content);
                }
                else {
                    tmp = beg_sect->next; // Save the current next sect
                    // Create a middle sect
                    beg_sect->next = malloc(sizeof(struct space));
                    beg_sect->next->size = beg_sect->size;
                    beg_sect->next->content = -1;
                    beg_sect->next->next = tmp;
                    beg_sect->next->prev = beg_sect;
                    // Put the end sect at the begginning
                    beg_sect->size = end_sect->size;
                    beg_sect->next->size -= end_sect->size;
                    beg_sect->content = end_sect->content;
                    end_sect->content = -1;
                    //printf("Option 2 : Now of size %d and contains %d\n", beg_sect->size, beg_sect->content);
                }
            }
            else {
                end_sect = end_sect->prev;
            }
        }
        else {
            end_sect = end_sect->prev;
        }
    }

    printf("\n\n");
    int disk[MAXLEN] = {0};
    current_sect = &first_sect;
    int j = 0;
    while (current_sect!=last_sect) {
        for (int i = 0; i<current_sect->size; i++) {
            printf("%d\n",j);
            disk[j] = current_sect->content;
            j++;
        }
        current_sect = current_sect->next;
    }

    //print_disk(&first_sect, last_sect);

    long long result = 0;
    for (int i = 0; i<MAXLEN; i++) {
        if (disk[i] != -1) {
            result += i * disk[i];
        }
    }

    printf("\n\nResult : %lld \n", result);

    return EXIT_SUCCESS;
}

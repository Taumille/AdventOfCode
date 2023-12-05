#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENBUFF 100

typedef struct{
    int tab[LENBUFF];
    int index;
} cards;

int sum = 0;
cards winning_card;
cards my_card;

void reset_tab(){
    int i;
    for (i = 0; i<LENBUFF; i++){
        winning_card.tab[i] = -1;
        my_card.tab[i] = -1;
    }
    winning_card.index = 0;
    my_card.index = 0;
}

void compare(){
    int tot = 0;
    for (int i = 0; i<my_card.index; i++){
        for (int j = 0; j<winning_card.index; j++){
            if (winning_card.tab[j] == my_card.tab[i]){
                if (!tot){tot = 1;}
                else {tot*=2;}
                printf("%d : Correspondance entre %d et %d.\n", winning_card.tab[j],j ,i);
                break;
            }
        }
    }
    sum += tot;
    printf("Total : %d\n",tot);

    reset_tab();
}

int main(int argc, char *argv[])
{
    reset_tab();
    char c;
    int current_num = 0;
    bool innum = false;
    int side = 1; // 1 in Card : 2 in the winning cards 3 in your cards
    FILE *fptr = fopen("input", "r");
    int n = 0;
    
    c = fgetc(fptr);
    do{
        if (side == 1 && c != ':'){continue;}
        else if (side == 1) { side = 2;}
        else if (side == 2) {
            if (c == '|'){
                side = 3;
            }
            else if (c == ' ' && innum) {
                winning_card.tab[winning_card.index] = current_num;
                printf("Entered %d\n",winning_card.tab[winning_card.index]);
                winning_card.index++;
                current_num = 0;
                innum = false;
            }
            else if (c >= '0' && c <= '9'){
                innum = true;
                current_num = current_num * 10 + (c-'0');
            }
        }
        else if (side == 3) {
            if (c == ' ' || c == '\n' && innum) {
                my_card.tab[my_card.index] = current_num;
                my_card.index++;
                current_num = 0;
                innum = false;
            }
            else if (c >= '0' && c <= '9'){
                current_num = current_num * 10 + (c-'0');
                innum = true;
            }
            if (c == '\n' || c == EOF){
                side = 1;
                compare();
                printf("New line %d\n", n);
                n++;
            }
        }
    }while ((c = getc(fptr)) != EOF);

    printf("Sum : %d\n",sum);
    

    return EXIT_SUCCESS;
}

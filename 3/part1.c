#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define LENTAB 140

typedef struct{
    int i,j;
    int val;
} Point;

typedef struct gear{
    int i,j;
    int val1, val2;
    struct gear *next;
}gear_t;

char data[LENTAB][LENTAB];
gear_t *Gears;

void complete_gear(int i, int j, int val){
    printf("Gear to complete : (%d,%d)\n",i,j);
    gear_t *cursor = Gears;
    while (cursor->next != NULL){
        cursor = cursor->next;
        if (cursor->i == i && cursor->j == j){
            cursor->val2 = val;
            printf("Gear (%d,%d) complete %d*%d\n",i,j,cursor->val1,cursor->val2);
            return;
        }
    }
    cursor->next = malloc(sizeof(gear_t));
    cursor = cursor->next;
    cursor->i = i;
    cursor->j = j;
    cursor->val1 = val;
    cursor->val2 = 0;
    printf("Gear created : (%d,%d)\n",i,j);
}

int is_neighbor(Point p){
    int length = (int)floor(log10(p.val))+1;
    int ci,cj;
    for (int modi = -1; modi<=length; modi++){
        for (int modj = -1; modj<=1; modj++){
            if (modj == 0 && modi != -1 && modi != length){continue;}
            ci = p.i+modi;
            cj = p.j+modj;
            if (ci>=0 && ci<LENTAB && cj>=0 && cj<LENTAB){
                if (data[cj][ci] != '.' && !(data[cj][ci]>='0' && data[cj][ci]<='9')){
                    if (data[cj][ci] == '*'){complete_gear(ci, cj, p.val);}
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fptr = fopen("input", "r");
    char c;
    int i=0;
    int j=0;
    Gears = malloc(sizeof(gear_t));
    while ((c = fgetc(fptr)) != EOF){
        if (c == '\n'){
            j++;
            i = 0;
        }
        else{
            data[j][i] = c;
            i++;        
            printf("%c",c);
        }
    }
    printf("\n Data written\n");

    int sum = 0;
    Point current_num;
    bool innum;

    for (int j = 0; j<LENTAB; j++){
        for (int i = 0; i<LENTAB; i++){
            //printf("%c",data[j][i]);
            if (data[j][i]>='0' && data[j][i]<='9'){
                if (innum){
                    current_num.val = current_num.val * 10 + data[j][i] - '0';
                }
                else{
                    current_num.i = i;
                    current_num.j = j;
                    current_num.val = data[j][i] - '0';
                    innum = true;
                }
            }
            else if (innum){
                if (is_neighbor(current_num)){
                    //printf("%d in sum\n", current_num.val);
                    sum += current_num.val;
                }
                innum = false;
            }
        }
    }
    printf("Sum : %d\n",sum);
    int gearratios = 0;
    gear_t *cursor = Gears;
    while (cursor != NULL) {
        gearratios += cursor->val1 * cursor->val2;
        cursor = cursor->next;
    }
    printf("Gear ratio : %d\n",gearratios);
    
    return EXIT_SUCCESS;
}

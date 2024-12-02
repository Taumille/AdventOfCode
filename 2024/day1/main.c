#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 8

struct list {
    int list[1024];
    int size;
};

int parse_file(const char* s, struct list* a, struct list* b){
    char c = '?';
    int written_number = 0;
    bool writing_a = true;
    FILE* f = fopen(s, "r");

    while (c != EOF) {
        c = fgetc(f);
        if (c >= '0' && c <= '9'){
            written_number = written_number * 10 + (c-'0');            
        }
        else if (written_number != 0) {
            if (writing_a){
                a->list[a->size] = written_number;
                a->size++;
            }
            else {
                b->list[b->size] = written_number;
                b->size++;
            }
            written_number = 0;
            writing_a = !writing_a;
        }
    
    }
    
    return 0;
}

void _swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int _partition(struct list* l, int lo, int hi){
    int pivot = l->list[hi];
    int tmp;

    int i = lo - 1;
    for (int j = lo; j <= hi -1; j++){
        if (l->list[j] < pivot) {
            i++;
            _swap(&l->list[i], &l->list[j]);
        }
    }
    _swap(&l->list[i+1], &l->list[hi]);

    return i+1;
}

int quicksort(struct list * l, int lo, int hi){
    if (lo < hi) {
        int pi = _partition(l, lo, hi);
        quicksort(l, lo, pi - 1);
        quicksort(l, pi + 1, hi);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    struct list a,b;
    a.size = 0;
    b.size = 0;

    parse_file("input.txt", &a, &b);
    quicksort(&a, 0, a.size-1);
    quicksort(&b, 0, b.size-1);

    int result = 0;

    /*
    * Part 1
    */
    for (int i = 0; i<a.size; i++) {
        if (a.list[i]>b.list[i])
            result += a.list[i]-b.list[i];
        else
            result += b.list[i]-a.list[i];
    }

    printf("Part 1 : %d\n", result);

    /*
    * Part 2
    */
    int similarity_score = 0;
    int multiplier;
    int left_nb = 0;
    int prev_nb;
    int right_index = 0;
    for (int i = 0; i < a.size; i++){
        prev_nb = left_nb;
        left_nb = a.list[i];
        if (left_nb == prev_nb){
            similarity_score += left_nb*multiplier;
            continue;
        }
        multiplier = 0;
        while (b.list[right_index] < left_nb){
            //printf("%d < %d\n", b.list[right_index], left_nb);
            right_index++;
        }
        while (b.list[right_index] == left_nb){
            //printf("%d = %d\n", b.list[right_index], left_nb);
            right_index++;
            multiplier++;
        }
        //printf("%d * %d\n", left_nb, multiplier);
        similarity_score += left_nb*multiplier;
    }

    printf("Part 2 : %d\n", similarity_score);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

long process_number(long x){
    int len = floor(log10(x))+1;
    if (len==1)
        return 0;

    long tmp, pattern;
    // For each number of digit, if it can divide x
    for (int div = 1; div <= len / 2; div++) {
        if (len % div)
            continue;
        tmp = x / (long)pow(10, div);
        pattern = x % (long)pow(10, div);
        //printf("tmp : %ld, pattern %ld\n", tmp, pattern);
        while (tmp != 0) {
            if (tmp % (long)pow(10, div) != pattern)
                break;
            tmp /= (long)pow(10, div);
        }
        if (tmp == 0){
            printf("It's a match : %ld\n", x);
            return x;
        }
    }
    return 0;
}

int main(){
    FILE* in = stdin;
    char* ps = malloc(1000*sizeof(char));
    fgets(ps, 1000, in);

    char *ps_split = malloc(1000*sizeof(char));
    long a,b;
    long sum = 0;
    
    ps_split = strtok(ps, ",");
    while (ps_split != NULL){
        sscanf(ps_split, "%ld-%ld", &a, &b);

        for (long i = a; i<=b; i++){
            // Find the len of i
            sum += process_number(i);
        }

        ps_split = strtok(0, ",");
    }
    free(ps);
    free(ps_split);
    printf("Sum = %ld\n", sum);
    return 0;
}

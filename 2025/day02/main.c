#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    FILE* in = stdin;
    char* ps = malloc(1000*sizeof(char));
    fgets(ps, 1000, in);
    printf("s : %s", ps);

    char *ps_split = malloc(1000*sizeof(char));
    long a,b;
    int len;
    int i_LSD, i_MSD;
    long sum = 0;
    
    ps_split = strtok(ps, ",");
    while (ps_split != NULL){
        sscanf(ps_split, "%ld-%ld", &a, &b);

        for (long i = a; i<=b; i++){
            // Find the len of i
            len = floor(log10(i))+1;
            if (len % 2 == 1)
                continue;
            i_LSD = i % (int)pow(10, len / 2);
            i_MSD = i / (int)pow(10, len / 2);
            if (i_LSD == i_MSD)
                sum += i;
        }

        ps_split = strtok(0, ",");
    }
    free(ps);
    printf("Sum = %ld\n", sum);
    return 0;
}

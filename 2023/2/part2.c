#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if (a>=b){return a;}
    return b;
}

int main(int argc, char *argv[])
{
    // red green blue
    size_t buffersize = 256 * sizeof(char);
    char * buffer = (char*) malloc(buffersize);
    int max_tir[3];
    int sum = 0;
    int j = 0;
    int tmp;

    FILE *fptr = fopen("input", "r");

    for (int i=1; i<=100; i++){
        max_tir[0] = 0;
        max_tir[1] = 0;
        max_tir[2] = 0;
        getline(&buffer, &buffersize, fptr);
        j=0;
        while (buffer[j] != ':'){j++;}
        j++;
        while (buffer[j] != '\0'){
            if (buffer[j] >= '0' && buffer[j]<='9'){tmp = tmp*10 + buffer[j] - '0'; j++;}
            else if (buffer[j] == ' ') {j++;}
            else if (buffer[j] == 'r' && buffer[j+1] == 'e' && buffer[j+2] == 'd') {max_tir[0] = max(max_tir[0],tmp);j+=4; tmp = 0;}
            else if (buffer[j] == 'g' && buffer[j+1] == 'r' && buffer[j+2] == 'e' && buffer[j+3] == 'e' && buffer[j+4] == 'n') {max_tir[1] = max(max_tir[1],tmp);j+=6; tmp = 0;}
            else if (buffer[j] == 'b' && buffer[j+1] == 'l' && buffer[j+2] == 'u' && buffer[j+3] == 'e') {max_tir[2] = max(max_tir[2],tmp); j+=5; tmp = 0;}
            else {
            printf("ERROR scanned '%c', sum = %d, tmp = %d, i = %d\n",buffer[j], sum, tmp, i);
            exit(1);
            }
            
        }
        sum += max_tir[0]*max_tir[1]*max_tir[2];
        printf("%d red, %d green %d blue\n",max_tir[0],max_tir[1],max_tir[2]);
        printf("Power : %d\n",max_tir[0]*max_tir[1]*max_tir[2]);
        printf("i = %d, new sum = %d\n",i,sum);

    }

    printf("Sum = %d\n",sum);

    return EXIT_SUCCESS;
}

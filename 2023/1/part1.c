#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

int main(int argc, char *argv[])
{
    FILE *fptr = fopen("input", "r");
    int result = 0;
    char c;
    int fd = 0;
    char sd = 0;
    int8_t n = 0;
    do {
        c = (char)fgetc(fptr);
        if (c != EOF){
            if (c>='0' && c<='9'){
                if (n == 0){
                    n++;
                    fd = (c - '0');
                    sd = (c - '0');
                }
                else{
                    sd = c - '0';
                }
            }
            else if (c == '\n') {
                n = 0;
                result += fd * 10 + sd;
                printf("Read %i, new value is %d\n",fd * 10 + sd ,  result);
                printf("Cric\n");}
        }
    }while (c != EOF);

    printf("%i\n",result);

    return EXIT_SUCCESS;
}

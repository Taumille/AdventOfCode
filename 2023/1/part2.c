#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

int compare(char *in, char *mask){
    for (int i=0; i<strlen(mask); i++){
        if (in[i] == '\0'){return 0;}
        else if (in[i] != mask[i]) {return 0;}
    }
    return 1;
}

int findnum(char *buff){
    char *mask;
    if (buff[0]>='0' && buff[0]<='9'){return buff[0]-'0';}
    mask = (char *)malloc(4*sizeof(char));
    mask = "zero";
    if (compare(buff, mask)){return 0;}
    mask = (char *)malloc(3*sizeof(char));
    mask = "one";
    if (compare(buff, mask)){return 1;}
    mask = (char *)malloc(3*sizeof(char));
    mask = "two";
    if (compare(buff, mask)){return 2;}
    mask = (char *)malloc(4*sizeof(char));
    mask = "three";
    if (compare(buff, mask)){return 3;}
    mask = (char *)malloc(4*sizeof(char));
    mask = "four";
    if (compare(buff, mask)){return 4;}
    mask = (char *)malloc(4*sizeof(char));
    mask = "five";
    if (compare(buff, mask)){return 5;}
    mask = (char *)malloc(3*sizeof(char));
    mask = "six";
    if (compare(buff, mask)){return 6;}
    mask = (char *)malloc(5*sizeof(char));
    mask = "seven";
    if (compare(buff, mask)){return 7;}
    mask = (char *)malloc(5*sizeof(char));
    mask = "eight";
    if (compare(buff, mask)){return 8;}
    mask = (char *)malloc(4*sizeof(char));
    mask = "nine";
    if (compare(buff, mask)){return 9;}
    return -1;
}

int main(int argc, char *argv[])
{
    FILE *fptr = fopen("input", "r");
    size_t buffersize = 64*sizeof(char);
    char *buffer = (char *)malloc(buffersize);
    int count = 0;
    int n;
    int fd,sd,tmp;
    int result = 0;

    do {
        n=0;
        getline(&buffer, &buffersize, fptr);
        count++;
        for (int i=0; i<strlen(buffer); i++) {
            tmp = findnum(&buffer[i]);
            if (tmp != -1){
            printf("Read %d in %s\n",tmp,&buffer[i]);
                if (n==0){
                    fd = tmp;
                    n++;
                }
                sd = tmp;
            }
        }
        result += fd*10 + sd;
    }while (count < 1000);
    
    printf("Result : %d\n",result);

    return 0;
}

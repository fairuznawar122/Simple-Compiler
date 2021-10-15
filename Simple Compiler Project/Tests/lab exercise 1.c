#include <stdio.h>
int main(){

    FILE *p1, *p2;
    int count=1;
    char x;
    int newline=1;
    p1 = fopen("input1.c", "r");
    p2 = fopen("output.txt","w");

    while((x = fgetc(p1))!= EOF){
        if(newline){
        fprintf(p2, "%d",count);
        fputc(':', p2);
        newline=0;
        }
        fputc(x, p2);
        if (x=='\n'){
            count++;
            fputc('\n', p2);
            fprintf(p2, "%d",count);
            fputc(':', p2);
        }
    }

}

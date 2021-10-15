#include<stdio.h>
#include<conio.h>

int main()
{
    FILE *input;
    input= fopen("in.c","w");
    char c;
    while ((c = getchar()) != '$')
    {
        fputc(c,input);
    }
    return 0;
}

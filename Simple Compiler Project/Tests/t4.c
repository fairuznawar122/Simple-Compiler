
#include <stdio.h>
#include <stdlib.h>
#define MAX 20


int main ()
{
    char exp[100];
    char *ptr;
    long ret;
    char *pch, prev[100],curr[100];
    int i = 0,j=0,n=0;
    int line=0;


    FILE *f1;
    f1 = fopen("token.txt","r");


    while(fgets(exp, 100, f1))
    {
        line++;
        if(!strcmp(exp,"\n")){
            continue;
        }
        strtok(exp, "\n");
        printf("%s",exp);

        for(i =0;i<strlen(exp);i++){
            if(exp[i]==' '){
                strcpy(prev,curr);
                continue;
            }
            else{
                strcat(curr,exp[i]);
            }
            printf("%s\n",curr);
        }


    }

    return(0);
}


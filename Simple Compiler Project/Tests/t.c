
#include <stdio.h>
#include <stdlib.h>
#define MAX 20


int main ()
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0,j=0,count=0;



    FILE *f1;
    f1 = fopen("IntermediateOutput.txt","r");


    while(fgets(exp, 100, f1))
    {

        if(!strcmp(exp,"\n"))
        {
            continue;
        }
        
        strtok(exp, "\n");
        
        ret = strtol(exp, &ptr, 10);
        printf("%s\n",exp);
        
        
        for(i=0;i<strlen(exp);i++){
            if(exp[i]==';'){
                for(j=i+1;j<strlen(exp);j++){
                    if(exp[j]==';'){
                        printf("Duplicate token at line %ld",ret);
                    }
                }
            }
        }




    }

    return(0);
}

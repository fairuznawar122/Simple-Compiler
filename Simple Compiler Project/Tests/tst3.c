
#include <stdio.h>
#include <stdlib.h>
#define MAX 20


int main ()
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0,j=0,n=0;
    int c=2;


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

        for(i=0; i<strlen(exp); i++)
        {


            if(exp[i]=='f')
            {
                if(exp[i+1]=='o')
                {
                    if(exp[i+2]=='r')
                    {
                        if(exp[i+3]=='(')
                        {
                            j=i+3;
                            while(exp[j]!=')' && j<strlen(exp))
                            {
                                c=0;
                                if(exp[j]==';')
                                {
                                    c++;
                                    printf("%d",c);
                                    continue;
                                }
                                continue;
                            }
                            i=j;
                            continue;
                        }

                    }
                }
            }

            if(exp[i]==';')
            {
                j=i+1;
                while(exp[j]==';' && j<strlen(exp))
                {
                    j++;
                    n=1;
                    continue;
                }
                i=j;
            }
            else
            {
                continue;
            }
            if(n)
            {
                printf("\nDuplicate Token at line %ld\n",ret);
            }
            if(c<2)
            {
                printf("\nWrong in for %ld\n",ret);
            }
            n=0;
            c=2;

        }
    }

    return(0);
}

#include <stdio.h>
#include <stdlib.h>
#define MAX 20


int main ()
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0,j=0,n=0;
    int c=22;


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
                        if(exp[i+3]==' ')
                        {

                            if(exp[i+4]=='(')
                            {
                                j=i+4;
                                c=0;
                                for(j=i+4; j<strlen(exp); j++)
                                {

                                    if(exp[j]==')')
                                    {
                                        break;
                                    }
                                    if(exp[j]==';')
                                    {
                                        c++;
                                    }
                                }
                                if(c<2)
                                {
                                    printf("\nAt line number %ld: Expected \';\' inside for loop. ",ret);
                                }
                                i=j;
                                continue;
                            }

                        }

                    }
                }
            }

        }

    }
    fclose(f1);
    return(0);
}

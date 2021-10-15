
#include <stdlib.h>
#define MAX 20
#include   <stdio.h>

int main()
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0,j=0,n=0;

    FILE *f1;
    f1 = fopen("InputWithLine.txt","r");
    char *header= "include";
    printf("\n\nHeader Files : ");
    while(fgets(exp, 100, f1))
    {

        if(!strcmp(exp,"\n"))
        {
            continue;
        }

        strtok(exp, "\n");

        ret = strtol(exp, &ptr, 10);

        if(strstr(exp, header) != NULL)
        {
            for(i=0; i<strlen(exp); i++)
            {
                if(exp[i]=='<'){

                    for(j=i+1;j<strlen(exp);j++){
                        if(exp[j]!='>'){
                            printf("%c",exp[j]);
                        }
                        else{
                            printf(", ");
                            break;
                        }
                    }

                }
                else
                    continue;
            }


        }
    }
        fclose(f1);
        return 0;
    }

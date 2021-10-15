#include<stdio.h>
#include<string.h>



int main()
{
    FILE *kwf;
    char kw[100];
    char header[1000];
    strcpy(header," ");
    kwf = fopen("KeyWordsUsed.txt","r");
    while(fgets(kw, 100, kwf))
    {
        strtok(kw, "\n");
        if(strstr(header, kw) != NULL){
            continue;
        }
        else{
            strcat(header,kw);
             strcat(header,", ");

        }
    }
    printf("%s",header);



    fclose(kwf);
    return 0;
}

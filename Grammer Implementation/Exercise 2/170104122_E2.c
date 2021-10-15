/*INPUT FILE 
input.txt

(a+b)*(a-2)
(7+b)/(4-2)
a+6
a*7
b/3
(7+2)*b

*/


#include<stdio.h>
#include<string.h>

void Factor(void);
void Term(void);
void Exp(void);


int i=0,f=0,l;

char s[10];

void Term()
{
    Factor();
    if(f && i<l && (s[i]=='*' || s[i]=='/'))
    {
        i++;
        Factor();
    }

}

void Factor()
{
    if(i<l && s[i]=='(')
    {
        i++;
        f=1;
        Exp();
        if(f && s[i]==')')
            i++;
        else
            f=0;

    }

    else if(i<l && s[i]>='0' && s[i]<='9')
    {
        i++;
        f=1;
    }
    else if(i<l && s[i]>='a' && s[i]<='e')
    {
        i++;
        f=1;
    }
    else
        f=0;
}

void Exp()
{
    Term();
    if(f && i<l &&(s[i]=='+' || s[i]=='-'))
    {
        i++;
        Term();
    }

}

int main(void)
{
    printf("\nCFG:\n");
    printf("Exp -> Term+Term | Term-Term | Term \nTerm -> Factor*Factor | Factor/Factor | Factor \nID -> a|b|c|d|e \nNUM-> 0|1|2|...|9 \n\n\n");
    char c[100];
    FILE *p1,*p2;
    p2 = fopen("output.txt","w");
    if ((p1 = fopen("input.txt","r")) == NULL)
    {
        printf("File Not Found.");
        exit(1);
    }
    while(fscanf(p1,"%s",&s)>0)
    {
        i = 0;
        l = strlen(s);
        if (l>=1)
            Exp();
        else{
            fprintf(p2,"The String %s is Not Valid.\n",s);
            printf("The String %s is Not Valid.\n",s);
        }

        if (l == i && f ){
            fprintf(p2,"The String %s is Valid.\n",s);
            printf("The String %s is Valid.\n",s);
        }

        else{
            fprintf(p2,"The String %s is Not Valid.\n",s);
            printf("The String %s is Not Valid.\n",s);
        }

    }

    fclose(p1);
    fclose(p2);
    return 0;

}


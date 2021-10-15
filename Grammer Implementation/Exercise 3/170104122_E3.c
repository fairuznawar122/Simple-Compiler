/*INPUT FILE
input.txt

a=2
if(a+b)d=a+b
a=(a+3)>=1-2
if(e)
if(a+d)b
while(a+b)
while(1)
while(b)
while(a<b)


*/


#include<stdio.h>
#include<string.h>
#include <stdbool.h>

void Factor(void);
void Term(void);
void Exp(void);
void stat();

int f=0,i=0,l;
char s[100];

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
        {
            i++;
        }
        else
        {
            f=0;
        }

    }
    else if(i<l && s[i]>='a' && s[i]<='e')
    {
        i++;
        f=1;
    }
    else if(i<l && s[i]>='0' && s[i]<='9')
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


void extn()
{
    if(f && relop())
    {
        Exp();
    }
}


void expn()
{
    Exp();
    if(f)
    {
        extn();
    }
}

bool relop()
{
    if(f && i<l && (s[i]=='=' || s[i]=='!'))
    {
        i++;
        if(i<l && s[i]=='=')
        {
            i++;
            return true;
        }


        else
            return false;
    }
    else if(f && i<l && (s[i]=='<' || s[i]=='>'))
    {
        i++;
        if(i<l && s[i]=='=')
        {
            i++;
        }

        return true;
    }
    return false;
}


void extn1()
{
    if(f && i+3<l && s[i]=='e' && s[i+1]=='l' && s[i+2]=='s' && s[i+3]=='e')
    {
        i=i+4;
        stat();
    }
}


void dscn_stat()
{
    if(i+1<l && s[i]=='i' && s[i+1]=='f')
    {
        i=i+2;
        if(s[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && s[i]==')')
            {
                i++;
                stat();
                if(f)
                {
                    extn1();
                }
            }
            else
                f=0;
        }
        else
            f=0;
    }
}

void asgn_stat()
{
    if(i<l && 'a'<=s[i] && s[i]<='e')
    {
        i++;
        if(s[i]=='=')
        {
            i++;
            expn();
        }
    }
}


void loop_stat()
{
    if(i+4<l && s[i]=='w' && s[i+1]=='h' && s[i+2]=='i' && s[i+3]=='l' && s[i+4]=='e')
    {
        i=i+5;
        if(i<l && s[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && s[i]==')')
            {
                i++;
                stat();
            }
            else
                f=0;
        }
        else
            f=0;
    }

    else if(i+2<l && s[i]=='f' && s[i+1]=='o' && s[i+2]=='r')
    {
        i++;
        if(i<l && s[i]=='(')
        {
            i++;
            expn();
            i++;
            if(s[i]==';')
            {
                i++;
                expn();
                i++;
                if(s[i]==';')
                {
                    i++;
                    expn();
                    if(f && i<l && s[i]==')')
                    {
                        i++;
                        stat();
                    }
                }
            }
        }
        else
            f=0;

    }

}


void stat()
{
    asgn_stat();
    dscn_stat();
    loop_stat();
}

int main()
{
    printf("\nCFG:");
    printf("\n<stat> -> <asgn_stat> | <dscn_stat> | <loop_stat>");
    printf("\n<asgn_stat> -> id = <expn>");
    printf("\n<expn> -> <smpl_expn> <extn>");
    printf("\n<extn> -> <relop> <smpl_expn> | epsilon");
    printf("\n<dcsn_stat> -> if (<expn> ) <stat> <extn1>");
    printf("\n<extn1> -> else <stat> | epsilon");
    printf("\n<loop_stat> -> while (<expn>) <stat> | for (<asgn_stat> ; <expn> ; <asgn_stat> ) <stat>");
    printf("\n<relop> -> == | != | <= | >= | > | <\n\n");

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
        strtok(s, "\n");
        i = 0;
        l = strlen(s);
        if (l>=1)
        {
            stat();
        }
        else
        {
            fprintf(p2,"The String %s is Not Valid.\n",s);
            printf("The String %s is Not Valid.\n",s);
        }
        if (l == i && f )
        {
            fprintf(p2,"The String %s is Valid.\n",s);
            printf("The String %s is Valid.\n",s);
        }
        else
        {
            fprintf(p2,"The String %s is Not Valid.\n",s);
            printf("The String %s is Not Valid.\n",s);
        }
        strcpy(s,"");

    }

    fclose(p1);
    fclose(p2);
    return 0;
}

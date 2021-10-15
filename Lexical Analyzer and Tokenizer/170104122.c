#include<stdio.h>
#include<string.h>
#include <ctype.h>

char inS[];
char kwString[100];
char err[100]="";


int main()
{
    FILE *in,*out, *token;
    in = fopen("input.c","r");
    out = fopen("out.c","w");
    token = fopen("token.txt","w");
    fclose(token);

    char c,c1;

    //------------------------Breaking Into Lexemes using delimiter----------------------------//
    while((c=fgetc(in))!=EOF)
    {
        if(c=='<'||c=='>'||c=='=' ||c=='!' || c=='+' ||c=='-'||c=='*'||c=='/'||c=='|'||c=='&')
        {
            c1=c;
            c=fgetc(in);
            if(c=='='||c=='+'||c=='-'||c=='|'|| c=='&'||c=='<'||c=='>')
            {
                fputc(' ',out);
                fputc(c1,out);
                fputc(c,out);
                fputc(' ',out);
                continue;
            }
            else
            {
                fputc(' ',out);
                fputc(c1,out);
                fputc(' ',out);
            }
        }
        if(isalpha(c) || c=='_' || c==' ' || isdigit(c)|| c=='.')
        {

            fputc(c,out);
        }
        else
        {
            fputc(' ',out);
            fputc(c,out);
            fputc(' ',out);
        }
    }

    fclose(out);
    ClearWhiteSpace();

    //------------------------Reading Lexemes String By String----------------------------//
    out = fopen("out.c","r");
    int i = 0;
    int len=0;
    char x;

    while((x=fgetc(out))!=EOF)
    {

        if(x==' ')
        {
            len = i;
            if(len>0)
            {
                int foundOpSep = findOpSep();
                if(!foundOpSep)
                {
                    int foundKw = findKeywords();
                    if(!foundKw)
                    {
                        int foundNx= findNumericEx();

                        if(!foundNx)
                        {
                            int foundVar = findVariable();

                            if(!foundVar)
                            {
                                token = fopen("token.txt","a");
                                fprintf(token," [unkn %s] ",inS);
                                strcat(err, "Error : Unknown ");
                                strcat(err,inS);
                                fclose(token);
                            }

                        }
                    }
                }
            }

            i=0;
            len=0;
            strcpy(inS, "");
        }
        else
        {
            strncat(inS, &x, 1);
            i++;
        }

    }

    fclose(in);
    fclose(out);

    printf("----------------------------------------INPUT FILE------------------------------------\n\n");

    FILE *p;
    p=fopen("input.c","r");
    while((c=fgetc(p))!=EOF){
        printf("%c",c);
    }
    fclose(p);
    printf("\n\n--------------------------------------LEXEMS---------------------------------------\n\n");

    p=fopen("out.c","r");
    while((c=fgetc(p))!=EOF){
        printf("%c",c);
    }
    fclose(p);
    printf("\n\n---------------------------------------TOKENS---------------------------------------\n\n");

    p=fopen("token.txt","r");
    while((c=fgetc(p))!=EOF){
        printf("%c",c);
    }
    fclose(p);

    printf("\n\n--------------------------------------------------------------------------------\n\n");
    printf("\n\n%s.\n",err);
    return 0;
}


int findOpSep()
{
    FILE *token;
    token = fopen("token.txt","a");
    int i=0;
    if (inS[0]=='+' || inS[0]=='-' || inS[0]=='/' || inS[0]=='%' || inS[0]=='*' || inS[0]=='=' || inS[0]=='>'||inS[0]=='<' ||inS[0]=='&'||inS[0]=='!'||inS[0]=='|' ||inS[0]=='^')
    {
        fprintf(token," [op %s] ",inS);
        i=1;
    }
    else if(inS[0]=='(' ||inS[0]==')' ||inS[0]=='{' ||inS[0]=='}' ||inS[0]=='[' ||inS[0]==']')
    {
        i=1;
        fprintf(token," [par %s] ",inS);
    }
    else if (inS[0]==',' ||inS[0]==';' || inS[0]=='\'' ||inS[0]=='"' )
    {
        fprintf(token," [sep %s] ",inS);
        i=1;
    }
    fclose(token);
    return i;

}

int findNumericEx()
{
    FILE *token;
    token = fopen("token.txt","a");
    int s=0;
    int i=0,l;
    l=strlen(inS);
    if(isdigit(inS[0]))
    {
        s=1;
        i++;
    }
    else if(inS[0]=='.')
    {
        s=2;
        i++;
    }
    else
    {
        s=0;
    }

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(inS[i]))
            {
                s=1;
            }
            else if(inS[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==2)
    {
        if(isdigit(inS[i]))
        {
            s=3;
            i++;
        }
        else
        {
            s=0;
        }
    }
    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(inS[i]))
            {
                s=3;
            }
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==3)
    {
        s==1;
    }
    if(s)
    {
        fprintf(token," [num %s] ",inS);
    }

    fclose(token);
    return s;
}

int findVariable()
{
    FILE *token;
    token = fopen("token.txt","a");
    int i=0,s=0,l;
    l=strlen(inS);
    if(isalpha(inS[0]) || inS[0]=='_')
    {
        s=1;
        i++;
    }
    else
    {
        s=0;
    }
    if(s==1)
    {
        for(; i<l; i++)
        {
            if(inS[i]=='_' || isalnum(inS[i]))
            {
                s=1;
            }
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s)
    {
        fprintf(token," [id %s] ",inS);
    }

    fclose(token);
    return s;
}


int findKeywords()
{
    FILE *token;
    token = fopen("token.txt","a");
    int i=0;
    FILE *p1;
    p1 = fopen("Ckeywords.txt","r");

    while(fgets(kwString, 100, p1))
    {
        strtok(kwString, "\n");
        if(!strcmp(inS,kwString))
        {
            i=1;
            fprintf(token," [kw %s] ",inS);

        }
        else
        {
            continue;
        }
    }
    fclose(token);
    return i;
}


void ClearWhiteSpace()
{
    FILE *out;
    out=fopen("out.c","r");
    char code[5000],prevChar;
    int index=0;
    while((code[index++]=fgetc(out))!=EOF);
    fclose(out);

    out=fopen("out.c","w");
    int i;
    for(i=0; i<index-1; i++)
    {
        if(code[i]=='\n')
            continue;
        if(i==0)
        {
            prevChar=code[i];
            fputc(prevChar,out);
        }
        else
        {
            if(!(prevChar==' ' && code[i]==' '))
            {
                fputc(code[i],out);
            }
            prevChar=code[i];
        }
    }
    fclose(out);
}

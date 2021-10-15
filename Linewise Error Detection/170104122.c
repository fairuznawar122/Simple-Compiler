#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>
#include<stdbool.h>
#define MAX 20
char inS[];
char kwString[100];
char var[10];
int row=0;
struct HashTable
{
    char name[100],Id_type[100],data_type[20],scope[100],value[100];
} tableRow[100];

struct stack
{
    char stk[MAX];
    int top;
} s;

void push(char item)
{
    if (s.top == (MAX - 1))
        printf ("Stack is Full\n");
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = item;
    }
}

void pop()
{
    if (s.top == - 1)
    {
        printf ("Stack is Empty\n");
    }
    else
    {
        s.top = s.top - 1;
    }
}

void searchTable()
{
    int i;
    for(i=0; i<row; i++)
    {
        char s[20];
        strcpy(s,tableRow[i].data_type);
        if((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "double")) ||(!strcmp(s, "char"))||(!strcmp(s, "bool")))
        {
            continue;

        }
        else
        {
            printf("\nUndeclared Identifier %s\n",tableRow[i].name);
        }
    }
    int j,k;
    char s1[20],s2[20];
    for(i=0; i<row; i++)
    {

        strcpy(s1,tableRow[i].name);
        strcpy(s2,tableRow[i].scope);
        k=i;
        for(j=0; j<row; j++)
        {
            if(j==k)
            {
                continue;
            }
            if(!(strcmp(s1,tableRow[j].name)) && !(strcmp(s2,tableRow[j].scope)))
            {
                    printf("\nDuplicate Identifier %s\n",tableRow[i].name);
            }
        }

    }


    return;
}

void IdenfifierError(char s)
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0;
    int j;
    FILE *f1;
    f1 = fopen("IntermediateOutput.txt","r");
    int index;

    while(fgets(exp, 100, f1))
    {

        strtok(exp, "\n");
        ret = strtol(exp, &ptr, 10);
        printf("%s\n",exp);
        strcpy(var,"");
        for(i = 0; i<strlen(exp); i++)
        {

            if(exp[i]=='i')
            {
                if(exp[i+1]=='d')
                {
                    if(exp[i+2]==' ')
                    {
                        j=i+3;

                        while(exp[j]!=' ' && j<strlen(exp))
                        {
                            //printf("%c",exp[j]);
                            strncat(var, &exp[j], 1);
                            j++;
                        }
                        printf("%s\n",var);
                        i=j+1;

                        if(!strcmp(s,var))
                        {
                            printf("LIne %ld",ret);
                        }
                        strcpy(var,"");
                    }
                }
            }
            else
            {
                continue;
            }

        }

    }
    fclose(f1);



}



int Search(char* idname,char* scope)
{
    int i;
    for(i=0; i<row; i++)
    {
        if(!strcmp(tableRow[i].name,idname) && !strcmp(tableRow[i].scope,scope))
        {
            return i;
        }
    }
    return -1;
}


bool DataTypes(char* s)
{

    if((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "double")) ||(!strcmp(s, "char"))||(!strcmp(s, "bool")))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool FindValue(char* value)
{
    int x=0;
    int position=0;
    while(value[x]!='\0')
    {
        if(!(isdigit(value[x]) || value[x]=='.'))
        {
            return false;
        }
        if(value[x]=='.')
        {
            position++;
            if(position>1)
                return false;
        }
        x++;
    }
    return true;
}


void Insert()
{


    FILE *f1;
    f1 = fopen("tokenFINAL.txt", "r");
    char scope[10],Type[20],Name[100],Value[100];


    bool flag= false;
    char c,c1,c2,c3;
    int x=0;

    strcpy(scope,"global");


    while(fgetc(f1)!=EOF)
    {
        x=0;
        while((c=fgetc(f1))!=']')
        {
            Type[x++]=c;

        }
        Type[x]='\0';

        if(!DataTypes(Type))
        {

            if(!strcmp(Type,"}"))
            {
                strcpy(scope,"global");
            }
            if(Type[0]=='i' && Type[1]=='d')
            {
                flag=true;
            }
            else
            {
                continue;
            }

        }
        if(!flag)
        {
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);
            x=0;

            while((c=fgetc(f1))!=']')
            {
                Name[x++]=c;
            }
            Name[x]='\0';
        }
        else
        {

            x=3;

            while(Type[x]!='\0')
            {
                Name[x-3]=Type[x];
                x++;
            }
            Name[x-3]='\0';

        }

        fgetc(f1);
        c=fgetc(f1);

        if(!strcmp(Name,"main"))
        {
            strcpy(scope,"global");
        }
        if(c=='=')
        {
            fgetc(f1);
            fgetc(f1);

            x=0;

            while((c=fgetc(f1))!=']')
            {
                Value[x++]=c;
            }
            Value[x]='\0';
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);


            if(!FindValue(Value))
            {
                continue;
            }

            int NewRow= Search(Name,scope);

            if(NewRow==-1)
            {
                strcpy(tableRow[row].name,Name);
                strcpy(tableRow[row].Id_type,"var");
                strcpy(tableRow[row].data_type,Type);
                strcpy(tableRow[row].scope,scope);
                strcpy(tableRow[row].value,Value);
                row++;
            }
            else
            {
                strcpy(tableRow[NewRow].value,Value);
            }
        }


        else if(c=='(')
        {
            fgetc(f1);
            strcpy(tableRow[row].name,Name);
            strcpy(tableRow[row].Id_type,"func");
            strcpy(tableRow[row].data_type,Type);
            strcpy(tableRow[row].scope,scope);
            strcpy(tableRow[row].value,"");
            strcpy(scope,Name);
            row++;
        }
        else
        {
            if(!flag)
            {
                fgetc(f1);
                strcpy(tableRow[row].name,Name);
                strcpy(tableRow[row].Id_type,"var");
                strcpy(tableRow[row].data_type,Type);
                strcpy(tableRow[row].scope,scope);
                strcpy(tableRow[row].value,"");
                row++;
            }
        }
        flag=false;
    }
    fclose(f1);
}




void Display()
{
    FILE *f1;
    f1 = fopen("HashTableComplete.txt", "w");

    int i;
    printf("\nSerial \tName\tIdType \tDataType \tScope\tValue\n");
    fprintf(f1,"\nSL no\tName\tId Type\tDataType\tScope\tValue\n");
    printf("**********************************************************\n");
    fprintf(f1,"***********************************************************\n");

    for(i=0; i<row; i++)
    {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t\n",i+1,tableRow[i].name,tableRow[i].Id_type,tableRow[i].data_type,tableRow[i].scope,tableRow[i].value);
        fprintf(f1,"%d\t%s\t%s\t%s\t\t%s\t%s\t\n",i+1,tableRow[i].name,tableRow[i].Id_type,tableRow[i].data_type,tableRow[i].scope,tableRow[i].value);
    }
    fclose(f1);

}


void CheckIfElse()
{


    char exp[100];
    char *ptr;
    long ret;
    int i = 0;
    s.top = -1;

    strcpy(s.stk,"");


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

        for(i = 0; i<strlen(exp); i++)
        {
            if(exp[i]=='i')
            {
                if(exp[i+1]=='f')
                {
                    push(exp[i]);
                    i = i+1;
                    continue;
                }
            }
            else if(exp[i]=='e')
            {
                if(exp[i+1]=='l')
                {
                    if(exp[i+2]=='s')
                    {
                        if(exp[i+3]=='e')
                        {
                            if(s.stk[s.top] == 'i')
                            {
                                pop();
                            }
                            else
                            {
                                printf("\nUnmatched \'else\' at line %ld\n",ret);
                                break;
                            }
                            i=i+3;
                        }
                    }
                }
            }
            else
            {
                continue;
            }


        }

    }
    fclose(f1);
}

void CheckDuplicateSep()
{

    char exp[100];
    char *ptr;
    long ret;
    int i = 0,j=0,n=0;

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

                        j=i+2;
                        while(exp[j]!=')' && j<strlen(exp))
                        {
                            j++;
                            continue;
                        }
                        i=j;
                        continue;
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
            n=0;

        }
    }
    fclose(f1);
}

void ParanthesisProblem()
{
    char exp[100];
    char *ptr;
    long ret;
    int i = 0;
    s.top = -1;

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

        for(i = 0; i<strlen(exp); i++)
        {
            if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            {
                push(exp[i]);
                continue;
            }
            else if(exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
            {
                if(exp[i] == ')')
                {
                    if(s.stk[s.top] == '(')
                    {
                        pop();
                    }
                    else
                    {
                        printf("\nUnbalanced \')\' at line %ld\n",ret);
                        break;
                    }
                }
                if(exp[i] == ']')
                {
                    if(s.stk[s.top] == '[')
                    {
                        pop();
                    }
                    else
                    {
                        printf("\nUnbalanced \']\' at line %ld\n\n");
                        break;
                    }
                }
                if(exp[i] == '}')
                {
                    if(s.stk[s.top] == '{')
                    {
                        pop();
                    }
                    else
                    {
                        printf("\nUnbalanced \'}\' at line %ld\n",ret);
                        break;
                    }
                }
            }
            else
            {
                continue;
            }
        }


    }
    fclose(f1);
}

int findOpSepImmediateOutput()
{
    FILE *token, *token2;
    token = fopen("token.txt","a");
    token2 = fopen("token2.txt","a");
    int i=0;
    if (inS[0]=='+' || inS[0]=='-' || inS[0]=='/' || inS[0]=='%' || inS[0]=='*' || inS[0]=='=' || inS[0]=='>'||inS[0]=='<' ||inS[0]=='&'||inS[0]=='!'||inS[0]=='|' ||inS[0]=='^')
    {
        fprintf(token,"%s",inS);
        fprintf(token2,"[%s]",inS);
        i=1;
    }
    else if(inS[0]=='(' ||inS[0]==')' ||inS[0]=='{' ||inS[0]=='}' ||inS[0]=='[' ||inS[0]==']')
    {
        i=1;
        fprintf(token,"%s",inS);
        fprintf(token2,"[%s]",inS);
    }
    else if (inS[0]==',' ||inS[0]==';' || inS[0]=='\'' ||inS[0]=='"' )
    {
        fprintf(token,"%s",inS);
        fprintf(token2,"[%s]",inS);
        i=1;
    }
    fclose(token2);
    fclose(token);
    return i;

}

int findNumericExImmediateOutput()
{
    FILE *token, *token2;
    token = fopen("token.txt","a");
    token2 = fopen("token2.txt","a");
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
        fprintf(token,"%s",inS);
        fprintf(token2,"[%s]",inS);
    }

    fclose(token);
    fclose(token2);
    return s;

}

int findVariableImmediateOutput()
{
    FILE *token, *token2;
    token = fopen("token.txt","a");
    token2 = fopen("token2.txt","a");
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
        fprintf(token," id %s ",inS);
        fprintf(token2,"[%s]",inS);
    }

    fclose(token);
    fclose(token2);
    return s;
}


int findKeywordsImmediateOutput()
{
    FILE *token, *token2;
    token = fopen("token.txt","a");
    token2 = fopen("token2.txt","a");
    int i=0;
    FILE *p1;
    p1 = fopen("Ckeywords.txt","r");

    while(fgets(kwString, 100, p1))
    {
        strtok(kwString, "\n");
        if(!strcmp(inS,kwString))
        {
            i=1;
            fprintf(token,"%s ",inS);
            fprintf(token2,"[%s]",inS);

        }
        else
        {
            continue;
        }
    }
    fclose(token);
    fclose(token2);
    return i;
}




void filter()
{
    FILE *in, *out;
    char x,x1,c;
    in = fopen("in.c","r");
    out = fopen("filter1.txt","w");


    fclose(in);
    in = fopen("in.c","r");


    while((x = fgetc(in))!=EOF)
    {

        if(x=='\n' || x=='\t')
        {
            continue;

        }
        if(x==' ')
        {

            x1=fgetc(in);

            if(x1==' ' || x1=='\n')
            {
                continue;
            }
            else if(x1=='/')
            {
                x=x1;
            }
            else
            {
                fputc(x,out);

                x=x1;
            }

        }

        if(x=='/')
        {
            x1= fgetc(in);
            if(x1=='/')
            {
                while((x1=fgetc(in))!=EOF)
                {
                    if(x1=='\n')
                    {
                        break;
                    }
                }
                continue;
            }
            else if(x1=='*')
            {
                while((x=fgetc(in))!=EOF)
                {
                    if(x=='*')
                    {
                        x=fgetc(in);
                        if(x=='/')
                            break;
                    }
                }
                continue;
            }

        }
        if(x=='"')
        {
            fputc(x,out);

            while((x1=fgetc(in))!=EOF )
            {

                fputc(x1,out);
                if(x1=='"')
                {
                    break;
                }

            }


        }
        else
        {
            fputc(x,out);
        }

    }

    fclose(in);
    fclose(out);
    printf("\n\n");



}

int findOpSep()
{
    FILE *token;
    token = fopen("token.txt","a");
    int i=0;
    if (inS[0]=='+' || inS[0]=='-' || inS[0]=='/' || inS[0]=='%' || inS[0]=='*' || inS[0]=='=' || inS[0]=='>'||inS[0]=='<' ||inS[0]=='&'||inS[0]=='!'||inS[0]=='|' ||inS[0]=='^')
    {
        fprintf(token,"[%s]",inS);
        i=1;
    }
    else if(inS[0]=='(' ||inS[0]==')' ||inS[0]=='{' ||inS[0]=='}' ||inS[0]=='[' ||inS[0]==']')
    {
        i=1;
        fprintf(token,"[%s]",inS);
    }
    else if (inS[0]==',' ||inS[0]==';' || inS[0]=='\'' ||inS[0]=='"' )
    {
        fprintf(token,"[%s]",inS);
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
        fprintf(token,"[%s]",inS);
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
        fprintf(token,"[id %s]",inS);
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
            fprintf(token,"[%s]",inS);

        }
        else
        {
            continue;
        }
    }
    fclose(token);
    return i;
}



void filterforIntermidiateOutput()
{

    FILE *in, *out;
    char x,x1,c;
    in = fopen("in.c","r");
    out = fopen("filterIO.txt","w");

    /*printf("Input Code: \n");

    while((c = fgetc(in))!=EOF)
    {
        printf("%c",c);
    }*/
    fclose(in);
    in = fopen("in.c","r");
    //printf("\n\n\nOutput Code: \n\n");

    while((x = fgetc(in))!=EOF)
    {

        if(x=='\n' || x=='\t')
        {
            if(x=='\n')
            {
                fputc(x,out);
            }
            continue;

        }
        if(x==' ')
        {

            x1=fgetc(in);

            if(x1==' ' || x1=='\n')
            {
                continue;
            }
            else if(x1=='/')
            {
                x=x1;
            }
            else
            {
                fputc(x,out);
                //printf("%c",x);
                x=x1;
            }

        }

        if(x=='/')
        {
            x1= fgetc(in);
            if(x1=='/')
            {
                while((x1=fgetc(in))!=EOF)
                {
                    if(x1=='\n')
                    {
                        break;
                    }
                }
                continue;
            }
            else if(x1=='*')
            {
                while((x=fgetc(in))!=EOF)
                {
                    if(x=='*')
                    {
                        x=fgetc(in);
                        if(x=='/')
                            break;
                    }
                }
                continue;
            }

        }
        if(x=='"')
        {
            fputc(x,out);
            //printf("%c",x);
            while((x1=fgetc(in))!=EOF )
            {
                //printf("%c",x1);
                fputc(x1,out);
                if(x1=='"')
                {
                    break;
                }

            }


        }
        else
        {
            fputc(x,out);
            // printf("%c",x);
        }

    }

    fclose(in);
    fclose(out);
    //printf("\n\n");

    FILE *token, *token2;
    in = fopen("filterIO.txt","r");
    out = fopen("out.c","w");
    token = fopen("token.txt","w");
    token2= fopen("token2.txt","w");
    fclose(token);
    fclose(token2);

    char c1;

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
    //ClearWhiteSpace();

    //------------------------Reading Lexemes String By String----------------------------//
    out = fopen("out.c","r");
    int i = 0;
    int len=0;

    while((x=fgetc(out))!=EOF)
    {

        if(x==' ')
        {

            len = i;
            if(len>0)
            {
                int foundOpSep = findOpSepImmediateOutput();

                if(!foundOpSep)
                {
                    int foundKw = findKeywordsImmediateOutput();

                    if(!foundKw)
                    {
                        int foundNx= findNumericExImmediateOutput();


                        if(!foundNx)
                        {
                            int foundVar = findVariableImmediateOutput();
                            if (x=='\n')
                            {
                                token = fopen("token.txt","a");
                                fprintf(token,"\n%s",inS);
                                fclose(token);
                                token2 = fopen("token2.txt","a");
                                fprintf(token2,"[%s]",inS);
                                fclose(token2);
                                continue;
                            }

                            if(!foundVar)
                            {
                                token = fopen("token.txt","a");
                                fprintf(token," %s",inS);
                                fclose(token);
                                token2 = fopen("token2.txt","a");
                                fprintf(token2,"[%s]",inS);
                                fclose(token2);


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


    fclose(out);

}


void AddLineNo()
{
    FILE *p1, *p2;
    int count=1;
    char x;
    int newline=1;
    p1 = fopen("token.txt", "r");
    p2 = fopen("IntermediateOutput.txt","w");

    while((x = fgetc(p1))!= EOF)
    {
        if(newline)
        {
            fprintf(p2, "%d",count);
            fputc(':', p2);
            newline=0;
        }
        fputc(x, p2);
        if (x=='\n')
        {
            count++;
            fputc('\n', p2);
            fprintf(p2, "%d",count);
            fputc(':', p2);
        }
    }
    fclose(p1);
    fclose(p2);
}



void Tokenize(FILE *out)
{

    FILE *token;
    token = fopen("token.txt","w");
    fclose(token);
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
                                fprintf(token,"[%s]",inS);

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
    fclose(out);
}
void ClearWhiteSpace()
{
    FILE *out;
    out=fopen("filter2.txt","r");
    char code[5000],prevChar;
    int index=0;
    while((code[index++]=fgetc(out))!=EOF);
    fclose(out);

    out=fopen("filter3.txt","w");
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

void filter2(FILE *in)
{

    FILE *out, *token;
    out = fopen("filter2.txt","w");

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

}

int main()
{
/////////////////////For Generating Symbol Table//////////////////////////////////
    filter();
    FILE *in;
    in = fopen("filter1.txt","r");
    filter2(in);
    fclose(in);
    ClearWhiteSpace();
    in = fopen("filter3.txt","r");
    Tokenize(in);
    fclose(in);

    FILE *p, *q;
    char c;
    p=fopen("token.txt","r");
    q=fopen("tokenFINAL.txt","w");
    while((c=fgetc(p))!=EOF)
    {
        fputc(c,q);
    }
    fclose(p);
    fclose(q);
//////////////////////////For Generating Intermediate Output/////////////////////////////
    printf("Intermediate Output : \n");
     printf("\n-----------------------------------\n");
    filterforIntermidiateOutput();
    AddLineNo();
    FILE *m;
    m=fopen("IntermediateOutput.txt","r");
    while((c=fgetc(m))!=EOF)
    {
        printf("%c",c);
    }
    fclose(m);
    printf("\n-----------------------------------\n\n");
/////////////////////////Error Checking /////////////////////////////////
      printf("Errors : \n");

    ParanthesisProblem();
    CheckIfElse();
    CheckDuplicateSep();

    Insert();
    //Display();
    //IdenfifierError();
    searchTable();


    return 0;
}

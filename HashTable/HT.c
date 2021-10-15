#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int row=0;


struct HashTable {
    char name[100],Id_type[100],data_type[100],scope[100],value[100];
}tableRow[100];


int Search(char* idname,char* scope) {
    int i;
    for(i=0;i<row;i++) {
        if(!strcmp(tableRow[i].name,idname) && !strcmp(tableRow[i].scope,scope)) {
            return i;
        }
    }
    return -1;
}


bool DataTypes(char* s) {

    if((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "double")) ||(!strcmp(s, "char"))||(!strcmp(s, "bool"))){
        return true;
    }
    else{
        return false;
    }
}


bool FindValue(char* value) {
    int x=0;
    int position=0;
    while(value[x]!='\0') {
        if(!(isdigit(value[x]) || value[x]=='.'))
        {
                return false;
        }
        if(value[x]=='.') {
            position++;
            if(position>1) return false;
        }
        x++;
    }
    return true;
}


void Insert() {


    FILE *f1,*f2;
    f1 = fopen("TokenFilterStep1.txt", "r");
    char scope[10],Type[20],Name[100],Value[100];


    bool flag= false;
    char c,c1,c2,c3;
    int x=0;

    strcpy(scope,"global");


    while(fgetc(f1)!=EOF) {
        x=0;
        while((c=fgetc(f1))!=']') {
            Type[x++]=c;

        }
        Type[x]='\0';

        if(!DataTypes(Type)) {

            if(!strcmp(Type,"}")){
                strcpy(scope,"global");
            }
            if(Type[0]=='i' && Type[1]=='d') {
                flag=true;
            }
            else {
                continue;
            }

        }
        if(!flag) {
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);
            x=0;

            while((c=fgetc(f1))!=']') {
                Name[x++]=c;
            }
            Name[x]='\0';
        }
        else {

            x=3;

            while(Type[x]!='\0') {
                Name[x-3]=Type[x];
                x++;
            }
            Name[x-3]='\0';

        }

        fgetc(f1);
        c=fgetc(f1);

        if(!strcmp(Name,"main")){
           strcpy(scope,"global");
        }
        if(c=='=') {
            fgetc(f1);
            fgetc(f1);

            x=0;

            while((c=fgetc(f1))!=']') {
                Value[x++]=c;
            }
            Value[x]='\0';
            fgetc(f1);
            fgetc(f1);
            fgetc(f1);


            if(!FindValue(Value)){
                continue;
            }

            int NewRow= Search(Name,scope);

            if(NewRow==-1) {
                strcpy(tableRow[row].name,Name);
                strcpy(tableRow[row].Id_type,"var");
                strcpy(tableRow[row].data_type,Type);
                strcpy(tableRow[row].scope,scope);
                strcpy(tableRow[row].value,Value);
                row++;
            }
            else {
                strcpy(tableRow[NewRow].value,Value);
            }
        }


        else if(c=='(') {
            fgetc(f1);
            strcpy(tableRow[row].name,Name);
            strcpy(tableRow[row].Id_type,"func");
            strcpy(tableRow[row].data_type,Type);
            strcpy(tableRow[row].scope,scope);
            strcpy(tableRow[row].value,"");
            strcpy(scope,Name);
            row++;
        }
        else {
            if(!flag) {
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




void Display() {
    FILE *f1;
    f1 = fopen("HashTableComplete.txt", "w");

    int i;
    printf("\nSerial \tName\tIdType \tDataType \tScope\tValue\n");
    fprintf(f1,"\nSL no\tName\tId Type\tDataType\tScope\tValue\n");
    printf("**********************************************************\n");
    fprintf(f1,"***********************************************************\n");

    for(i=0;i<row;i++) {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t\n",i+1,tableRow[i].name,tableRow[i].Id_type,tableRow[i].data_type,tableRow[i].scope,tableRow[i].value);
        fprintf(f1,"%d\t%s\t%s\t%s\t\t%s\t%s\t\n",i+1,tableRow[i].name,tableRow[i].Id_type,tableRow[i].data_type,tableRow[i].scope,tableRow[i].value);
    }
    fclose(f1);

}

int main() {

    FILE *p1, *p2;
    char c;
    int i;
    TokenFilterStep1();

    printf("Step 1 : \n\n");
    p1 = fopen("TokenFilterStep1.txt", "r");
    while((c=fgetc(p1))!=EOF){
        printf("%c",c);
    }
    fclose(p1);
    Insert();
    printf("\n\n\nHASH TABLE : \n");
    Display();




    /*
    p2 = fopen("Step4.txt", "w");
    char var[10];
    while((c=fgetc(p1))!=EOF){
        if(c=='i'){

            fputc(c,p2);
            if((c=fgetc(p1))=='d'){
                fputc(c,p2);
                if(c=fgetc(p1)==' '){

                      fputc(c,p2);
                    while((c=fgetc(p1))!=' '){
                          strncat(var, &c, 1);
                    }

                    for(i=0;i<row;i++){
                        if(!strcmp(var,tableRow[i].name)){
                            fputc(i,p2);
                            break;
                        }
                    }
                    printf("%s",var);
                      strcpy(var,"");


                }
                else{
                    fputc(c,p2);
                }
            }
            else{
                fputc(c,p2);
                continue;
            }
        }
        else{
            fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);*/

    return 0;
}

void TokenFilterStep1(){
    char c,c1,c2;
    FILE *p1, *p2;
    p1 = fopen("input.c", "r");
    p2 = fopen("TokenFilterStep1.txt", "w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='[')
        {
            fputc(c,p2);
            c1=fgetc(p1);
            c2=fgetc(p1);
            if(c1=='i' && c2=='d')
            {
                fputc(c1,p2);fputc(c2,p2);
                while((c=fgetc(p1))!=']')
                {
                    fputc(c,p2);
                }
                fputc(c,p2);
            }
            else
            {
                while((c=fgetc(p1))!=' '){}
                while((c=fgetc(p1))!=']')
                {
                    fputc(c,p2);
                }
                fputc(c,p2);
            }
        }
    }
    fclose(p1);
    fclose(p2);

}



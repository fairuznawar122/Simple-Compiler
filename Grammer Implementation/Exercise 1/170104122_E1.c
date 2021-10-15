/* Input File

input.txt
ad
abbd
abbbbd
abcd
abcbbd

*/

#include<stdio.h>
#include<string.h>
char s[30];
int len,i=0,f=0;

void A()
{
    if(s[i] == 'a')
    {
        i++;
        X();
        if(f==1)
        {
            if(s[i-1] == 'd')
                f = 1;
            else
                 f = 0;

            return;
        }
    }
}

void X()
{
    if(len-1 == i)
    {
        i++;
        f = 1;
        return;
    }
    else
    {
        if(s[i] == 'b')
        {
            i++;
            if(s[i] == 'b' || s[i] == 'c')
            {
                i++;
                X();

            }
        }
        else
        {
            f = 0;
            return;
        }
    }
}

int main(void)
{
   printf("CFG: \n");
    printf("A -> aXd\nX -> bbX | bcX | epsilon\n\n\n");

   char c[100];
   FILE *p1,*p2;
   p2 = fopen("output.txt","w");
   if ((p1 = fopen("input.txt","r")) == NULL){
       printf("File Not Found.");
       exit(1);
   }
   while(fscanf(p1,"%s",&s)>0)
   {
        i = 0;
        len = strlen(s);
        if(len>=1)
            {
                A();
            }
        else{
            fprintf(p2,"The String %s is Not Valid.\n",s);
            printf("The String %s is Not Valid.\n",s);
        }

        if(len == i && f == 1){
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


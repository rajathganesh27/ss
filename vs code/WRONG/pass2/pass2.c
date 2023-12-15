#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EXIT_FAILURE 1
int o=-1,s=-1;
FILE *f1,*f2,*f3,*f4,*f5,*f6;
char label[20],opcode[20],operand[20],staddr[20],address[20];
char t1[20],t2[20],t3[20],t4[20];
char ad[20],a[20];
int i,j;
char length[20],size[20];
struct symtab
{
    char label[10];
    char addr[10];
}st[30];

struct optab
{
    char opcode[10];
    char hexcode[10];
}ot[30];

void read_OPTAB()
{
    while(1)
    {
        o++;
        fscanf(f3,"%s%s",ot[o].opcode,ot[o].hexcode);
        if(getc(f3)==EOF)
        {
            break;
        }
    }
}

void read_SYMTAB()
{
    while(1)
    {
        s++;
        fscanf(f2,"%s%s",st[s].label,st[s].addr);
        if(getc(f2)==EOF)
        {
            break;
        }
    }
}

void readLine()
{
    strcpy(t1,"");
    strcpy(t2,"");
    strcpy(t3,"");
    strcpy(t4,"");

    fscanf(f1,"%s",t1);
    fscanf(f1,"%s",t2);
    fscanf(f1,"%s",t3);
    fscanf(f1,"%s",t4);

    if(strcmp(t1,"**")!=0)
    {
        strcpy(address,t1);
    }
    else
    {
        strcpy(address,"");
    }
    if(strcmp(t2,"**")!=0)
    {
        strcpy(label,t2);
    }
    else
    {
        strcpy(label,"");
    }

    if(strcmp(t3,"**")!=0)
    {
        strcpy(opcode,t3);
    }
    else
    {
        strcpy(opcode,"");
    }


    if(strcmp(t4,"**")!=0)
    {
        strcpy(operand,t4);
    }
    else
    {
        strcpy(operand,"");
    }

}

int main()

{
    // int length,size;

    
    f1=fopen("intermediate.txt","r");
    f2=fopen("symtab.txt","r");
    f3=fopen("optab.txt","r");
    f4=fopen("length.txt","r");

    f5=fopen("output.txt","w");
    f6=fopen("objcode.txt","w");

    if (!f1 || !f2 || !f3 || !f4 || !f5 || !f6)
    {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    fscanf(f4,"%s",length);
    fscanf(f4,"%s",size);

    read_OPTAB();
    read_SYMTAB();

    fscanf(f1,"%s%s%s",label,opcode,operand);
    strcpy(staddr,operand);

    if(strcmp(opcode,"START")==0)
    {
        fprintf(f5,"\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(f6,"H^%s^00%s^0000%s\n",label,operand,length);
        fprintf(f6,"T^00%s^%s",operand,size);
        readLine();
    }

    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(opcode,"BYTE")==0)
        {
            
            fprintf(f5,"%s\t%s\t%s\t%s\t",address,label,opcode,operand);
            sprintf(ad,"%X",operand[2]);

            //long int intad = strtol(ad, NULL, 16);
            // printf("OBJECT CODE====%s",intad);

            fprintf(f5,"%s\n",ad);
            // printf("OBJECT CODE====%s",operand[2]);
            fprintf(f6,"^%s",ad);
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            sprintf(a,"%X",atoi(operand));
            fprintf(f5,"%s\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
            fprintf(f6,"^00000%s",a);
        }
        // else if ((strcmp(opcode, "RESB") == 0) || (strcmp(opcode, "RESW") == 0))
        //     fprintf(f5, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);

        else
        {
            i=0;
            while(strcmp(opcode,ot[i].opcode)!=0 && i<30)
            {
                i++;
            }

            j=0;
            while(strcmp(operand,st[j].label)!=0 && j<30)
            {
                j++;
            }
            // printf("%s\t%s\t%s\t%s\t%s%s\n",address,label,opcode,operand,ot[i].hexcode,st[j].addr);
            
            fprintf(f5,"%s\t%s\t%s\t%s\t%s%s\n",address,label,opcode,operand,ot[i].hexcode,st[j].addr);
            fprintf(f6,"^%s%s",ot[i].hexcode,st[j].addr);

        }
        readLine();
    }

    fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
    fprintf(f6,"\nE^00%s",staddr);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
    printf("SUCCESS");
    return 0;
    



}
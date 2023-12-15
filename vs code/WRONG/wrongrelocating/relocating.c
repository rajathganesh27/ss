#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char bit[30];
int main()
{

  
    char rec[20],name[20],bitmask[20],second[20],first[20];
    int addr,start,len,bitmask_index,i,mod_obj_code;
    printf("ENter the starting address:\n");
    scanf("%d",&start);
    addr=start;

    FILE *f1,*f2;
    f1=fopen("input.txt","r");
    fscanf(f1,"%s",rec);


    if(strcmp (rec,"H")==0)
    {
        fscanf(f1,"%s",name);
        fscanf(f1,"%X",&addr);
        fscanf(f1,"%X",&len);

        printf("\nPROGRAM NAME =%s\n\n",name);

        printf("ADDRESS\t OBJECT CODE\n");

        printf("-----------------\n");
    }

    else
    {
        printf("INVALID CODE FORMAT\n");
        fclose(f1);
        exit(1);
    }


    strcpy(rec,"");

    fscanf(f1,"%s",rec);

    while(strcmp(rec,"E")!=0)
    {
        
        if(strcmp(rec,"T")==0)
        {
            fscanf(f1,"%d",&addr);
            fscanf(f1,"%d",&len);
            fscanf(f1,"%s",bitmask);

            // printf("%d\n",addr);
            // printf("%d\n",start);
            addr=addr+start;
            // printf("%d\n",start);
            // printf("%d\n",addr);
            bitmask_index=0;
            
            strcpy(bit, "");
            for(i=0;i<strlen(bitmask);i++)
            {
                
                switch(bitmask[i])
                {
                    case '0': strcat(bit,"0000");
                        break;
                    case '1': strcat(bit,"0001");
                        break;
                    case '2': strcat(bit,"0010");
                        break;
                    case '3': strcat(bit,"0011");
                        break;
                    case '4': strcat(bit,"0100");
                        break;
                    case '5': strcat(bit,"0101");
                        break;
                    case '6': strcat(bit,"0110");
                        break;
                    case '7': strcat(bit,"0111");
                        break;
                    case '8': strcat(bit,"1000");
                        break;
                    case '9': strcat(bit,"1001");
                        break;
                    case 'A': strcat(bit,"1010");
                        break;
                    case 'B': strcat(bit,"1011");
                        break;
                    case 'C': strcat(bit,"1100");
                        break;
            
                    case 'D': strcat(bit,"1101");
                        break;
                    case 'E': strcat(bit,"1110");
                        break;

                    case 'F': strcat(bit,"1111");
                        break;
                        

                    default : break;


                }



            }

            printf("%s\n",bit);
            fscanf(f1,"%s",rec);

        }
        if(bit[bitmask_index] =='1')
            {
                for(i=0;i<6;i++)
                {
                    if(i<2)
                    {
                        first[i]=rec[i];
                    }
                    else
                    {
                        second[i-2]=rec[i];
                    }
                }
                first[2]='\0';
                second[4]='\0';

                // mod_obj_code=strtol(second,NULL,16);
                mod_obj_code=atoi(second);
                mod_obj_code=mod_obj_code+start;
                printf("%d\t%s%d\n",addr,first,mod_obj_code);



            }
            else
            {
                printf("%d\t%s\n",addr,rec);
            }

            addr+=3;
            bitmask_index++;
            fscanf(f1,"%s",rec);
       

        
    }
    


        fclose(f1);
        return 0;









}
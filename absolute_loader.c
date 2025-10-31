#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fin,*fout;
    char line[50],ch,add[90];
    int i,j,loc,n;
    fin=fopen("co.txt","r");
    fout=fopen("ab.txt","w");
    while (fscanf(fin,"%s",line)!=EOF)
    {
       if(line[0]=='T')
        {
            for(i=1,j=0;i<7;i++,j++)
            {
                 add[j]=line[i];

            }
            loc=strtol(add,NULL,16);
            n=strlen(line);
            i=9;
            while(line[i]!='\0')
            {
                fprintf(fout,"%04X %c%c\n",loc,line[i],line[i+1]);
                loc=loc+1;
                i+=2;
            }
        }

        else
        {
            fscanf(fin,"\n");
        }
    }
    
    fclose(fin);
    fclose(fout);

}
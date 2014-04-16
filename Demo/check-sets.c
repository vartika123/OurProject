#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


char T[4][8]={"4210848","4212896","4214944","4216992"};

void main()
{
	char buff[10];
        int set[4][256],i,j,k=0;
        //4 look up tables
        for(i=0;i<4;i++)
        {

                for(j=0;j<256;j++)
                {
                        sprintf(buff,"%x",(atoi(T[i])+j*8));
                        set[i][j]=setNumber(buff);

                 }

        }
	printf("Sets of lookup table indices\n");
	for(i=0;i<4;i++)
        {
		printf("\nTable %d\n",i);
                for(j=0;j<256;j++)
                {
			
			printf("%d\t",set[i][j]);                         

                        }
		printf("\n");
         }

}



int setNumber(char hexaDecimal[7])
{
char binaryNumber[24],modifiedBinary[12],ch;
    int i,j,blen,len,temp;
    long int num,rem,set=0,power=0;

    len=strlen(hexaDecimal);
    blen=len*4;
    binaryNumber[blen]='\0';
    i=len;
    while(i>0)
    {
        i--;
        ch=hexaDecimal[i];
        if(ch>=48 && ch <=57)
            temp=ch-48;
        else
       {
               temp=ch-55;
        }
        for(j=0;j<4;j++)
        {
             binaryNumber[--blen]=(temp%2)+48;
             temp/=2;
        }
     }
        for(i=6,j=0;i<18;i++,j++)
                modifiedBinary[j]=binaryNumber[i];
     modifiedBinary[12]='\0';
     num=atoi(modifiedBinary);

     for(i=0;i<12;i++)
     {
                rem = num%10;
                 num = num/10;
                set = set + rem * pow(2,power);
                 power++;
        }
return set;
 }


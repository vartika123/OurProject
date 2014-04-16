#include<stdio.h>
#include<time.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}

char T[4][8]={"4210848","4212896","4214944","4216992"};
int plaintext[16]={0x67,0x89,0x65,0x43,0x12,0x34,0x56,0x78,0x95,0x43,0x23,0x45,0x45,0x67,0x87,0x2F};
int cachedset[4][4]={{262,267,268,283},{296,299,313,314},{324,326,328,354},{359,362,363,369}};


int uncachedIndices[4][256]={-1};
int cyc[4][4]={0};
int rejectedKeyBits[16][256]={-1};
int uncachedIndicesLength[4]={-1};
int possibleKeySet[16][256]={-1};
FILE *fp,*fp1;


void attack()
{
	int latest[16][256];
	int result,val;
	char buff[10];
	int set[4][256],i,j,k=0;
	//4 look up tables
	for(i=0;i<4;i++)
	{
		k=0;
		for(j=0;j<256;j++)
		{
			sprintf(buff,"%x",(atoi(T[i])+j*8));
			set[i][j]=setNumber(buff);
			result = setSearch(i,set[i][j]);
			if(!result)
			{
			     	uncachedIndices[i][k]=j;
			        k++;
			}
			
		}
		uncachedIndicesLength[i]=k;
	}
	
	for(i=0;i<16;i++)
	{	
		for(j=0;j<uncachedIndicesLength[i%4];j++)
		{
			rejectedKeyBits[i][j]=uncachedIndices[i%4][j]^plaintext[i];
		}
	}	

	for(i=0;i<16;i++)
	{
		for(j=0;j<uncachedIndicesLength[i%4];j++)
		{
        		result=rejectedKeyBits[i][j];
		        possibleKeySet[i][result]=-1;
		}
	}

	for(i=0;i<16;i++)
	{
		for(j=0;j<256;j++)
		{
			fprintf(fp,"%d\t",possibleKeySet[i][j]);
		}
		fprintf(fp,"\n\n");
	}

	fclose(fp);

}


int main(int argc, char **argv)
{
	fp=fopen(argv[1],"w+");
        char a[4194305];
	char buff[100];
        int i,j,k,m,n,count,l,increment=0,h=0;
        double start,end;
	int flag=0;

//Generate all possible key values
	for(i=0;i<16;i++)
	{
		for(j=0;j<256;j++)
		{
		possibleKeySet[i][j]=j;
		}
	}

	attack();
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

int setSearch(int tableNumber, int setNumber)
{
   int first, last, middle;
   first = 0;
   last = 3;
   middle = (first+last)/2;
 
   while( first <= last )
   {
      if ( setNumber < cachedset[tableNumber][middle] )
         last = middle - 1;    
      else if ( cachedset[tableNumber][middle] == setNumber) 
      {
         return 1;
      }
      else
         first = middle + 1;
 
      middle = (first + last)/2;
   }
   return 0;   
}


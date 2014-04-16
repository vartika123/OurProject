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
		cyc[i] = 6000;

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
		
         		   if((l>=258)&&(l<=386)&&(!(l==310||l==379||l==300||l==308||l==338||l==367||l==309||l==281||l==294||l==261||l==264||l==274||l==277||l==295||l==298||l==304||l==306||l==313||l==271||l==276||l==284||l==307||l==322||l==352||l==386||l==339||l==345||l==346||l==351||l==353||l==364||l==371||l==375||l==297)))
			   {
				   if((cycles-cyc[l])>=250)
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

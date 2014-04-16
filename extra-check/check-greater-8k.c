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
//	for(i=0;i<4096;i++)
//		cyc[i] = 8000;

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
		
         		   if(l==313||l==324 ||l==369||l==333||l==267||l==283||l==291||l==299||l==303||l==258||l==266||l==270||l==272||l==275||l==278||l==285||l==286||l==287||l==288||l==292||l==301||l==302||l==325||l==326||l==328||l==361||l==362||l==368||l==384||l==262||l==263||l==265||l==268||l==269||l==273||l==280||l==282||l==289||l==290||l==296||l==305||l==311||l==312||l==314||l==315||l==316||l==323||l==335||l==344||l==349||l==350||l==354||l==357||l==358||l==359||l==363||l==366||l==373||l==378||l==381)
			   {
				
				   if(cycles>7000)
				{
					
					fprintf(fp,"%d: %llu\t",l,cycles);
					//cyc[l]= cycles;
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

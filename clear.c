#include<stdio.h>
#include<stdlib.h>

int main()
{
        int i,j;
        const int size = 20*1024*1024; // Allocate 20M. Set much larger then L2$

        char *c = (char *)malloc(size);

                for(j = 0; j < size; j++)
                        c[j] = j;

}


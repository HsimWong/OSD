#include<stdio.h>
#include<stdlib.h>
#include<ctime>
int main()
{
	// srand((unsigned)time(0));
       for(int i=0;i<10;i++)
             printf("%.9f\n",(double)rand() * rand()/RAND_MAX);
}


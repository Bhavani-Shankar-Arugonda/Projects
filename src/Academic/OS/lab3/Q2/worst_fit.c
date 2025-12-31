#include<stdio.h>

void allocate(int* a , int n)
{
	int x = -1;
	for(int i = 0;i < 5;i++)
	{
		if(n <= a[i])
		{
			if(x == -1)
				x = i;
			else
			{
				if(a[x] < a[i])
					x = i;
			}
		}
	}
	if(x == -1)
		printf("Not allocated\n");
	else
	{
		a[x] -= n;
		printf("Allocated as %d\n" , x+1);
	}
}

void main()
{
	int memory[5] = {300 , 500 , 100 , 350 , 150};
	int n;
	printf("Enter memory needed for the proccess\nEnter -1 to exist :");
	scanf("%d",&n);
	while(n != -1)
	{
		allocate(memory,n);
		printf("Enter memory needed for the proccess\nEnter -1 to exist :");
		scanf("%d",&n);
	}
}

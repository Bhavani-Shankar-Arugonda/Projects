#include<stdio.h>
int main()
{
	int n;
	printf("Enter number of array elements: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter array elements: ");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	int max = a[0];

	for(int i = 1; i < n; i++)
	{
		if(a[i] > max)
		{
			max = a[i];
		}
	}

	int count[max + 1];

	for(int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		count[a[i]]++;
	}

	for(int i = 0; i <= max; i++)
	{
		while(count[i] > 0)
		{
			printf("%d ", i);
			count[i]--;
		}
	}

}

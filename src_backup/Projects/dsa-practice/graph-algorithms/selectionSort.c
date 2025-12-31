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

	for(int i = 0; i < n - 1; i++)
	{
		int min = a[i];
		int ind = -1;
		int j;
		for(j = i + 1; j < n; j++)
		{
			if(a[j] < min)
			{
				min = a[j];
				ind = j;
			}
		}
		int temp = a[i];
		a[i] = min;
		a[ind] = temp;
	}

	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}


}

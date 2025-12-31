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
		int j = i;
		while(a[j] > a[j + 1] && j >= 0)
		{
			int temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
			j--;
		}
	}
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}

}

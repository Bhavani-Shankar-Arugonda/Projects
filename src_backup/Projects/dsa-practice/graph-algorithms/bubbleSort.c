#include<stdio.h>
int main()
{
	int n;
	printf("Enter array size: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter array elements: ");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n - i - 1; j++)
		{
			if(a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}

}


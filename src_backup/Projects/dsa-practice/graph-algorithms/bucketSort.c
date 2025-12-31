#include<stdio.h>
void bucketSort(int, int []);
void insertionSort(int, int []);
int main()
{
	int n;
	printf("Enter number of array elementsL: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter array elements: ");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	bucketSort(n, a);

	printf("sorted elements:");
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}	
}
void insertionSort(int n, int a[])
{
	for(int i = 0; i < n; i++)
	{
		int j = i;
		while(j > 0 && a[j - 1] > a[j])
		{
			int t = a[j - 1];
			a[j - 1] = a[j];
			a[j] = t;
			j--;
		}
	}
}
void bucketSort(int n, int l[])
{
	int max = l[0];
	for(int i = 1; i < n; i++)
	{
		if(l[i] > max)
		{
			max = l[i];
		}
	}

	int m = (max / 10) + 1;

	int arr[m][n];
	int count[n];
	for(int i = 0; i < n; i++)
	{
		count[i] = 0;
	}
	for(int i = 0; i < n; i++)
	{
		int x = l[i] / 10;
		arr[x][count[x]] = l[i];
		count[x]++;
	}
	for(int i = 0; i < n; i++)
	{
		insertionSort(count[i], arr[i]);
	}
	int k = 0;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < count[i]; j++)
		{
			l[k] = arr[i][j];
			k++;
		}
	}
}

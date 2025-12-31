#include<stdio.h>
void quickSort(int [], int , int );
int getPivotIndex(int [], int , int );
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

	printf("hi");

	quickSort(a, 0, n - 1);

	printf("Sorted array is: ");
	for(int i = 0; i < n; i++)
	{
		printf("%d", a[i]);
	}
}
void quickSort(int a[], int low, int high)
{
	int pivotIndex;
	while(low < high)
	{
		//printf("hi");
		pivotIndex = getPivotIndex(a, low, high);
		quickSort(a, low, pivotIndex - 1);
		quickSort(a, pivotIndex + 1, high);
	}
}
int getPivotIndex(int a[], int left, int right)
{
	int pivote = a[left];
	int i = left + 1;
	int j = right;
	while(i <= j)
	{
		while(a[i] < pivote && i <= right)
		{
			i++;
		}
		while(a[j] > pivote && j >= left)
		{
			j--;
		}
		if(i <= j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	a[left] = a[j];
	a[j] = pivote;
	return j;
}

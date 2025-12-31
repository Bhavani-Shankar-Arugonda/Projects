#include<stdio.h>
void quickSort(int [], int, int);
int getCorrectIndex(int [], int, int);
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

	quickSort(a, 0, n - 1);

	printf("Sorted array is: ");
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}
void quickSort(int a[], int low, int high)
{
	if(low < high)
	{
		int pivot = getCorrectIndex(a, low, high);
		quickSort(a, low, pivot - 1);
		quickSort(a, pivot + 1, high);
	}
}
int getCorrectIndex(int a[], int l, int r)
{
	int piv = l;
	while(l < r)
	{
		while(a[l] <= a[piv])
		{
			l++;
		}
		while(a[r] > a[piv])
		{
			r--;
		}
		if(l < r)
		{
			int temp = a[l];
			a[l] = a[r];
			a[r] = temp;
		}
	}
	int temp = a[piv];
	a[piv] = a[r];
	a[r] = temp;
	return r;
}

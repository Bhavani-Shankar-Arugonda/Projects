#include<stdio.h>
void mergeSort(int [], int, int);
void merge(int [], int, int, int);
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
	mergeSort(a, 0, n - 1);

	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}
void mergeSort(int a[], int l, int r)
{
	if(l < r)
	{
		int mid = (l + r) / 2;

		mergeSort(a, l, mid);
		mergeSort(a, mid + 1, r);

		merge(a, l, mid, r);
	}
}
void merge(int a[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1];
	int R[n2];

	for(int i = 0; i < n1; i++)
	{
		L[i] = a[l + i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = a[m + 1 + j];
	}

	int i = 0, j = 0, k = l;

	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1)
	{
		a[k] = L[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		a[k] = R[j];
		j++;
		k++;
	}
}


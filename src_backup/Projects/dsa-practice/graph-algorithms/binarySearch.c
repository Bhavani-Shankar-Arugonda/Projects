#include<stdio.h>
int main()
{
	int n;
	printf("Enter number of elements in array: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter array elements in ascending order: ");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	int key;
	printf("Enter a key to be searched: ");
	scanf("%d", &key);

	int l = 0;
	int r = n - 1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(a[mid] == key)
		{
			printf("Key found at index %d", mid);
			return 0;
		}
		if(a[mid] > key)
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("Key not found!");


}

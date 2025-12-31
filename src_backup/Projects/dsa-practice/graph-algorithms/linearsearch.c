#include<stdio.h>
int main()
{
	int n;
	printf("Enter number of elements of the array: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter array elements: ");

	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	int key;
	printf("Enter key to be searched: ");
	scanf("%d", &key);
	int found = 0;
	int ind = -1;
	for(int i = 0;i < n; i++)
	{
		if(key == a[i])
		{
			found = 1;
			ind = i;
			break;
		}
	}
	if(found == 1)
	{
		printf("Key found at index %d", ind);
	}
	else
	{
		printf("Key not found!");
	}

}

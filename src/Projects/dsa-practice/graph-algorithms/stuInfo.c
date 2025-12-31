#include<stdio.h>
struct student
{
	char name[50];
	int rNo;
	int marks;
	float cgpa;
};
typedef struct student student;
int main()
{
	int n;
	printf("Enter number of students:");
	scanf("%d", &n);

	student a[n];

	for(int i = 0; i < n; i++)
	{
		printf("Enter student %d details: \n", (i + 1));

		printf("Enter student name: ");
		scanf("%s", a[i].name);

		printf("Enter roll number: ");
		scanf("%d", &a[i].rNo);

		printf("Enter marks: ");
		scanf("%d", &a[i].marks);

		printf("Enter cgpa: ");
		scanf("%f", &a[i].cgpa);
	}

	for(int i = 0; i < n; i++)
	{
		printf("Student %d details are: \n", (i + 1));

		printf("Student name: ");
		printf("%s\n", a[i].name);

		printf("Roll number: ");
		printf("%d\n", a[i].rNo);

		printf("Marks: ");
		printf("%d\n", a[i].marks);

		printf("cgpa: ");
		printf("%f\n", a[i].cgpa);
		
	}
	
	int key;
	printf("Enter roll number to be searched: ");
	scanf("%d", &key);
	
	printf("using linear search\n");
	for(int i = 0; i < n; i++)
	{
		if(key == a[i].rNo)
		{
			printf("%s %d %d %f\n", a[i].name, a[i].rNo, a[i].marks, a[i].cgpa);
			break;
		}
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n - i - 1; j++)
		{
			if(a[j].rNo > a[j + 1].rNo)
			{
				int temp = a[j].rNo;
				a[j].rNo = a[j + 1].rNo;
				a[j + 1].rNo = temp;
			}
		}
	}

	/*for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i].rNo);
	}*/
	
	printf("using binary search\n");
	int l = 0;
	int r = n - 1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(a[mid].rNo == key)
		{
			printf("name is %s roll number is %d marks are %d cgpa is %f", a[mid].name, a[mid].rNo, a[mid].marks, a[mid].cgpa);
			return 0;
		}
		if(a[mid].rNo > key)
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

#include<stdio.h>
#include<ctype.h>
#define MAX 5
int main()
{
	int a[MAX];
	char choice;
	printf("Enqueue?(E) or Dequeue?(D) or Stop?(S)");
	scanf(" %c", &choice);
	int rear = -1;
	while(toupper(choice) != 'S')
	{
		switch(choice)
		{
			case 'E':
				if(rear == MAX - 1)
				{
					printf("Queue is full!");
				}
				else
				{
					rear++;
					printf("Enter element to be queued: ");
					scanf("%d", &a[rear]);
				}
				break;
			case 'D':
				if(rear == -1)
				{
					printf("No elements!");
				}
				else
				{
					printf("%d", a[0]);
					for(int i = 0; i <= rear; i++)
					{
						a[i] = a[i + 1];
					}
					rear--;
				}
				break;
			default:
				printf("Enter valid choice!");
				break;
		}
		printf("Queue?(E) or Dequeue?(D) or Stop?(S)");
		scanf(" %c", &choice);
	}
	printf("Queue is: ");
	for(int i = 0; i <= rear; i++)
	{
		printf("%d -> ", a[i]);
	}
	printf("NULL");
}

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct node
{
	int data;
	struct node *link;
};
typedef struct node node;
int main()
{
	node *head = NULL;
	node *tail = NULL;

	char choice;
	printf("Enqueue?(E) or Dequeue?(D) or Stop?(S)");
	scanf(" %c", &choice);
	while(toupper(choice) != 'S')
	{
		switch(choice)
		{
			case 'E':
				
				node *newNode = malloc(sizeof(node));
				printf("Enter element to be queued: ");
				scanf("%d", &newNode -> data);
				

				newNode -> link = NULL;		
				if(head == NULL)
				{
					head = newNode;
					tail = newNode;	
				}
				else
				{
					tail -> link = newNode;
					tail = newNode;
				}	
				break;
			case 'D':
				if(head == NULL)
				{
					printf("No elements!");
				}
				else
				{
					printf("Dequeued element is %d", head -> data);
					head = head -> link;
				}
				break;
			default:
				printf("Enter valid choice!");
				break;
		}
		printf("Enqueue?(E) or Dequeue?(D) or Stop?(S)");
		scanf(" %c", &choice);
	}
	printf("Queue is: ");
	while(head != NULL)
	{
		printf("%d -> ", head -> data);
		head = head -> link;
	}	
	printf("NULL");


}

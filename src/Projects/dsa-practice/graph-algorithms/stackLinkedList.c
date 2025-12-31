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
	node *curptr = head;

	int choice;
	printf("Push?(1) or Pop(2)? or Stop(0)?\n");
	scanf("%d", &choice);

	while(choice != 0)
	{
		switch(choice)
		{
			case 1:
				curptr = malloc(sizeof(node));
				printf("Enter element to be pushed: ");
				scanf("%d", &curptr -> data);
				curptr -> link = head;
				head = curptr;
				break;
			case 2:
				if(head == NULL)
				{
					printf("Stack is empty!\n");
				}
				else
				{
					printf("Popped element is %d\n", head -> data);
					head = head -> link;
				}
				break;
			default:
				printf("Enter valid choice!\n");
				break;
		}
		printf("Push?(1) or Pop(2)? or Stop(0)?\n");
		scanf("%d", &choice);
	}
	while(head != NULL)
	{
		printf("%d -> ", head -> data);
		head = head -> link;
	}
	printf("NULL");
}

#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int data;
	struct node *link;
};
typedef struct node node;
void addAtBegin(node **, node **);
void addAtEnd(node **);
void addAtLoc(node **);
void delAtBegin(node **);
void delAtEnd(node **);
void delAtLoc(node **);
int main()
{
	node *head = NULL;
	node *curptr = head;
	int choice;
	printf("Add at beginning?(1) or Add at end?(2) or Add at a particular location?(3) or Delete at beginning?(4) or Delete at end?(5) or Delete at a particular location?(6) or Exit(-1)\n");
	scanf("%d", &choice);
	while(choice != -1)
	{
		switch(choice)
		{
			case 1:
				addAtBegin(&head, &curptr);
				break;
			case 2:
				addAtEnd(&curptr);
				break;
			case 3:
				addAtLoc(&head);
				break;
			case 4:
				delAtBegin(&head);
				break;
			case 5:
				delAtEnd(&head);
				break;
			case 6:
				delAtLoc(&head);
				break;
			default:
				printf("Enter valid choice!");
				break;
		}
		printf("Add at beginning?(1) or Add at end?(2) or Add at a particular location?(3) or Delete at beginning?(4) or Delete at end?(5) or Delete at a particular location?(6) or Exit(-1)\n");
		scanf("%d", &choice);
	}
	while(head != NULL)
	{
		printf("%d -> ", head -> data);
		head = head -> link;
	}	
	printf("NULL");
}
void addAtBegin(node **head, node **curptr)
{
	node *newNode = malloc(sizeof(node));
	printf("Enter element to be added: ");
	scanf("%d", &newNode -> data);
	if(*head == NULL)
	{
		*head = *curptr = newNode;
		newNode -> link = NULL;
	}
	else
	{
		newNode -> link = *head;
		*head = newNode;
	}
}
void addAtEnd(node **curptr)
{
	node *newNode = malloc(sizeof(node));
	printf("Enter element to be added: ");
	scanf("%d", &newNode -> data);
	(*curptr) -> link = newNode;
	*curptr = newNode;
	newNode -> link = NULL;
}
void addAtLoc(node **head)
{
	int n;
	node *newNode = malloc(sizeof(node));
	printf("Enter where to be added and element to be added: ");
	scanf("%d%d", &n, &newNode -> data);
	node *temp = *head;
	for(int i = 1; i < n - 1; i++)
	{
		temp = temp -> link;
	}
	newNode -> link = temp -> link;
	temp -> link = newNode;
}
void delAtBegin(node **head)
{
	*head = (*head) -> link;
}
void delAtEnd(node **head)
{
	node *temp = *head;
	while(temp -> link -> link != NULL)
	{
		temp = temp -> link;
	}
	//node *temp2 = temp -> link;
	temp -> link = NULL;
	//free(temp2);
}
void delAtLoc(node **head)
{
	int n;
	printf("Enter location to be deleted: ");
	scanf("%d", &n);
	node *temp = *head;
	for(int i = 1; i < n - 1; i++)
	{
		temp = temp -> link;
	}
	temp -> link = temp -> link -> link;
}

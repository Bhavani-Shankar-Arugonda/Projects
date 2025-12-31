#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int data;
	struct node *link;
};
typedef struct node node;
void addAtBegin(node **, node **);
void addAtEnd(node **, node **);
void addAtLoc(node **);
void delAtBegin(node **, node **);
void delAtEnd(node **, node **);
void delAtLoc(node **);
void display(node **, node **);
int main()
{
	node *head = NULL;
	node *curptr = head;
	int choice;
	printf("Add at beginning?(1) or Add at end?(2) or Add at a particular location?(3) or Delete at beginning?(4) or Delete at end?(5) or Delete at a particular location?(6) or Display?(7) or Exit(-1)\n");
	scanf("%d", &choice);
	while(choice != -1)
	{
		switch(choice)
		{
			case 1:
				addAtBegin(&head, &curptr);
				break;
			case 2:
				addAtEnd(&curptr, &head);
				break;
			case 3:
				addAtLoc(&head);
				break;
			case 4:
				delAtBegin(&head, &curptr);
				break;
			case 5:
				delAtEnd(&head, &curptr);
				break;
			case 6:
				delAtLoc(&head);
				break;
			case 7:
				display(&head, &curptr);
				break;
			default:
				printf("Enter valid choice!");
				break;
		}
		printf("Add at beginning?(1) or Add at end?(2) or Add at a particular location?(3) or Delete at beginning?(4) or Delete at end?(5) or Delete at a particular location?(6) or Display?(7) or Exit(-1)\n");
		scanf("%d", &choice);
	}
	/*while(head != NULL)
	{
		printf("%d -> ", head -> data);
		head = head -> link;
	}	
	printf("NULL");*/
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
		(*curptr) -> link = newNode;
	}
}
void addAtEnd(node **curptr,node **head)
{
	node *newNode = malloc(sizeof(node));
	printf("Enter element to be added: ");
	scanf("%d", &newNode -> data);
	(*curptr) -> link = newNode;
	*curptr = newNode;
	newNode -> link = *head;
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
void delAtBegin(node **head, node **curptr)
{
	*head = (*head) -> link;
	(*curptr) -> link = *head;
}
void delAtEnd(node **head, node **curptr)
{
	node *temp = *head;
	while(temp -> link -> link != *head)
	{
		temp = temp -> link;
	}
	//node *temp2 = temp -> link;
	temp -> link = *head;
	*curptr = temp;
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
void display(node **head, node **curptr)
{
	node *temp3 = *head;
	while(temp3 != *curptr)
	{
		printf("%d -> ", temp3 -> data);
		temp3 = temp3 -> link;
	}	
	printf("%d ->", (*curptr) -> data);
	printf("HEAD");

}

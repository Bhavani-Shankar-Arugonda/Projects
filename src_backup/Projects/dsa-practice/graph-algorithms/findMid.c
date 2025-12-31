#include<stdio.h>
#include<stdlib.h>
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
	printf("Enter element?(1) or Stop?(2)");
	scanf("%d", &choice);
	while(choice != 2)
	{
		node *newNode = malloc(sizeof(node));
		printf("Enter element to be added: ");
		scanf("%d", &newNode -> data);
		if(head == NULL)
		{
			head = curptr = newNode;
			newNode -> link = NULL;
		}
		else
		{
			newNode -> link = head;
			head = newNode;
		}
		printf("Enter element?(1) or Stop?(2)");
		scanf("%d", &choice);

	}
	int opt;
	printf("approach 1?(1) or approach 2?(2)");
	scanf("%d", &opt);
	switch(opt)
	{
		case 1:
			node *fp = head;
			node *sp = head;
			while(fp -> link != NULL && fp -> link -> link != NULL)
			{
				sp = sp -> link;
				fp = fp -> link -> link;
			}
			printf("Middle element is %d", sp -> data);
			break;
		case 2:
			int i = 0;
			node *temp = head;
			while(temp != NULL)
			{
				temp = temp -> link;
				i++;
			}
			int p = i / 2;
			for(int i = 1; i <= p; i++)
			{
				head = head -> link;
			}
			printf("Middle element is %d", head -> data);
			break;


	}
}

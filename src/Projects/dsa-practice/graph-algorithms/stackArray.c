#include<stdio.h>
#define SIZE 15
int stack[SIZE];
int top = -1;
int main()
{
	int choice;
	printf("Push?(1) or Pop(2)? or Stop(0)?\n");
	scanf("%d", &choice);

	while(choice != 0)
	{
		switch(choice)
		{
			case 1:
				if(top == SIZE - 1)
				{
					printf("Stack is full!\n");
				}
				else
				{
					top++;
					printf("Enter element to be added: ");
					scanf("%d", &stack[top]);
				}
				break;
			case 2:
				if(top == -1)
				{
					printf("Stack is empty!\n");
				}
				else
				{
					printf("Popped element is %d\n", stack[top]);
					top--;
				}
				break;
			default:
				printf("Enter valid choice!\n");
				break;
		}
		printf("Push?(1) or Pop(2)? or Stop(0)?\n");
		scanf("%d", &choice);
	}

	for(int i = top; i >= 0; i--)
	{
		printf("%d -> ", stack[i]);
	}
	printf("NULL");
}

#include<stdio.h>
#include<stdlib.h>
struct node
{
	char data;
	struct node *link;
};

int main()
{
	char name[30];
	printf("Enter name: ");
	scanf("%s", name);

	char stack[30];
	int top = -1;
	
	int i = 0;
	while(name[i] != '\0')
	{
		top++;
		stack[top] = name[i];
		i++;
	}
	//printf("%d", top);
	int pal = 1;
	for(int i = 0; i <= top; i++)
	{
		//printf("hi");
		if(stack[top] != name[i])
		{
			//printf("%c", stack[top]);
			pal = 0;
		}
		top--;
	}
	if(pal == 1)
	{
		printf("Its a palindrome!");
	}
	else
	{
		printf("Ites not a palindrome!");
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
int stack[MAX];
int top = -1;

void push(int value)
{
	if(top < (MAX - 1))
	{
		stack[++top] = value;
	}
	else
	{
		printf("stack overflow!");
	}
}
int pop()
{
	if(top >=0)
	{
		return stack[top--];
	}
	else
	{
		printf("stack underflow\n");
		exit(1);
	}
}
int evalpost(char *expression)
{
	int i = 0;
	int ope1, ope2, result;
	while(expression[i] != '\0')
	{
		if(isdigit(expression[i]))
		{
			push(expression[i] - '0');
		}
		else
		{
			ope1 = pop();
			ope2 = pop();

			switch(expression[i])
			{
				case '+':
					result = ope1 + ope2;
					break;
				case '-':
					result = ope2 - ope1;
					break;
				case '*':
					result = ope1 * ope2;
					break;
				case '/':
					result = ope2 / ope1;
					break;
				default:
					printf("INVALID OPERATOR!");
					break;
			}
			push(result);
		}
		i++;
	}
	return pop();
}
int main()
{
	char expression[MAX];
	printf("Enter postfix expression: ");
	scanf("%s", expression);
	printf("Final result is : %d", evalpost(expression));
}

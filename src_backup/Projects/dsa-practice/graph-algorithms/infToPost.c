#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int prec(char);
struct stack
{
	int top;
	char arr[];
};
typedef struct stack stack;
int main()
{
	char input[MAX];
	printf("Enter infix expression: ");
	scanf("%s", input);

	stack operator;
	operator.top = -1;
	operator.arr[MAX];

	char postfix[MAX];

	int i = 0, j = 0;
	while(input[i] != '\0')
	{
		if(input[i] == '(')
		{
			operator.top++;
			operator.arr[operator.top] = input[i];
			i++;
		}
		else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			if(prec(input[i]) > prec(operator.arr[operator.top]))
			{
				operator.top++;
				operator.arr[operator.top] = input[i];
				i++;
			}
			else
			{
				postfix[j] = operator.arr[operator.top];
				operator.arr[operator.top] = input[i];
				j++;
				i++;
			}
		}
		else if(input[i] == ')')
		{
			while(operator.arr[operator.top] != '(')
			{
				postfix[j] = operator.arr[operator.top];
				j++;
				operator.top--;
			}
			i++;
		}
		else
		{
			postfix[j] = input[i];
			i++;
			j++;
		}
	}
	while(operator.top != -1)
	{
		postfix[j] = operator.arr[operator.top];
		operator.top--;
		j++;
	}
	postfix[j] = '\0';
	int l = 0;
	while(postfix[l] != '\0' && postfix[l] != '(')
	{
		printf("%c", postfix[l]);
		l++;
	}
}
int prec(char val)
{
	if(val == '*' || val == '/')
	{
		return 2;
	}
	else if(val == '+' || val == '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


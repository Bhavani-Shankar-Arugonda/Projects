#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 100

typedef struct
{
        char stack[maxsize];
        int top;
}stack;

void push(stack *s, char c)
{
        if(s->top == maxsize-1)
        {
                printf("Stack overflow");
                exit(1);
        }
        s->stack[++(s->top)]=c;
}

char pop(stack* s)
{
        if(s->top==-1)
        {
                printf("stack underflow");
                exit(1);
        }
        return s->stack[(s->top)--];
}


void parenthesis(char *exp)
{
        stack s;
        s.top=-1;
        int len = strlen(exp);

        for(int i=0; i<len; i++)
        {
                char token= exp[i];

                if(token == '(' || token == '{' || token == '[')
                {
                        push(&s,token);
                }
                else if(token ==')' || token=='}' || token==']')
                {
                        if(s.top==-1)
                        {
                                printf("Not Balanced");
                                return;
                        }
                        char popped = pop(&s);
                        if((token == ')' && popped !='(')||(token == '}' && popped !='{')||(token == ']' && popped !='['))
                        {
                                printf("Not Balanced");
                                return;
                        }
                }
        }
        if(s.top==-1)
        {
                printf("Balanced");
        }
        else
        {
                printf("Not Balanced");
        }
}

int main()
{
    FILE *file=fopen("input.txt","r");

    if(file==NULL)
    {
        printf("unable to open file\n");
        return 0;
    }

    int count=0;
    while(fgetc(file)!=EOF)
    {
        count++;
    }

    char *arr = (char *)malloc(count*sizeof(char));

    rewind(file);

    char a;
    int i=0;
    while((a=fgetc(file))!=EOF)
    {
        arr[i++]=a;
    }

        parenthesis(arr);
        return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int availableframes = 3;
int referencestring[] = {7, 0, 1, 2, 0, 3, 0, 4,2, 3, 0, 3};
int queue[10];
int front = 0;
int rear = 0;
void enqueue(int i)
{
    queue[front] = i;
    front = front + 1;
    if(front == availableframes)
        front = 0;
}
void printarr()
{
    for(int i =0;i<availableframes;i++)
    {
        printf("%d ",queue[i]);
    }
    printf("\n");
}
bool pagealreadypresentornot(int k)
{
    for(int i =0;i<availableframes;i++)
    {
        if(k == queue[i])
            return true;
    }
    return false;
}    
bool freespacepresentornot()
{
    for(int i =0;i<availableframes;i++)
    {
        if(queue[i] == -1)
            return true;
    }
    return false;
}
void dequeue()
{
    queue[rear] = 1;
    rear = rear +1 ;
    if(rear == availableframes)
        rear = 0;
}
void fifopro(int n)
{
    int c = 0;
    for(int i =0;i<availableframes;i++)
    {
        queue[i] = -1;
    }
    int pagefaultcount = 0;
    for(int i =0;i<n;i++)
    {
        if(!pagealreadypresentornot(referencestring[i]))
        {
            if(freespacepresentornot())
            {
                enqueue(referencestring[i]);
            }
            else
            {
                dequeue();
                enqueue(referencestring[i]);
            }
            pagefaultcount++;
        }
        printarr();
    }
     printf("No of Page Faults = %d",pagefaultcount);
}
int main()
{
    fifopro(12);
}
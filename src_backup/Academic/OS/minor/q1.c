#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int availableframes = 3;
int referencestring[] = {0, 1, 2, 0, 3, 4, 1, 0,3, 2, 4, 5, 1, 2, 3};
int referencestring1[] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1};
int referencestring2[] = {2,5,7,4,6,9,1,0,3,6,4,7,8,3,6,3,9};
int queue[20];
int front = 0;
int rear = 0;
void enqueue(int i)
{
    queue[front] = i;
    front = front + 1;
    if(front == availableframes)
    {
        front = 0;
    }
}
void dequeue()
{
    queue[rear] = -1;
    rear = rear + 1;
    if(rear == availableframes)
    {
        rear = 0;
    }
}
bool checkifpagepresentinstackornot(int k)
{
    for(int i = 0;i<availableframes;i++)
    {
        if(k == queue[i])
        {
            return true;
        }
    }
    return false;
}
void printqueue()
{
    for(int i =0;i<availableframes;i++)
    {
        printf("Index %d->%d ",i,queue[i]);

    }
    printf("\n");
}
bool freespacepresentornot()
{
    for(int i = 0;i<availableframes;i++)
    {
        if(queue[i] == -1)
        {
            return true;
        }
    }
    return false;
}
void pagereplacementfifo(int *rs,int n)
{
    for(int i =0;i<availableframes;i++)
    {
        queue[i] = -1;
    }
    int pagefaultcount = 0;
    for(int i = 0;i<n;i++)
    {
        if(checkifpagepresentinstackornot(rs[i]) == false)
        {
            if(freespacepresentornot() == true)
            {
                enqueue(rs[i]);
            }
            else
            {
                dequeue();
                enqueue(rs[i]);
            }
            pagefaultcount++;
        }
        //printqueue();
        
    }
    printf("In FIFO Total Page Faults = %d\n",pagefaultcount);
}
int delta = 2;
int calcworkingset(int t,int rs[])
{
    int count;
    int workingset[100];
    for(int i =0;i<100;i++)
    {
        workingset[i] = -1;
    }
    int flag = 1;
    int r = 0;
    for(int i = t-1;i>delta-1;i--)
    {
        flag = 1;
        for(int j =0;j<100;j++)
        {
            if(rs[i] == workingset[j])
            {
                flag = 0;
            }
        }
        if(flag == 1)
        {
            workingset[r++] = rs[i];
        }
    }
    return r;
}
void checkthrashing(int t)
{
    printf("Assuming Delta to be %d\n",delta);
    printf("At time T = %d\n",t);
    int a = calcworkingset(t,referencestring);
    printf("Working Set for Process 1 = %d\n",a);
    int b = calcworkingset(t,referencestring1);
    printf("Working Set for Process 2 = %d\n",b);
    int c = calcworkingset(t,referencestring2);
    printf("Working Set for Process 3 = %d\n",c);
    if(a+b+c>availableframes)
    {
        printf("Thrashing\n");
    }
    else
    {
        printf("No Thrashing\n");
    }
}
int main()
{
    printf("Assuming for every Index in The Reference String The time in incremented by 1\n");
    printf("Available Frames is %d\n",availableframes);
    checkthrashing(4);
    checkthrashing(6);
    checkthrashing(11);
    printf("Process 1 ");
    pagereplacementfifo(referencestring, sizeof(referencestring)/sizeof(referencestring[0]));
    front = rear = 0;
    printf("Process 2 ");
    pagereplacementfifo(referencestring1, sizeof(referencestring1)/sizeof(referencestring1[0]));
    front = rear = 0;
    printf("Process 3 ");
    pagereplacementfifo(referencestring2, sizeof(referencestring2)/sizeof(referencestring2[0]));
}
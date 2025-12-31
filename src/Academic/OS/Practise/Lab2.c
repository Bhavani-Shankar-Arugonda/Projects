#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

void fcfs(int arrival_time[],int burst_time[],int k)
{
    int pid[k];
    for(int i=0;i<k;i++)
    {
        pid[i]=i+1;
    }

    for(int i=0;i<k-1;i++)
    {
        for(int j=0;j<k-1-i;j++)
        {
            if(arrival_time[j]>arrival_time[j+1])
            {
                int temp=arrival_time[j];
                arrival_time[j]=arrival_time[j+1];
                arrival_time[j+1]=temp;

                temp=burst_time[j];
                burst_time[j]=burst_time[j+1];
                burst_time[j+1]=temp;

                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
            }
        }
    }

    for(int i=0;i<k;i++)
    {
        printf("%d %d\n",pid[i],arrival_time[i]);
    }
}


void sjf(int arrival_time[],int burst_time[],int k)
{
    int pid[k];
    for(int i=0;i<k;i++)
    {
        pid[i]=i+1;
    }

    bool executed[k];
    for(int i=0;i<k;i++)
    {
        executed[i]=false;
    }

    int min=arrival_time[0];
    int min_index=0;
    for(int i=1;i<k;i++)
    {
        if(arrival_time[i]<min)
        {
            min=arrival_time[i];
            min_index=i;
        }
    }

    executed[min_index]=true;
    int time =arrival_time[min_index];

    int z=1;
    while(z<k)
    {
        int Min;
        int shortest_index;
        for(int i=0;i<k;i++)
        {
            if(!executed[i])
            {
                Min=burst_time[i];
                shortest_index=i;
                break;
            }
        }

        for(int i=0;i<k;i++)
        {
            if(!executed[i] && arrival_time[i]<=time && burst_time[i]<Min)
            {
                Min=burst_time[i];
                shortest_index=i;
            }
        }

        time+=burst_time[shortest_index];
        executed[shortest_index]=true;
        printf("%d ",shortest_index);
        z++;
    }
    
}

void round_robin(int arrival_time[],int burst_time[],int k)
{
    
}

int main()
{
    int k;
    printf("Enter number of processes");
    scanf("%d",&k);

    int arrival_time[k];
    for(int i=0;i<k;i++)
    {
        arrival_time[i]=rand()%11;
        printf("%d ",arrival_time[i]);
    }

    printf("\n");

    int burst_time[k];
    for(int i=0;i<k;i++)
    {
        burst_time[i]=rand()%100;
        printf("%d ",burst_time[i]);
    }

    printf("\n");

    //fcfs(arrival_time,burst_time,k);
    sjf(arrival_time,burst_time,k);
}
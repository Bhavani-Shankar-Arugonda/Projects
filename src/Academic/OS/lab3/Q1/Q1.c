#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int check[20];
int cpu_time;

void hrrn(int arrival_time[],int cpu_burst_time[],int n)
{
    int queue[n];

    int min=0;
    for(int i=0;i<n;i++)
    {
        if(arrival_time[i]<arrival_time[min])
        {
            min=i;
        }
    }
    check[min]=1;

    int ptr=0;
    queue[ptr++]=min;
    cpu_time=arrival_time[min]+cpu_burst_time[min];
    while(ptr<n)
    {
        double max_hrr=0;
        int max_hrr_index=-1;
        for(int i=0;i<n;i++)
        {
            if(check[i]!=1)
            {
                if(arrival_time[i]<=cpu_time)
                {
                    double hrr=(double)((cpu_time-arrival_time[i])+cpu_burst_time[i])/cpu_burst_time[i];
                    if(hrr>max_hrr)
                    {
                        max_hrr=hrr;
                        max_hrr_index=i;

                    }
                }
            }
        }
        if(max_hrr_index != -1)
        {
            queue[ptr++] = max_hrr_index;
            cpu_time = cpu_time + cpu_burst_time[max_hrr_index];
            check[max_hrr_index] = 1;
        }
    }


    printf("Sequence of job execution (process indices): ");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    int n;
    printf("Enter the number of processes : (max is 20)");
    scanf("%d",&n);

    int arrival_time[n];
    int cpu_burst_time[n];
    for(int i=0;i<n;i++)
    {
        arrival_time[i]=rand()%11;
        cpu_burst_time[i]=rand()%101;
    }
    

    printf("\nProcesses:\n");
    printf("PID\tArrival\tBurst\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", i, arrival_time[i], cpu_burst_time[i]);
    }
    printf("\n");

    cpu_time=0;
    hrrn(arrival_time,cpu_burst_time,n);
}

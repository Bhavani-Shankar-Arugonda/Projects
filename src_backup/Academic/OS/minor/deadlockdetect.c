#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int noofprocess = 3;
int noofresources = 3;
int allocated[3][3] = {
    {0, 1, 0},
    {2, 0, 0},
    {0, 0, 1}
};
int request[3][3] = {
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 0}
};
int available[3] = {0, 0, 0};
bool finish[10];
int work[10] = {0};
bool check()//step 4 of unsafe algorithm
{
    for(int i =0;i<noofprocess;i++)
        {
            if(finish[i] == false)
            {
                return false;
            }
        }
        return true;
}
void initializeall()
{
    for(int i =0;i<noofresources;i++)
    {
        work[i] = available[i];//initially transferring all available resources to the work array
    }
    for(int i =0;i<noofprocess;i++)
    {
       int a = 1;
       for(int j =0;j<noofresources;j++)
       {
            if(allocated[i][j] != 0)
            {
                a = 0;
            }
       }
       if(a == 0)
       {
            finish[i] = false;
       }
       else
            finish[i] = true;
    }
}
void deadlockdetection()
{
    int ch = 1;
    bool progress = true;
    initializeall();
    while(progress) 
    {
        progress = false;
        for(int i = 0;i < noofprocess;i++)
        {
            ch = 1;
            for(int j =0;j<noofresources;j++)
            {
                if(request[i][j]>work[j])
                {
                    ch = 0;
                    break;
                }   
            }
            if(finish[i] == false && ch == 1)
            {
                finish[i] = true;
                for(int k = 0;k<noofresources;k++)
                {
                    work[k] = work[k] + allocated[i][k];
                }
                progress = true;
            }
        }
    }
    if(check())
    {
        printf("No Deadlock\n");
    }   
    else
    {
        printf("!!!!DeadLock!!!\n");
    }
}
int main()
{
    deadlockdetection();
}
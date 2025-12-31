#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int noofprocess = 5;
int noofresources = 3;
    int max[10][10] = {
        {7, 5, 3},  // P0
        {3, 2, 2},  // P1
        {9, 0, 2},  // P2
        {2, 2, 2},  // P3
        {4, 3, 3}   // P4
    };
    int allocated[10][10] = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}   // P4
    };
    int total[10] = {10 , 5, 7};
    int available[10] = {3, 3, 2};
    int need[10][10];
    int request[10][10] = {
        {0, 2, 0},
        {1, 0, 2}, 
        {1, 0, 0},
        {0, 0, 2},
        {0, 0, 0}
    };
    int work[10] = {0};
    bool finish[10];
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
        finish[i] = false;//initialzing every process of finish array which has information about total number of process to false
    }
}
void input()
{
    for(int i =0;i<noofprocess;i++)
    {
        for(int j =0;j<noofresources;j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
}
bool safetyalgorithm()
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
                if(need[i][j]>work[j])
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
    return check();   
    
}
void bankers()
{
    for(int i =0;i<noofprocess;i++)
    {
        int flag = 1;
        for(int j =0;j<noofresources;j++)
        {
            if(request[i][j] > need[i][j] || request[i][j] > available[j])
            {
                flag = 0;
            }
        }
        if(flag == 1)
        {
            for(int k =0;k<noofresources;k++)
            {
                available[k] = available[k] - request[i][k];
                allocated[i][k] = allocated[i][k] + request[i][k];
                need[i][k] = need[i][k] - request[i][k];
            }
            bool result =  safetyalgorithm();
            if(result == false)
            {
                for(int k =0;k<noofresources;k++)
                {
                    available[k] = available[k] + request[i][k];
                    allocated[i][k] = allocated[i][k] - request[i][k];
                    need[i][k] = need[i][k] + request[i][k];
                }
                printf("!!!!Unsafe State\n");
                return;
            }
            else
            {
                printf("P%d - Safe\n",i);
            }
        }
    }
}                                                                                                                         
int main()
{
    input();
    bankers();
}
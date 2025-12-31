#include<stdio.h>
#include<stdbool.h>

int main(){
       int n;
       printf("enter number of processe");
       scanf("%d",&n);

       int m;
       printf("enter number of resources");
       scanf("%d",&m);

       int allocation[n][m];
        int maximum[n][m];
        int available[m];
        int need[n][m];

    printf("enter allocation");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }

    printf("enter maximum");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&maximum[i][j]);
        }
    }

    printf("Enter available");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&available[i]);
    }

       for(int i=0;i<n;i++)
       {
        for(int j=0;j<m;j++)
        {
            need[i][j]=maximum[i][j]-allocation[i][j];
        }
       }

       bool finish[n];
       for(int i=0;i<n;i++)
       {
        finish[i]=false;
       }
       int work[m];
       for(int i=0;i<m;i++)
       {
        work[i]=available[i];
       }
        for(int i=0;i<n;i++)
        {
            if(!finish[i])
            {
                bool allocated=true;
                for(int j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        allocated=false;
                        break;
                    }
                }

                if(allocated)
                {
                    for(int k=0;k<m;k++)
                    {
                        work[k]+=allocation[i][k];
                    }
                    finish[i]=true;
                    i = -1;
                }
            }

        }

        for(int i=0;i<n;i++)
        {
            if(finish[i]==false)
            {
                printf("unsafe");
                return 0;
            }
        }
        printf("safe");

}
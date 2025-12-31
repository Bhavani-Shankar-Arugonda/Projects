#include <stdio.h>

int s=4;
int vis[4];
int path[4];
int cycle;

void find(int u,int m[][4])
{
    vis[i]=1;
    path[i]=1;

    for(int v=0;v<s;v++)
    {
        if(m[u][v])
        {
            if(path[v])
            {
                cycle =1;
                return;
            }

            if(!vis[v])
            {
                find(v,m);
                if(cycle) return;
            }
        }
    }
    path[u]=0;
}

void solve(int m[][4],int case)
{
    cycle=0;
    for(int i=0;i<s;i++)
    {
        vis[i]=0;
        path[i]=0;
    }

    for(int i=0;i<s;i++)
    {
        if(!vis[i])
        {
            find(i,m);
        }
    }

    if(cycle)
    {
        printf("Cycle is detected");
    }
    else{
        printf("cycle is not detected");
    }
}

int main() {
    int rag1[4][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };
    
    int rag2[4][4] = {
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };

    solve(rag1, 1);
    solve(rag2, 2);

    return 0;
}
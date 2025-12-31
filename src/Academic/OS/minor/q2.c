#include<stdio.h>
#include<stdbool.h>
int adjmatrix[4][4];
bool visited[4];
int top = -1;
int stack[100];
int visit[10];
int q = 0;
void pushvisited(int x)
{
    visit[q++] = x;
}
void push(int x)
{
    top = top + 1;
    stack[top] = x;
}
int pop()
{
    
    int x = stack[top];
    top = top-1;
    return x;

}
bool dfs(int x)
{
    for(int i =0;i<4;i++)
    {
        if(adjmatrix[x][i] == 1)
        {
            push(i);
            pushvisited(i);
            if(visited[x] == true)
            {
                for(int j =0;j<q;j++)
                {
                    if(visit[j]<2)
                        printf("R%d->",visit[j]+1);
                    else
                        printf("P%d->",visit[j]-1);
                }
                return true;
            }
            visited[x] = true;
        }
    }
    if(top == -1)
    {
        return false;
    }
    return dfs(pop());

}
void createadjacencymatrix()
{
    //Test Case 1
    for(int i =0;i<4;i++)
    {
        for(int j =0;j<4;j++)
        {
            adjmatrix[i][j] = 0;
        }
    }
    printf("Test Case 1\n");
    adjmatrix[0][2] = 1;
    adjmatrix[1][3] = 1;
    adjmatrix[2][1] = 1;
    adjmatrix[3][0] = 1;
    for(int i =0;i<4;i++)
    {
        visited[i] = false;
    }
    if(dfs(0) == true)
    {
        printf("Cycle Detected\n");
    }
    else
    {
        printf("Cycle Not Detected\n");
    }
    printf("Test Case 2\n");
    q = 0;
    adjmatrix[3][0] = 0;
    for(int i =0;i<4;i++)
    {
        visited[i] = false;
    }
    if(dfs(0) == true)
    {
        printf("Cycle Detected\n");
    }
    else
    {
        printf("Cycle Not Detected\n");
    }

}
int main()
{
    createadjacencymatrix();
}
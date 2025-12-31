#include <stdio.h>
#include <stdbool.h>

int main()
{
    int N = 4; 
    int M = 3;

    int Available[] = {5, 5, 4};

    int Max[][3] = {
        {4, 1, 3},
        {1, 0, 2},
        {0, 2, 3},
        {0, 0, 1}
    };

    int Allocation[][3] = {
        {1, 1, 0},
        {0, 0, 1},
        {0, 1, 2},
        {0, 0, 0}
    };

    int Need[4][3];
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    int Request[N][M];
    for(int i=0;i<N;i++)
    {   
        printf("Enter request values for process %d (with space between valus)\n",i);
        for(int j=0;j<M;j++)
        {
            scanf("%d",&Request[i][j]);           
        }
    }

    
    for (int p = 0; p < N; p++)
    {
        bool canGrant = true;

        for (j = 0; j < M; j++)
        {
            if (Request[p][j] > Need[p][j])
            {
                canGrant = false;
                break;
            }
        }

        if (!canGrant)
            continue;

        for (j = 0; j < M; j++)
        {
            if (Request[p][j] > Available[j])
            {
                canGrant = false;
                break;
            }
        }

        if (!canGrant)
            continue;

        
        for (j = 0; j < M; j++)
        {
            Allocation[p][j] = Allocation[p][j] + Request[p][j];
            Available[j] = Available[j] - Request[p][j];
            Need[p][j] = Need[p][j] - Request[p][j];
        }

        //is safe
        bool Finish[] = {false, false, false, false};
        int Work[M];
        for (j = 0; j < M; j++)
            Work[j] = Available[j];

        int count = 0;
        while (count < N)
        {
            bool found = false;
            for (i = 0; i < N; i++)
            {
                if (!Finish[i])
                {
                    bool possible = true;
                    for (j = 0; j < M; j++)
                    {
                        if (Need[i][j] > Work[j])
                        {
                            possible = false;
                            break;
                        }
                    }

                    if (possible)
                    {
                        for (j = 0; j < M; j++)
                            Work[j] += Allocation[i][j];
                        Finish[i] = true;
                        found = true;
                        count++;
                    }
                }
            }
            if (!found)
                break;
        }

        bool safe = true;
        for (i = 0; i < N; i++)
        {
            if (!Finish[i])
            {
                safe = false;
                break;
            }
        }

        if (safe)
        {
            printf("Request of Process %d can be granted safely.\n", p);
        }
        else
        {
            for (j = 0; j < M; j++)
            {
                Available[j] += Request[p][j];
                Allocation[p][j] -= Request[p][j];
                Need[p][j] += Request[p][j];
            }
            printf("Request of Process %d cannot be granted safely (Unsafe state).\n", p);
        }
    }

    printf("\nFinal Allocation Matrix:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
            printf("%d ", Allocation[i][j]);
        printf("\n");
    }

    printf("\nFinal Available Resources:\n");
    for (j = 0; j < M; j++)
        printf("%d ", Available[j]);
    printf("\n");

    return 0;
}

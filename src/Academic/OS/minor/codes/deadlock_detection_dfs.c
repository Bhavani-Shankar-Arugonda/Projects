#include<stdio.h>

int s = 4;
int vis[4];
int path[4];
int cycle;

void find(int u, int m[][4]) {
    vis[u] = 1;
    path[u] = 1;
    
    
    for (int v = 0; v < s; v++) {
        if (m[u][v]) {
            if (path[v]) {
                cycle = 1;
                printf("%d",v);
                return;
            }
            if (!vis[v]) {
                printf("%d->",v);
                find(v, m);
                if (cycle) return;
            }
        }
    }
    
    path[u] = 0;
}

void solve(int m[][4], int case_num) {
    cycle = 0;
    for (int i = 0; i < s; i++) {
        vis[i] = 0;
        path[i] = 0;
    }
    
    for (int i = 0; i < s; i++) {
        if (!vis[i]) {
            printf("%d->",i);
            find(i, m);
        }
    }
    
    printf("case %d: ", case_num);
    if (cycle) {
        printf("deadlock detected\n");
    } else {
        printf("no deadlock\n");
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
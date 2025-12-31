#include<stdio.h>
#include<stdlib.h>

#define page_size 50;

typedef struct{
    int frame_num;
    int valid;
}PTE;

typedef struct{
    int pid;
    PTE pte[10];
    int num;
}PT;

typedef struct{
    int pid;
    int page;
    char type[20];
}FTE;

int main()
{
    int n;
    printf("enter number of physical memory frames : ");
    scanf("%d",&n);
    printf("\n");

    int s;
    printf("enter size of shared library : ");
    scanf("%d",&s);
    printf("\n");

    int k;
    printf("enter number of processe : ");
    scanf("%d",&k);
    printf("\n");

    int l;
    printf("enter size of private data segment : ");
    scanf("%d",&l);
    pritnf("\n");

    FTE ft[n];
    for(int i=0;i<n;i++)
    {
        ft[i].pid=-2;
        ft[i].page=-2;
    }

    //shared memory

    for(int i=0;i<s;i++)
    {
        ft[i].pid=-1;
        ft[i].page=i;
        strcpy(ft[i].type,"Lib");
    }

    PT pt[k];

    for(int i=0;i<k;i++)
    {
        pt[i].num=k;
        pt[i].pid=i;
        for(int j=0;j<s;j++)
        {
           pt[i].pte->frame_num=j;        
        }
    }

    int fnum=s;
    for(int i=0;i<k;i++)
    {
        pt[i].pid=i;
        for(int j=s;j<s+l;j++)
        {
            if(fnum+1>=n)break;
            ft[fnum].page=s;
            ft[fnum].pid=i;
            strcpy(ft[fnum].type,"Data");
            pt[i].pte->valid=1;
            pt[i].pte->frame_num=fnum++;
        }
    }

    int process;
    printf("Enter process num : ");
    scnaf("%d",&process);
    printf("\n");

    int add;
    printf("Enter logical address [between 0 and %d]: ",50*(s+l));
    scanf("%d",&add);

    int page_num=add/50;
    int offset=add%50;
    if(pt[process].pte[page_num].valid!=1)
    {
        printf("invlid address");
        return 0;
    }
    int frame_num=pt[process].pte[page_num].frame_num;

    int physical_add=frame_num*50+offset;
    printf("Physical address id %d ",physical_add);
}
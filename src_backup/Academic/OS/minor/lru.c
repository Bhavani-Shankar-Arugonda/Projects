#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int availableframes = 3;
int referencestring[] = {7, 0, 1, 2, 0, 3, 0, 4,2, 3, 0, 3};
int arr[10];
bool pagealreadypresentornot(int k)
{
    for(int i =0;i<availableframes;i++)
    {
        if(k == arr[i])
            return true;
    }
    return false;
}    
bool freespacepresentornot()
{
    for(int i =0;i<availableframes;i++)
    {
        if(arr[i] == -1)
            return true;
    }
    return false;
}
void printarr()
{
    for(int i =0;i<availableframes;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int pagefaultcount = 0;
int count[3];
int returnindex(int k)
{
    for(int i =0;i<availableframes;i++)
    {
        if(arr[i] == k)
            return i;
    }
    return -1;
}
int returnindexoflru()
{
    int max = 0;
    int j =  0;
    for(int i =0;i<availableframes;i++)
    {
        if(count[i]!=-1)
        {
            if(count[i]>max)
            {
                max = count[i];
                j = i;
            }
        }
    }
    return j;
}   
void incrementallcounters()
{
    for(int i =0;i<availableframes;i++)
    {
        if(count[i]!=-1)
            ++count[i];
    }
}
void lru(int n)
{
    int c = 0;
    for(int i =0;i<availableframes;i++)
    {
        arr[i] = -1;
        count[i] = -1;
    }
    for(int i =0;i<n;i++)
    {
        incrementallcounters();
        if(!pagealreadypresentornot(referencestring[i]))
        {
            if(freespacepresentornot())
            {
                arr[c] = referencestring[i];
                count[c] = 0;
                c++;
            }
            else
            {
               int d = returnindexoflru();
               arr[d] = referencestring[i];
               count[d] = 0;

            }
            pagefaultcount++;
        }
        else
        {
            count[returnindex(referencestring[i])] = 0;
        }
        printarr();
    }
}
int main()
{
    lru(12);
}
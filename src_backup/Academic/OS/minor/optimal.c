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
int pagefaultcount = 0;
int returnindoffarthestusedone(int a)
{
    int indexstore[3];
    int s = 0;
    for(int i = 0;i<availableframes;i++)
    {
        int j = 0;
        for(j=a+1;j<12;j++)//mistake i did
        {
            if(arr[i] == referencestring[j])//mistake i did
            {
                indexstore[s++] = j;//mistake i did 
                break;
            }
        }
        if(j == 12)
            return i;
    }
    int max = 0;
    int u = 0;
    for(int i = 0;i<s;i++)
    {
        if(indexstore[i]>max)
        {
            max = indexstore[i];
            u = i;
        }   
    }
//     for(int i = 0;i<availableframes;i++)
//     {
//         if(referencestring[max] == arr[i]) mistake i did
//             return i;
//     }
    return u;
 }
void printarr()
{
    for(int i =0;i<availableframes;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void optimalpro(int n)
{
    int c = 0;
    for(int i =0;i<availableframes;i++)
    {
        arr[i] = -1;
    }
    for(int i =0;i<n;i++)
    {
        if(!pagealreadypresentornot(referencestring[i]))
        {
            if(freespacepresentornot())
            {
                arr[c] = referencestring[i];
                c++;
            }
            else
            {
                int a = returnindoffarthestusedone(i);
                arr[a] = referencestring[i];
            }
            pagefaultcount++;
        }
        printarr();
    }
    printf("No of Page Faults = %d",pagefaultcount);
    
}
int main()
{
    optimalpro(12);
    return 0;
}
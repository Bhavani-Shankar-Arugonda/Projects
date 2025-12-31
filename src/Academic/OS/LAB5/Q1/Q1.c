#include<stdio.h>
int logical_address_space=128;
int page_size=1024;
int physical_memory_address=64;
int page_table[128];

void get_physical_address(int logical_address)
{
    int page_number=logical_address/page_size;
    printf("Page Number = %d\n",page_number);

    if(page_number<0 || page_number>128)
    {
        printf("Invalid Page number!!");
        return;
    }

    int offset=logical_address%page_size;
    printf("Offset = %d\n",offset);

    int frame=page_table[page_number-1];
    printf("corresponding frame number = %d\n",frame);
    if(frame==-1)
    {
        printf("page fault!!\n");
        return;
    }

    int phycial_address=frame*page_size+offset;
    printf("Physcial address is = %d\n",phycial_address);
}

int main()
{
    for (int i=0;i<128;i++)
    {
        page_table[i]=-1;
    }
    int page_number;
    int frame_number;
    printf("Enter Page Table Entries (Enter -1 to stop entries) : \n");
    while(1)
    {
        printf("Enter Page Number : ");
        scanf("%d",&page_number);
        printf("\n");

        if(page_number==-1)
        {
            break;
        }else if(page_number<-1 || page_number>128)
        {
            printf("Max page number is 128!!");
            return 0;
        }

        printf("Enter Corresponding Frame Number : ");
        scanf("%d",&frame_number);
        printf("\n");

        if(frame_number==-1)
        {
            break;
        }else if(frame_number<-1 || frame_number>65)
        {
            printf("Max frame number is 64!!\n");
            return 0;
        }

        page_table[page_number-1]=frame_number;
    }

    int logical_address;
    int phycial_address;
    while(1)
    {
        printf("Enter Logical Address or -1 to exit : ");
        scanf("%d",&logical_address);
        if(logical_address==-1)
        {
            return 0;
        }
        
        get_physical_address(logical_address);
        
    }
}
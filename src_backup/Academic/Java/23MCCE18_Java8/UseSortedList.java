import java.util.*;
class UseSortedList
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in); 
        int arr[] = new int[50];
        int count  = 0;
        System.out.println("Enter the value to 1 to enter elements into sorted list 0 to stop");
        int p = sc.nextInt();
        while(p!=0)
        {
            if(p == 1)
            {
                System.out.println("Enter the element You want to add");
                arr[count] = sc.nextInt();
                ++count;
            }
            else
            {
                break;
            }
            System.out.println("Enter the value to 1 to enter elements into sorted list 0 to stop");
            p = sc.nextInt();
        }
        SortedList sl = new SortedList(arr,count);
        System.out.println("Enter the value as 0 to exit\n3 to find an value in the sorted list\n1 to insert an element into the sorted list\n2 to delete the element into the sorted list \n4 to display elements of the sorted lsit=");
        int a = sc.nextInt();
        while(a!= 0)
            {
                if(a == 1)
                {
                    System.out.println("Enter the element you want to add = ");
                    int o = sc.nextInt();
                    sl.insert(o);
                }
                else if(a == 2)
                {
                    System.out.println("Enter the element you want to delete = ");
                    int o = sc.nextInt();
                    sl.delete(o);
                }
                else if(a == 3)
                {
                    System.out.println("Enter the element you want to find= ");
                    int o = sc.nextInt();
                    sl.find(o);
                }
                else if(a==4)
                {
                    sl.display();
                }
                else
                {
                    return;
                }
                System.out.println("Enter the value as 0 to exit\n3 to find an value in the sorted list\n1 to insert an element into the sorted list\n2 to delete the element into the sorted list \n 4to display elements of the sorted list=");
                a = sc.nextInt();
            }
    }
}


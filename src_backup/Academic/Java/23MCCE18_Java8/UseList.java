import java.util.*;
class UseList
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        int count = 0;
        System.out.println("Enter the value to 1 to enter elements into sorted list 0 to stop");
        int array[] = new int[50];
        int p = sc.nextInt();
        while(p!=0)
        {
            if(p == 1)
            {
                System.out.println("Enter the element You want to add");
                array[count] = sc.nextInt();
                ++count;
            }
            else
            {
                break;
            }
            System.out.println("Enter the value to 1 to enter elements into sorted list 0 to stop");
            p = sc.nextInt();
        }
        System.out.println("Enter the value as 0 to exit\n 1 to insert into list \n2 to delete an element \n3 to find if an element is present in list\n 4 to display the elements = ");
        int a = sc.nextInt();
        List l = new List(array,count);
        while(a!= 0)
        {
            if(a == 1)
            {
                System.out.println("Enter the element you want to add = ");
                int o = sc.nextInt();
                l.insert(o);
            }
            else if(a == 2)
            {
                System.out.println("Enter the element you want to delete = ");
                int o = sc.nextInt();
                l.delete(o);
            }
            else if(a == 3)
            {
                System.out.println("Enter the element you want to find= ");
                int o = sc.nextInt();
                int u = l.find(o);
                if(u!=100)
                    System.out.println("The element is found at the index = " + u);
            }
            else if(a == 4)
            {
                l.display();
            }
            else
            {
                return;
            }
             System.out.println("Enter the value as 0 to exit\n 1 to insert into list \n2 to delete an element \n3 to find if an element is present in list\n 4 to display the elements = ");
            a = sc.nextInt();
        }
    }
}
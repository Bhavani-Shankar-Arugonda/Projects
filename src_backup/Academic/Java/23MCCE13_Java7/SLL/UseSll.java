import java.util.*;

public class UseSll{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int s=0;
        sll list=new sll();
        while(s!=-1)
        {
            System.out.println("Enter 1 to insert node at biginning / Enter 2 to Delete at biginning / Enter 3 to insert at end / Enter 4 to delete by value / Enter 5 to get sum / Enter 6 to display / Enter -1 to exit.");
            s=sc.nextInt();
            switch(s) {
                case 1:
                    System.out.println("Enter data to insert in the node:");
                    int d=sc.nextInt();
                    list.insertAtBiginning(d);
                    break;
                case 2:
                    list.deleteAtBiginning();
                    break;
                case 3:
                    System.out.println("Enter data to insert in the node:");
                    int a=sc.nextInt();
                    list.insertAtEnd(a,sll.head);
                    break;
                case 4:
                    System.out.println("Enter value to delete:");
                    int data=sc.nextInt();
                    list.DeleteByValue(data,sll.head);
                    break;
                case 5:
                    int sum=list.getSum(sll.head,0);
                    System.out.println("Sum : "+sum);
                    break;
                case 6:
                    list.display(sll.head);
                    System.out.println("");
                    break;
                default:
                    break;
            }
        }
    }
} 
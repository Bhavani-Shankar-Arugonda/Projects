import java.util.*;

public class UseQueueSll{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int s=0;
        QueueSll list=new QueueSll();
        while(s!=-1)
        {
            System.out.println("Enter 1 to enqueue / Enter 2 to dequeue / Enter 3 to peek / Enter 4 to display / Enter 5 to check isEmpty / Enter -1 to exit.");
            s=sc.nextInt();
            switch(s) {
                case 1:
                    System.out.println("Enter data to enqueue:");
                    int d=sc.nextInt();
                    list.enqueue(d);
                    break;
                case 2:
                    list.dequeue();
                    break;
                case 3:
                    list.peek();
                    break;
                case 4:
                    list.display();
                    break;
                case 5:
                    if(list.isEmpty())
                    {
                        System.out.println("Queue is Empty!!");
                    }
                    else{
                        System.out.println("Queue is Not Empty!!");
                    }
                default:
                    break;
            }
        }
    }
} 
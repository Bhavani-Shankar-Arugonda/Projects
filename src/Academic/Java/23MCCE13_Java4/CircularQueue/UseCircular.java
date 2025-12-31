import java.util.*;

public class UseCircular
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter The Size Of The Queue : ");
        int n=sc.nextInt();
        CircularQueue queue = new CircularQueue(n);
        
        int s=0;
        System.out.println("Enter 1 To Enqueue.");
        System.out.println("Enter 2 To Dequeue.");
        System.out.println("Enter 3 To Display.");
        System.out.println("Enter 4 To Exit."); 
        while(s!=4)
        {
            
            s=sc.nextInt();
            switch(s)
            {
                case 1:
                    int k=0; 
                    System.out.print("Enter The Element To Enqueue : ");
                    k= sc.nextInt();
                    queue.enqueue(k);
                    break;
                case 2:
                    queue.dequeue();
                    break;
                case 3:
                    queue.displayElements();
                    break;
                case 4:
                    return;
                
            }
        }
        
    }
}

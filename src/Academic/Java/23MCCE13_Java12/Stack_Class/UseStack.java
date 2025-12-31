import java.util.*;

public class UseStack
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter The Size Of The Stack : ");
        int n=sc.nextInt();
        Stack stack = new Stack(n);
        
        int s=0;
        System.out.println("Enter 1 To Push.");
        System.out.println("Enter 2 To Pop.");
        System.out.println("Enter 3 To Display.");
        System.out.println("Enter 4 To Exit."); 
        while(s!=4)
        {
            
            s=sc.nextInt();
            switch(s)
            {
                case 1:
                    char k=0; 
                    System.out.print("Enter The Element To Push : ");
                    k= sc.next().charAt(0);
                    try{
                        stack.push(k);
                    }
                    catch(OverflowException oe)
                    {
                        System.out.println("Exception caught: " + oe.toString());
                    }
                    break;
                case 2:
                    try{
                        stack.pop();
                    }
                    catch(UnderflowException ue)
                    {
                        System.out.println("Exception caught: " + ue.toString());
                    }
                    break;
                case 3:
                    stack.displayElements();
                    break;
                case 4:
                    return;
                
            }
        }
        
    }
}

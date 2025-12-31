import java.util.*;

public class UseStack {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

    Stack stack = new Stack();

    int s=0;
    System.out.println("Enter 1 to push. Enter 2 to pop, Enter 3 to peek , Enter 4 to check stack is empty, Enter 5 to kow the size of stack.");
    
    while(s!=-1)
    {
        System.out.println("Enter Option : ");
        s=sc.nextInt();
        switch(s)
        {
            case 1:
                System.out.println("Enter data to be pushed:");
                int a=sc.nextInt();
                stack.push(a);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                System.out.println(stack.peek());
                break;
            case 4:
                if(stack.isEmpty())
                {
                    System.out.println("stack is empty!!");
                    
                }
                else
                {
                    System.out.println("stack is not empty!!");
                    
                }
                break;
            case 5:
                System.out.println(stack.size());
                break;

        }
    }
    }
}

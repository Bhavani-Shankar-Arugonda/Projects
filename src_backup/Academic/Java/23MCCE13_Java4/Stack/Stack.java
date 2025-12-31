public class Stack
{
    private int top=-1;
    private char stack[];
    
    Stack(int n)
    {   
         stack = new char[n];
    }
    
    public void push(char a)
    {
        if(isFull())
        {
            System.out.println("Stack Is Full");
            return;
        }
        
        stack[++top]=a;
    }
    
    public void pop()
    {
        if(isEmpty())
        {
            System.out.println("Stack Is Empty");
            return;
        }
        System.out.println("Element Removed From Stack = "+stack[top]);
        top--;
    }
    
    public boolean isFull()
    {
        return top==stack.length-1;    
    }
    
    public boolean isEmpty()
    {
        return top==-1;
    }
   
    public void displayElements()
    {
            for(int i=0; i<=top; i++)
            {
                System.out.print(stack[i]+" ");
            }
            System.out.println();
    }
}

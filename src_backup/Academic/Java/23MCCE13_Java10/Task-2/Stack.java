public class Stack extends ArrayLinearList 
{
    private int top;
    public Stack()
    {
        super();
        top=0;
    }

    public void push(int element)
    {
        super.add(n, element);
        top=super.size();
    }

    public void pop() {
        if (!isEmpty()) {
            super.remove(n - 1);
        } else {
            System.out.println("Stack is empty. Cannot pop.");
        }
    }

    public int peek() {
        if (!isEmpty()) {
            return super.get(n - 1);
        } else {
            System.out.println("Stack is empty. Cannot peek.");
            return -999;
        }
    }
    
    public boolean isEmpty()
    {
        return super.isEmpty();
    }

    public int size()
    {
        return super.size();
    }

    public int indexOf()
    {
        System.out.println("Semantics of ArrayLinearList are not satisfied");
        return 0;
    }

    public String toString()
    {
        System.out.println("Semantics of ArrayLinearList are not satisfied");
        return "$";
    }

    public int get()
    {
        System.out.println("Semantics of ArrayLinearList are not satisfied");
        return 0;
    }

    public int remove()
    {
        System.out.println("Semantics of ArrayLinearList are not satisfied");
        return 0;
    }
    
    public void add()
    {
        System.out.println("Semantics of ArrayLinearList are not satisfied");
        return;
    }
}

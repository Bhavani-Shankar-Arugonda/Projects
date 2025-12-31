public class PostfixToInfix{
    private String postfix;
    private int top=-1;
    private String[] stack;

    PostfixToInfix(String postfix)
    {
        this.postfix=postfix;
        stack = new String[postfix.length()];
    }

    private boolean isFull()
    {
        return this.top+1==stack.length;
    }

    private boolean isEmpty()
    {
        return this.top==-1;
    }

    private String push(String a)
    {
        if(isFull())
        {
            return "";
        }
        else{
            stack[++top]=a;
            return stack[top];
        }
    }

    private  String pop()
    {
        if(isEmpty())
        {
            return "";
        }
        else{
            return stack[top--];
        }
    }

    public String stringConversion()
    {
        for(int i=0; i<postfix.length();i++)
        {
            char ch=postfix.charAt(i);
            if(Character.isLetterOrDigit(ch))
            {
                push(String.valueOf(ch));
            }
            else if(ch == '*' || ch == '/' || ch == '+' || ch == '-')
            {
                String s1=pop();
                String s2=pop();
                String infix="("+s1+ch+s2+")";
                push(infix);
            }
        }
        return pop();
    }
}
public class ParanthesisStack
{
    private int top=-1;
    private char stack[];
    
    public ParanthesisStack(int n) {
        stack = new char[n];
    }

    private void push(char a)
    {   if(top<stack.length-1){
            stack[++top]=a;
        }
    }
    
    private void pop()
    {   
        if(top>=0){
            top--;
        }
    }
    
   
    public int paranthesisCheck(String s)
    {
        for(int i=0; i<s.length(); i++)
        {
            if(s.charAt(i)=='{'||s.charAt(i)=='('||s.charAt(i)=='[')
            {
                push(s.charAt(i));
            }
            else if(s.charAt(i)=='}'||s.charAt(i)==')'||s.charAt(i)==']')
            {
                if (top == -1) {  
                    return 1; 
                }
            
                if((s.charAt(i)== ']'&&stack[top]=='[')||(s.charAt(i)== '}'&&stack[top]=='{')||(s.charAt(i)== ')'&&stack[top]=='('))
                {
                    pop();
                }
                else{
                    return 1;
                }
            }
        }
        if(top==-1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

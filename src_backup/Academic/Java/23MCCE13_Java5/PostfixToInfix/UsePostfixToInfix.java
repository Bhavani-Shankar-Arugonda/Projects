import java.util.*;

public class UsePostfixToInfix{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);

        System.out.println("Enter The Postfix Expression : ");
        String postfix=sc.nextLine();

        PostfixToInfix p=new PostfixToInfix(postfix);

        String infix=p.stringConversion();
        System.out.println("The Infix Systement is : "+infix);
    }
}
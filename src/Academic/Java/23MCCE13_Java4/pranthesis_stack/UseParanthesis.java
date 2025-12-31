import java.util.*;

public class UseParanthesis
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String s=sc.nextLine();
        ParanthesisStack string= new ParanthesisStack(s.length());


        switch (string.paranthesisCheck(s)) {
            case 0:
                System.out.println("Balanced");
                break;
            case 1:
                System.out.println("Unbalanced");
                break;
            default:
                break;
        }
        
    }
}

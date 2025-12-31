import java.util.*;

public class ArmstrongNumber
{
    public static int power(int a, int b)
    {
        int res=1;
        for(int i=0; i<b; i++)
        {
            res=res*a;
        }
        return res;
    }
    public static void armstrongNumber(int n)
    {
        int len=0;
        int temp=n;
        int temp2=n;
        while(temp != 0)
        {
            len++;
            temp=temp/10;
        }

        int sol=0;
        for(int i=0; i<len; i++)
        {
            sol=sol+power(n%10,len);
            n=n/10;
        }
        if(sol==temp2)
        {
            System.out.print("It Is A Armstrong Number.");
            return;
        }
        System.out.print("It Is Not An Armstrong Number.");
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Enter The Number : ");
        int n=sc.nextInt();

        armstrongNumber(n);
    }
}
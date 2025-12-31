import java.util.*;

public class Fibonacchi
{
    //Function to generate Fibonacchi series.
    public static void generateFibonacchi(int n)
    {
        int a=0;
        int b=1;
        int [] myArr = new int[n];
	
	//Calculate terms of the Fibonacchi series and store it in the array.
        myArr[0]=0;
        myArr[1]=1;
        for(int i=2; i<n; i++)
        {
            myArr[i]=a+b;
            a=b;
            b=myArr[i];
        }
	
	//Print Output Array.
	System.out.print("Fibonacchi series : ");
        for(int i=0; i<n; i++)
        {
            System.out.print(myArr[i]+" ");
        }
    }
    
    //Main function.
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        
        //Take number of elements to be printed as user input.
        System.out.println("Enter The Value Of n To Generate n Number Of Fobanacchi Series :");
        int n = sc.nextInt();
        
        //Input validation.
        if(n<=0)
        {
            System.out.println("Invalid Input");
            return;
        }
        
        //call function
        generateFibonacchi(n);
    }
}

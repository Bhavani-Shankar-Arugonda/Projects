import java.util.*;

public class AP
{
    //Funtion to generate Arithmetic progression
    public static void generateAP(int a, int d, int n)
    {	
    	//Calculate and print the terms of the AP as the loop goes on.S
    	System.out.print("Elements Of The AP are : ");
        System.out.print(a+" ");
        for(int i=0; i<n-1; i++)
        {
            a=a+d;
            System.out.print(a+" ");
        }
    }

    public static void main(String[] args) 
    {   
        Scanner sc = new Scanner(System.in);
	
	//Take First Term,Common Difference and Number of terms needed as a user input.
        System.out.println("Enter First Term Of The Arithmetic Progression : ");
        int a = sc.nextInt();
        System.out.println("Enter Common Difference Of The Arithmetic Progression : ");
        int d = sc.nextInt();
        System.out.println("Enter Number Of Terms Needed For The Arithmetic Progression : ");
        int n = sc.nextInt();
	
	//Input validation.
        if(n<=0)
        {
            System.out.println("Invalid Input");
            return;
        }
	
	//call the Function.
        generateAP(a,d,n);
        
    }
}

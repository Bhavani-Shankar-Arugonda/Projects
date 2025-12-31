import java.util.*;

public class BinaryToDecimal
{	
	//Function to convert Binary to Decimal.
	public static void BinaryToDecimal(String binary)
	{
	    int a=0;
	    int s=1,p;
	    
	    //calculating string length of the bainary string.
	    int strlen=binary.length();
	    
	    //Loop to get each Binary number and convert it to Decimal form.
	    for(int i=0; i<strlen; i++)
	    {
		p=binary.charAt(strlen-i-1) - '0';
		
		if(p!=0 && p!=1)
		{
			System.out.print("Invalid Input (Enter only 0 or 1)");
			return;
		}
		
		a = a + p*s;
		s=s*2;
	    }
	    
	    //Print the calculated Decimal number.
	    System.out.print("Binary Value of "+binary+" is "+a+".");        
	}
	public static void main(String[] args)
	{
		
	    Scanner sc = new Scanner(System.in);
	    
	    //Taking binary input as a string from the user.
	    System.out.print("Enter The Binary Number : ");
	    String binary = sc.nextLine();
		
	    //Calling the function.
	    BinaryToDecimal(binary);
	}
}

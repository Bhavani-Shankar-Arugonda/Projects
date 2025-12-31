import java.util.Scanner;

public class SquareCube
{
	//Function to generate squares and cubes upto n.
	public static void generateSquareCubeTable(int n)
	{
		//calculate and print the Squares and Cubes with proper spacing.
		System.out.println("n\tn^2\tn^3");
		for(int i=0; i<=n; i++)
		{
			System.out.println(i+"\t"+i*i+"\t"+i*i*i);
		}
	}
	
	//Main Function.
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		//User Input.
		System.out.println("Enter n To Generate Squares And Cubes Of First n Numbers (n>=0) : ");
		int n = sc.nextInt();
		
		//Input Validation.
		if(n<0)
		{
			System.out.print("Invalid Input (n>=0).");
			return;
		}
		
		//Call Function.
		generateSquareCubeTable(n);
	}
}

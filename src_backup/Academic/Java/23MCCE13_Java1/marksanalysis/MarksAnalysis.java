import java.util.*;
public class MarksAnalysis {

    //Function to calculate and print Min,Max,Avg.
    public static void analyzeMarks(int[] marks, int n)
    {
        int max=0;
        int min=marks[0];
        int avg=0;
	
	//Loop to calculate the Minimum, Maximum, and Sum of the given marks.
        for(int i=0; i<n ; i++)
        {
            if(max < marks[i])
            {
                max=marks[i];
            }
            if(min > marks[i])
            {
                min=marks[i];
            }
            avg=avg+marks[i];
        }
        
        //Print required outputs.
        System.out.println("Maximum Marks = "+max);
        System.out.println("Minumum Marks= "+min);
        System.out.println("Average Of Marks= "+(avg/n));
    }
    
    //Main Function.
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
	
	//take number of students and their marks as user input.
        System.out.println("Enter The Number Of Students : ");
        int n = sc.nextInt();
        int[] marks = new int[n];
        for(int i=0; i<n; i++)
        {
            System.out.println("Enter Marks Of Student (Marks Scaled between 0 and 100) "+(i+1)+" :");
            marks[i] = sc.nextInt();
            
            //Input Validation.
            if(marks[i]<0 || marks[i]>100)
            {
            	System.out.print("Invalid Input(Enter Marks Scaled between 0 and 100).");
            	return;
            }
            
        }
     	
     	//call Function.
        analyzeMarks(marks,n);
    }
}

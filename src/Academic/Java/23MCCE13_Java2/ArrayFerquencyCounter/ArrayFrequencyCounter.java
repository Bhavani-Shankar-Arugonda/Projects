import java.util.*;

public class ArrayFrequencyCounter
{
    public static void arrayFrequencyCounter(int[] arr,int n)
    {
        int max=0; 
        for(int i=0; i<n; i++)
        {
            if(arr[i]>max)
            {
                max=arr[i];
            }
        }

        int [] arr2= new int[max+1];

        for(int i=0; i<n; i++)
        {
            arr2[arr[i]]++;
        }

        for(int i=0; i<=max; i++)
        {
            if(arr2[i]!=0)
            {
                System.out.println(i+":"+arr2[i]);
            }
        }
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in); 
        
        
        System.out.println("Enter The Size Of The Array : ");
        int n=sc.nextInt();

        int [] arr = new int[n];
        System.out.println("Enter The Elements Of The Array One By One : ");
        for(int i=0;i<n ;i++)
        {
            arr[i]=sc.nextInt();
        }

        arrayFrequencyCounter(arr,n);
    }
}
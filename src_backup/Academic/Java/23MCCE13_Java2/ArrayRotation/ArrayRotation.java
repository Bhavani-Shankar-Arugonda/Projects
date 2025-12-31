//package ArrayRotation;
import java.util.*;

public class ArrayRotation
{
    public static int[] swap(int [] arr, int a, int b)
    {
        int temp=arr[a];
        arr[a]=arr[b];
        arr[b]=temp;

        return arr;
    }

    public static void arrayRotation(int [] arr, int n, int k)
    {
        for(int j=0; j<k; j++)
        {
            for(int i=0; i<n-1; i++)
            {
                arr=swap(arr,i,i+1);
            }
        }

        System.out.println("The Rotated Array : ");
        for(int i=0; i<n;i++)
        {
            System.out.print(arr[i]+" ");
        }
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter The Number Of Elements In The Array : ");
        int n = sc.nextInt();

        System.out.println("Enter The Elements Of Array One By One : ");
        
        int [] arr=new int[n];
        for(int i=0; i<n; i++)
        {
            arr[i]=sc.nextInt();
        }

        System.out.println("Enter The Number Of Rations : ");
        int k = sc.nextInt();

        arrayRotation(arr, n, k);

    }
}
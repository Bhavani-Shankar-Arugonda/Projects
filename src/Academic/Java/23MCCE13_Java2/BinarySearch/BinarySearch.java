import java.util.*;

public class BinarySearch
{
    public static void binarySearch(int[] arr,int n,int k)
    {
        int l=0,f=n-1;
        while(l<=f)
        {
            int m=(f+l)/2;
            if(k==arr[m])
            {
                System.out.print("Element Found At Index "+m);
                return;
            }
            else if(k<arr[m])
            {
                f=m-1;
            }
            else if(k>arr[m])
            {
                l=m+1;
            }
        }
        System.out.println("Element Not Found");
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter The Size Of Array : ");
        int n = sc.nextInt();

        int[] arr= new int[n];
        System.out.println("Enter The Elements Of Array One By One(Array Has To Be Sorted)");
        for(int i=0; i<n; i++)
        {
            arr[i]=sc.nextInt();
        }

        System.out.printf("Enter The Key Element : ");
        int k= sc.nextInt();

        binarySearch(arr,n,k);
    }
}
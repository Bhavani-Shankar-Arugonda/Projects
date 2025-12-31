import java.util.*;

public class UseMyComparable{

    public static void sortArray(int[] list,MyComparable comparator)
    {
        int n= list.length;
        for(int i=0; i<n-1;i++)
        {
            for(int j=i+1; j<n;j++)
            {
                if(comparator.compareTo(list[i],list[j])>0)
                {
                    //swap
                    list[i] = list[i] + list[j];  
                    list[j] = list[i] - list[j];  
                    list[i] = list[i] - list[j];
                }
            }
        }

        //print
        System.out.print("Sorted Elements of list : ");
        for(int i=0; i<n;i++)
        {
            System.out.print(list[i]+" ");
        }
        System.out.println("");
    }

    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        
        int n=0;
        System.out.println("Enter the size of the input List : ");
        n=sc.nextInt();

        int[] list = new int[n];
        System.out.println("Enter array Elemets : ");
        for(int i=0; i<n;i++)
        {
            list[i]=sc.nextInt();
        }

        int s=0;
        System.out.println("Enter 1 to print Ascending order.");
        System.out.println("Enter 2 to print Descending order.");
        System.out.println("Enter 3 to print Prime Order.");
        System.out.println("Enter -1 to Exit.");
        while(s!=-1)
        {
            System.out.println("Enter option : ");
            s=sc.nextInt();
            switch(s) {
                case 1:
                    Ascending as = new Ascending(); 
                    sortArray(list, as);
                    break;
                case 2:
                    Descending ds = new Descending();
                    sortArray(list, ds);
                    break;
                case 3:
                    PrimeOrder po = new PrimeOrder();
                    sortArray(list, po);
                    break;
            }
        }
    }
}
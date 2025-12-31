import java.util.*;

public class UseMaxHeap
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int size;
        System.out.println("Enter the Size Of the array");
        size=sc.nextInt();
        MaxHeap h2 = new MaxHeap(size);
        MaxHeap h1 = new MaxHeap(size);

        
            System.out.println("Enter 1 To buildheap.");
            System.out.println("Enter 2 To insert.");
            System.out.println("Enter 3 To delete.");
            System.out.println("Enter 4 To display.");
            System.out.println("Enter 5 To Exit.");
        while(true)
        {  
            int s=sc.nextInt();

            switch(s)
            {
                case 1:
                    
                    
                    System.out.println("Enter the elements Of the array one by one");
                    int[] arr = new int[size];
                    for(int i=0; i<size; i++)
                    {
                        arr[i]=sc.nextInt();
                    }

                    

                    h1.buildHeap(arr);
                    System.out.print("heap elements : ");
                    h1.displayHeap();
                    System.out.println("");
                    System.out.println(" sorted heap elements : ");
                    
                    int[] a = new int[size];
                    for(int i=size-1; i>=0; i--)
                    {
                        a[i]=h1.delete();
                    }

                    for(int i=0; i<size; i++)
                    {
                        System.out.print(a[i]+" ");
                    }
                    return;
                case 2:
                    System.out.println("Enter The Element TO be Inserted");
                    int b = sc.nextInt();
                    
                    h2.insert(b);
                    break;
                case 3:
                    int k=h2.delete();
                    if(k!=-1)
                    {
                        System.out.println("Deleted Elements is "+k);
                    }
                    break;
                case 4:
                    h2.displayHeap();
                    break;
                case 5:
                    break;
                
            }
        }
    }
}
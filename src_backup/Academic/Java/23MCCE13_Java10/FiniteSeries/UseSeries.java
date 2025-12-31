
/**
 * Write a description of class UseSeries here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.*;

public class UseSeries
{
    public static void printSeries(Series a, int howmany){
        for (int i=0;i<howmany;i++){
            System.out.println("Next number in Series: "+a.getNext());
        }
    }
    
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);

        int size;
        System.out.println("Enter size of the array.");
        size=sc.nextInt();

        int arr[] = new int[size];
        System.out.println("Enter the list elements one by one.");
        for(int i=0; i<size; i++)
        {
            arr[i]=sc.nextInt();
        }

        FiniteSeries fs =new FiniteSeries(arr);

        int s=0;
        System.out.println("Enter 1 to get next element.");
        System.out.println("Enter 2 to reset the index and start.");
        System.out.println("Enter 3 to set start.");
        System.out.println("Enter 4 to print the series from start.");
        System.out.println("Enter -1 to exit");
        while(s!=-1)
        {
            System.out.print("Enter Option : ");
            s=sc.nextInt();
            System.out.println("");
            switch(s)
            {
                case 1:
                    int a= fs.getNext();
                    System.out.println("    Next Element : "+a);
                    break;
                case 2:
                    fs.reset();
                    break;
                case 3:
                    System.out.print("    Enter Index to set start : ");
                    int next=sc.nextInt();
                    fs.setStart(next);
                    System.out.println("");
                    break;
                case 4:
                    System.out.print("Enter number of elements to be printed : ");
                    int k=sc.nextInt();
                    printSeries(fs,k);
                    System.out.println("");
                    break;
            }
        }
    }
}

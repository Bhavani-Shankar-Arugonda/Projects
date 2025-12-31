import java.util.*;
public class FiniteSeries implements Series{
     int arr[];
    private int ind;
    private int start;

    FiniteSeries(int[] arr)
    {
        this.arr=new int[arr.length];
        for(int i=0; i<arr.length;i++)
        {
            this.arr[i]=arr[i];
        }
        ind=0;
        start=0;
    }

    public int getNext()
    {
        
        if(ind>=arr.length)
        {
            ind=0;
            return arr[ind++];
        }
        return arr[ind++];    
    }

    public void reset()
    {
        ind=0;
        start=0;
    }

    public void setStart(int i)
    {
        start=ind=i;
    }
}
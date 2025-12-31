public class Ascending implements MyComparable{
    @Override
    public int compareTo(int first,int second)
    {
        if(first>second)
            return 1;
        else if(second>first)
            return -1;
        else
            return 0;
    }
}
public class PrimeOrder implements MyComparable{

    private boolean isPrime(int b)
    {
        if (b < 2) return false;
        if (b == 2) return true; 
        if (b % 2 == 0) return false; 

        for (int i = 3; i * i <= b; i += 2) 
        { 
            if (b % i == 0) {
                return false;
            }
        }
        return true;
    }

    private int getLargestPrimeFactor(int a)
    {
        int temp=a;
        while(temp>1)
        {
            if(isPrime(temp) && a%temp==0)
            {
                return temp;
            }
            temp--;
        }
        return 1;
    }

    @Override
    public int compareTo(int first,int second)
    {
        if(getLargestPrimeFactor(first)>getLargestPrimeFactor(second))
            return 1;
        else if(getLargestPrimeFactor(first)<getLargestPrimeFactor(second))
            return -1;
        else
        {
            if(first>second)
                return 1;
            else if(second>first)
                return -1;
            else
                return 0;
        }
    }
}
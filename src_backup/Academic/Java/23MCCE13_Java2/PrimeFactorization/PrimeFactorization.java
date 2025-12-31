//package PrimeFacorization;

import java.util.Scanner;

public class PrimeFactorization 
{
    public static int isPrime(int i)
    {
        for(int j=2; j<i; j++)
        {
            if(i%j==0)
            {
                return 0;
            }
        }
        return 1;
    }
    public static void primeFactorization(int n)
    {
        if(isPrime(n)==1)
        {
            System.out.print("Given Number Is A Prime Number.");
            return;
        }
        int i=2;
        int s=n;
        while(i<s)
        {
            if(n%i==0)
            {
                if(isPrime(i)==1)
                {
                    System.out.print(i+" ");
                }
                n=n/i;
                
            } 
            else
            {
                i++;
            }
        }
    }
    public static  void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter The Number : ");
        int n = sc.nextInt();
        if(n<=0)
        {
            System.out.print("Invalid Input(n>=0)");
            return;
        }

        primeFactorization(n);
    }    
}

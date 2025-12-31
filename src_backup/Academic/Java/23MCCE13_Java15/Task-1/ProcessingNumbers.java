import java.io.*;
import java.lang.*;
import java.util.*;

public class ProcessingNumbers {
    public static void main(String[] args)
    {
        try{
            int sum=0;
            int count=0;
            File myFile= new File("input.txt");
            Scanner sc = new Scanner(myFile);
            System.out.println("Numbers in the given file are : ");
            while(sc.hasNextLine())
            {
                String line=sc.nextLine();
                String[] parts=line.split("[,\\s]+");
                for(String part : parts)
                {
                    try{
                        if(part.trim().isEmpty())
                            continue;
                        System.out.println(part);
                        int number=Integer.parseInt(part.trim());
                        sum += number;
                        count++;
                    }catch(NumberFormatException e)
                    {
                        System.out.println(e);
                    }
                }
            }
            System.out.println("");
            System.out.println("Total Number is : "+count);
            System.out.println("Average Sum "+sum/count);
        }catch(FileNotFoundException e)
        {
            System.out.println(e);
        }
    }
}

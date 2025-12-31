import java.util.*;
import java.io.*;

public class ByteArray {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the number Subjects : ");
        int count=sc.nextInt();

        try{
            ByteArrayOutputStream byteArray = new ByteArrayOutputStream((count+1)*4);
            DataOutputStream input= new DataOutputStream(byteArray);

            for(int i=0; i<count; i++)
            {
                System.out.println("Enter marks : ");
                int marks=sc.nextInt();
                input.writeInt(marks);
            }

            byte[] packedData = byteArray.toByteArray();

            ByteArrayInputStream outputBiteArray = new ByteArrayInputStream(packedData);
            DataInputStream output = new DataInputStream(outputBiteArray);

            for(int i=0; i<count; i++)
            {   
                int outputMarks=output.readInt();
                System.out.println("output marks : "+outputMarks);
            }
        }catch(IOException e)
        {
            System.out.println(e);
        }
    }
    
}

import java.io.*;
import java.util.*;

public class ManyExceptions {
    public void sayHello(int a) {
        System.out.println("Hello");
    }

    public static void main(String[] args) {
        try {
            System.out.println("The third argument is " + args[2]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Insufficient arguments provided.");
        }
        
        Scanner sc = new Scanner(System.in);
        int a = 0, b = 1, c = 0;
        
        try {
            System.out.println("Enter a number:");
            a = sc.nextInt();

            System.out.println("Enter another number:");
            b = sc.nextInt();
        } catch (InputMismatchException e) {
            System.out.println("Error: Please enter valid integers.");
            sc.next(); 
        }
        
        try {
            c = a / b;
            System.out.println("The result of the division is " + c);
        } catch (ArithmeticException e) {
            System.out.println("Error: Division by zero is not allowed.");
        }
        
        try {
            int d = sc.nextInt();
        } catch (NoSuchElementException e) {
            System.out.println("Error: No input available for reading.");
        }
        
        sc.close();

        ManyExceptions me = null;
        try {
            me.sayHello(5);
        } catch (NullPointerException e) {
            System.out.println("Error: Attempted to call a method on a null object.");
        }

        try (BufferedReader br = new BufferedReader(new FileReader("file1.txt"))) {
            String line = br.readLine();
            System.out.println("Read line: " + line);
        } catch (FileNotFoundException e) {
            System.out.println("Error: file1.txt not found.");
        } catch (IOException e) {
            System.out.println("Error: An error occurred while reading the file.");
        }
        
        try {
            int[] arr = new int[5];
            System.out.println("Element1 : " + arr[3] + "\nElement2 : " + arr[5]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Array index out of bounds.");
        }

        try (BufferedReader reader = new BufferedReader(new FileReader("file1.txt"))) {
            String data = reader.readLine();
            System.out.println("Read data: " + data);
        } catch (FileNotFoundException e) {
            System.out.println("Error: file1.txt not found.");
        } catch (IOException e) {
            System.out.println("Error: An error occurred while reading the file.");
        }
    }
}

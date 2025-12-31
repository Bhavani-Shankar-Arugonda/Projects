import java.util.Scanner;

public class StringCompression {
    public static void stringCompression(String str) {
        int n = str.length();
        for (int i = 0; i < n; ) {
            char currentChar = str.charAt(i);
            int count = 1;

          
            while (i + 1 < n && str.charAt(i) == str.charAt(i + 1)) {
                count++;
                i++;
            }

            
            System.out.print(currentChar);
            if (count >= 1) {
                System.out.print(count);
            }

            i++;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the string: ");
        String str = sc.nextLine();

        stringCompression(str);
    }
}

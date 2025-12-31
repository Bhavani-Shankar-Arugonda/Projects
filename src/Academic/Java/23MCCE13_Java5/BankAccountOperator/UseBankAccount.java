import java.util.Scanner;

class UseBankAccount {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BankAccount b1 = null; 

        int s = 0;
        while (true) {
            System.out.println("Press 1 to create account / Press 2 to deposit / Press 3 to withdraw / Press 4 to display account / Press 5 to exit");
            s = sc.nextInt();
            sc.nextLine();

            switch (s) {
                case 1:
                    System.out.println("Enter account name:");
                    String accountName = sc.nextLine();

                    System.out.println("Enter PIN number:");
                    int pinNumber = sc.nextInt();

                    System.out.println("Enter deposit amount:");
                    double depositAmount = sc.nextDouble();

                    System.out.println("Enter interest rate:");
                    double interestRate = sc.nextDouble();

                    b1 = new BankAccount(accountName, pinNumber, depositAmount, interestRate);
                    System.out.println("Account created successfully!");
                    break;

                case 2:
                    if (b1 == null) {
                        System.out.println("No account found! Create an account first.");
                        break;
                    }
                    System.out.println("Enter amount to be deposited:");
                    double a = sc.nextDouble();
                    b1.deposit(a);
                    break;

                case 3:
                    if (b1 == null) {
                        System.out.println("No account found! Create an account first.");
                        break;
                    }
                    System.out.println("Enter PIN:");
                    int k = sc.nextInt();
                    System.out.println("Enter amount to withdraw:");
                    double b = sc.nextDouble();
                    b1.withdraw(k, b);
                    break;

                case 4:
                    if (b1 == null) {
                        System.out.println("No account found! Create an account first.");
                        break;
                    }
                    System.out.println("Enter PIN:");
                    int m = sc.nextInt();
                    b1.displayAccount(m);
                    break;

                case 5:
                    System.out.println("Exiting...");
                    sc.close();
                    return;

                default:
                    System.out.println("Enter a valid option.");
            }
        }
    }
}

public class BankAccount{
    private String accountName; 
    private int pinNumber; 
    private double depositAmount;
    private double interestRate;
    private String accountNumber;

    static int counter=1000;

    BankAccount(String accountName, int pinNumber, double depositAmount,double interestRate)
    {
        this.accountName=accountName;
        this.pinNumber=pinNumber;
        this.depositAmount=depositAmount;
        this.interestRate=interestRate;
        counter++;
        this.accountNumber= "ACC"+String.valueOf(counter);
    }

    void deposit(double amount)
    {
        if(amount <0)
        {
            System.out.println("ERROR");
            return;
        }
        else
        {
            this.depositAmount=this.depositAmount+amount;
        }
    }
    void withdraw(int PIN,double amount)
    {
        if(this.depositAmount< amount)
        {
            System.out.println("LOW BALANCE");
            return ;
        }
        else
        {
            this.depositAmount=this.depositAmount-amount;
            System.out.println("Withdrawn amount is "+amount);
        }
    }
    void displayAccount(int PIN)
    {
        if(this.pinNumber != PIN)
        {
            System.out.println("INCORRECT PIN");
        }
        else
        {
            System.out.print("Account name: "+this.accountName+"\n"+"Account No: "+this.accountNumber+"\n"+
            "PIN: "+this.pinNumber+"\n"+"Total Amount: "+this.depositAmount+"\n"+
            "Intrest Rate: "+this.interestRate +"\n");
        }
    }
    void checkBalance(int PIN)
    {
        if(this.pinNumber != PIN)
        {
            System.out.println("WRONG PIN");
        }
        else
        {
            System.out.println("Balance"+depositAmount);
        }
    }
}
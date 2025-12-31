import java.time.LocalDate;
import java.util.*;

//package Java3.GreetingCard;

class useGreeting {
    public static void main(String [] args)
    {
        Scanner sc= new Scanner(System.in);

       System.out.println("Enter your name : ");
       String name = sc.nextLine();

        System.out.println("Enter Your Birthday(yyyy-mm-dd) :");
        String birthday = sc.nextLine();
        LocalDate bday = LocalDate.parse(birthday);

        System.out.println();
        Greeting gt = new Greeting();
        gt.greetPerson(name);
        gt.greetBirthday(bday,name); 
        gt.getage(bday);

    }   


}

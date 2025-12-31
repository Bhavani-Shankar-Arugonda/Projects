//package Java3.GreetingCard;
import java.time.LocalDate;
import java.time.LocalTime;

class Greeting 
{
    void greetPerson(String name)
    {
        LocalTime time1;
        time1=LocalTime.now();

        if(time1.compareTo(LocalTime.of(05,00,00))>=0 && time1.compareTo(LocalTime.of(11,59,00))<=0)
        {
            System.out.println("Good Morning,"+name+"!");
        }
        else if(time1.compareTo(LocalTime.of(12,00,00))>=0 && time1.compareTo(LocalTime.of(15,59,00))<=0)
        {
            System.out.println("Good Afternoon,"+name+"!");
        }
        else if(time1.compareTo(LocalTime.of(16,00,00))>=0 && time1.compareTo(LocalTime.of(18,59,00))<=0)
        {
            System.out.println("Good Evening,"+name+"!");
        }
        else{
            System.out.println("Good Night,"+name+"!");
        }
    }   

    void greetBirthday(LocalDate day, String name)
    {
        LocalDate current = LocalDate.now();
        LocalDate bday=LocalDate.of(current.getYear(),day.getMonthValue(),day.getDayOfMonth());

        if(current.compareTo(bday)>0)
        {
            System.out.println("Belated Happy Birthday,"+name+"!");
        }
        else if(current.compareTo(bday)<0)
        {
            System.out.println("Advanced Happy Birthday,"+name+"!");
        }
        else if(current.compareTo(bday)==0)
        {
            System.out.println("Happy Birthday,"+name+"!");
        }

    }

    void getage(LocalDate bday)
    {
        LocalDate today=LocalDate.now();
        int year= (today.getYear()-bday.getYear());
        int month;
        if(bday.getMonthValue()>today.getMonthValue())
        {
            month=12-bday.getMonthValue()+today.getMonthValue();
            System.out.println("You are "+(year-1)+" years and "+month+" months old");
        }
        else{
            month=today.getMonthValue()-bday.getMonthValue();
            System.out.println("You are "+year+" years and "+month+" months old");    
        }
    }

    
}

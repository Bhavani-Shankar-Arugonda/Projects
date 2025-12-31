import java.util.*;

public class B extends A {
    B()
    {
        System.out.println("B class is being used now");
    }
    void changepublic()
    {
        
        aa = 11;
        System.out.println("Public variable is child class after being modified is "+aa);
    }
    void changeprivate()
    {
        System.out.println("Child class can't access parent class private variable");
        super.setprivate();
    }
    void changedefault()
    {
       
        ad = 44;
        System.out.println("Default variable is child class after being modified is "+ad);
    }
    void changeprotected()
    {
        
        ac = 33;
        System.out.println("Protected variable is child class after being modified is "+ac);
    }
    void changestatic()
    {
        ae = 55;
        System.out.println("Protected variable is child class after being modified is "+ae);
    }
    void common()
    {
        System.out.println("PUblic variable in child class " + aa);
    }
}

import java.util.*;
class UseB
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        B b = new B();
        A a = new A();
       
        b.setpublic();
        b.changepublic();
        b.setprivate();
        b.changeprivate();
        b.setdefault();
        b.changedefault();
        b.setprotected();
        b.changeprotected();
        b.setstatic();
        b.changestatic();
        a.common();
        b.common();
        A a1 = new A(100);
        System.out.println("Now B object can access Parent class public instance variable ="+b.aa);
        System.out.println("Now B object cannot access Parent class public instance variable ");
        System.out.println("Now B object can access Parent class protected instance variable ="+b.ac);
        System.out.println("Now B object can access Parent class default instance variable ="+b.ad);
        System.out.println("Now B class can access Parent class static instance variable ="+B.ae);
    }
}
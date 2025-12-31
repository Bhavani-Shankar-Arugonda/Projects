class A
{
    public int aa;
    private int ab;
    protected int ac;
    public static int ae;
    int ad;
    A()
    {
        System.out.println("A class is being used now");
    }
    A(int a)
    {
        System.out.println("A Pramaterized A Constructor is called = " + a);
    }
    void setpublic()
    {
        
        aa = 1;
        System.out.println("Public variable in parent class is "+aa);
    }
    void setprivate()
    {
        ab = 2;
        System.out.println("Private variable in parent class is "+ab);
    }
    void setprotected()
    {
        ac = 3;
        System.out.println("Protected variable in parent class is "+ac);
    }
    void setdefault()
    {
        ad = 4;
        System.out.println("Default variable in parent class is "+ad);
    }
    void setstatic()
    {
        ae = 5;
        System.out.println("Static variable in parent class is "+ae);
    }
    void common()
    {
        System.out.println("Public variable in parent class " + aa);
    }

}
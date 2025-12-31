import java.util.*;

class useLines{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);

        System.out.println("Enter coefficients(a,b,c) of line 1 one by one : ");
        double a1=sc.nextDouble();
        double b1=sc.nextDouble();
        double c1=sc.nextDouble();

        System.out.println("Enter coefficients(a,b,c) of line 1 one by one : ");
        double a2=sc.nextDouble();
        double b2=sc.nextDouble();
        double c2=sc.nextDouble();

        System.out.println("Enter the coordinates of the point:");
        double x=sc.nextDouble();
        double y=sc.nextDouble();
    
        StraightLines l1 = new StraightLines(a1,b1,c1);
        StraightLines l2 = new StraightLines(a2,b2,c2);

        if(l1.isParallel(l2))
        {
            System.out.println("Given lines are parallel.");
        }
        else
        {
            System.out.println("Given lines are not parallel.");
        }

        if(l1.isPerpendicular(l2))
        {
            System.out.println("Given lines are perpendicular.");
        }
        else
        {
            System.out.println("Given lines are not perpendicular.");
        }

        Point p=new Point(x,y);
        if(p.isOnLine(l1))
        {
            System.out.println("Given Point lies on First line.");
        }
        else{
            System.out.println("Given Point Does not lie on First line.");
        }

        if(p.isOnLine(l2))
        {
            System.out.println("Given Point lies on Second line.");
        }
        else{
            System.out.println("Given Point Does not lie on Second line.");
        }
    } 
}
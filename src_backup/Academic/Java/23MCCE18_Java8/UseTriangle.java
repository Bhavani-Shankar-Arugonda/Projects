import java.util.*;
class UseTriangle
{
    public static boolean checkTriangle(int points[][])
    {
        double hyp = ((points[2][0] - points[0][0])*(points[2][0] - points[0][0]) + (points[2][1]-points[0][1])*(points[2][1]-points[0][1]));
        double height = ((points[1][0] - points[0][0])*(points[1][0] - points[0][0]) + (points[1][1]-points[0][1])*(points[1][1]-points[0][1]));
        double base = ((points[2][0] - points[1][0])*(points[2][0] - points[1][0]) + (points[2][1]-points[1][1])*(points[2][1]-points[1][1]));
        if(hyp == height + base)
        {
            return true;
        }
       
        return false;
    }
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a value as 1 to create a  Triangle 0 to exit =");
        int a = sc.nextInt();
        while(a!=0)
        {
            if(a==1)
            {
                Triangle t = new Triangle();
                System.out.println("Start entering the points");
                System.out.println("(x1,y1) (x3,y3) form the hypotenuse and (x2,y2) point is common for both height and base of the Right Angle Triangle");
                System.out.println("Enter the x"+ 1 + "coordinate =");
                t.points[0][0] = sc.nextInt();
                System.out.println("Enter the y"+ 1 + "coordinate =");
                t.points[0][1]= sc.nextInt();
                System.out.println("Enter the x"+ 2 + "coordinate =");
                t.points[1][0] = sc.nextInt();
                System.out.println("Enter the y"+ 2 + "coordinate =");
                t.points[1][1] = sc.nextInt();
                System.out.println("Enter the x"+ 3 + "coordinate =");
                t.points[2][0] = sc.nextInt();
                System.out.println("Enter the y"+ 3 + "coordinate =");
                t.points[2][1] = sc.nextInt();
                boolean check = checkTriangle(t.points);
                if(check == true)
                {
                    System.out.println("The given triangle is a Right Angle Triangle");
                    RightAngleTriangle r = new RightAngleTriangle();
                    r.points = t.points;
                    System.out.println("Enter the value to 1 to find the area of the Right Angle Triangle 2 to find perimeter of the Right Angle Triangle 0 to return");
                    int k = sc.nextInt();
                    while(k!=0)
                    {
                        if(k==1)
                        {
                            r.area();
                        }
                        else if(k == 2)
                        {
                            r.perimeter();
                        }
                        else
                        {
                            return;
                        }
                        System.out.println("Enter the value to 1 to find the area of the Right Angle Triangle 2 to find perimeter of the Right Angle Triangle 0 to return");
                        k = sc.nextInt();
                    }
                }
                else
                {
                    System.out.println("Enter the value to 1 to find the area of the Triangle 2 to find perimeter of the Triangle 0 to return");
                    int k = sc.nextInt();
                    while(k!=0)
                    {
                        if(k==1)
                        {
                            t.area();
                        }
                        else if(k == 2)
                        {
                            t.perimeter();
                        }
                        else
                        {
                            return;
                        }
                        System.out.println("Enter the value to 1 to find the area of the Triangle 2 to find perimeter of the Triangle 0 to return");
                        k = sc.nextInt();
                    }
                }
            }
            else
            {
                return;
            }
            System.out.println("Enter a value as 1 to create a  Triangle 0 to exit =");
            a = sc.nextInt();
        }
    }
}
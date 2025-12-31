import java.util.*;

public class UseShape
{
    public void getAreaPerimeter(Shape sh){
        System.out.println("Area: " + sh.getArea());
        System.out.println("Perimeter: " + sh.getPerimeter());
    }
    public static void main(String[] args)
    {
        Scanner sc= new Scanner(System.in);
        int s=0;
        System.out.println("Enter 1 to check for Triangle.");
        System.out.println("Enter 2 to check for Circle.");
        System.out.println("Enter 3 to check for Parallelogram.");
        System.out.println("Enter -1 to exit.");
        while(s!=-1)
        {
            s=sc.nextInt();
            UseShape useShape = new UseShape();
            switch(s)
            {
                case 1:
                    double arr[][]= new double[3][2];
                    System.out.println("Enter cordinates of triangle:");
                    for(int i=0; i<3;i++)
                    {
                        for(int j=0; j<2; j++)
                        {
                            arr[i][j]=sc.nextDouble();
                        }
                    }
                    
                    Triangle triangle=new Triangle(arr);
                    
                    useShape.getAreaPerimeter(triangle);
                    System.out.println("Area of the given Triangle = "+triangle.getArea());
                    System.out.println("Perimeter of the given Triangle = "+triangle.getPerimeter());
                    if(triangle.isRightAngleTriangle())
                    {
                    System.out.println("Given Triangle is a Right Angled Traingle!!");
                    }   
                    if(triangle.isEquilateralTriangle())
                    {
                    System.out.println("Given Triangle is a Equilateral Traingle!!");
                    }
                    if(triangle.isIsoscelesTriangle())
                    {
                    System.out.println("Given Triangle is a Isosceles Traingle!!");
                    }
                    break;
                case 2:
                    System.out.println("Enter the radius of the triangle.");
                    double r=sc.nextDouble();
                    System.out.println("Enter the x coordinate of center.");
                    double x=sc.nextDouble();
                    System.out.println("Enter the y coordinate of center.");
                    double y=sc.nextDouble();
                    
                    Circle circle = new Circle(r,x,y);
                    useShape.getAreaPerimeter(circle);
                    System.out.println("Area of the given Circle = "+circle.getArea());
                    System.out.println("Perimeter of the given Circle = "+circle.getPerimeter());
                    
                    System.out.println("Enter x coordinate to check if point is inside");
                    double X=sc.nextDouble();
                    System.out.println("Enter y coordinate to check if point is inside");
                    double Y=sc.nextDouble();
                    
                    if(circle.isPointInside(X,Y))
                    {
                        System.out.println("The Point is inside the Circle!!");
                    }
                    else
                    {
                        System.out.println("The Point is outside the Circle!!");
                    }
                    break;
                case 3:
                    System.out.println("Enter the base of the paralellogram.");
                    double b=sc.nextDouble();
                    System.out.println("Enter the height of the paralellogram.");
                    double h=sc.nextDouble();
                    System.out.println("Enter the angle of the paralellogram in degrees.");
                    double a=sc.nextDouble();
                    System.out.println("Enter the legth of side 1 of the paralellogram.");
                    double s1=sc.nextDouble();
                    System.out.println("Enter the length of side 2 of the paralellogram.");
                    double s2=sc.nextDouble();
                    
                    Parallelogram p= new  Parallelogram(b,h,a,s1,s2);
                    useShape.getAreaPerimeter(p);
                    System.out.println("Area of the given parallelogram = "+p.getArea());
                    System.out.println("Perimeter of the given parallelogram = "+p.getPerimeter());
                    
                    if(p.isRectangle())
                    {
                    System.out.println("Given Parallelogram is a Rectangle!!");
                    }   
                    if(p.isSquare())
                    {
                    System.out.println("Given Parallelogram is a Square!!");
                    }
                    break;
            }
        }
    }
}

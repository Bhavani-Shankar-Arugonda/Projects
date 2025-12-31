public class Parallelogram extends Shape
{
    private double base;
    private double height;
    private double angle;
    private double side1;
    private double side2;
    
    Parallelogram(double base,double height,double angle, double side1,double side2)
    {
        this.base=base;
        this.height=height;
        this.angle=angle;
        this.side1=side1;
        this.side2=side2;
    }
    
    public double getArea()
    {
        return base*height;
    }
    
    public double getPerimeter()
    {
        return 2*(side1+side2);
    }
    
    public boolean isRectangle()
    {
        return angle==90;
    }
    
    public boolean isSquare()
    {
        return (angle==90 && side1==side2);
    }
}

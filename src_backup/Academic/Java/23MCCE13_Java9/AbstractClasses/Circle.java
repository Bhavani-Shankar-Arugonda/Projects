public class Circle extends Shape
{
    private double radius;
    private double centerX;
    private double centerY;
    
    Circle(double r, double x,double y)
    {
        radius=r;
        centerX=x;
        centerY=y;
    }
    
    public double getArea()
    {
        return Math.PI*Math.pow(radius,2);
    }
    
    public double getPerimeter()
    {
        return Math.PI*2*radius;
    }
    
    public boolean isPointInside(double x,double y)
    {
        return Math.sqrt(Math.pow(centerX-x,2)+Math.pow(centerY-y,2))<=radius;
    }
}

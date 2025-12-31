
public class Triangle extends Shape
{
    double arr[][]=new double[3][2];
    
    Triangle(double[][] arr)
    {
        this.arr=arr;
    }
    
    public double getArea()
    {
        double area=Math.abs(((arr[0][0]*(arr[1][1]-arr[2][1]))+(arr[1][0]*(arr[2][1]-arr[0][1]))+(arr[2][0]*(arr[0][1]-arr[1][1])))/2);
        return area;
    }
    
    public double getPerimeter()
    {
        double perimeter=Math.sqrt(Math.pow(arr[1][0]-arr[0][0],2)+Math.pow(arr[1][1]-arr[0][1],2))+Math.sqrt(Math.pow(arr[2][0]-arr[1][0],2)+Math.pow(arr[2][1]-arr[1][1],2))+Math.sqrt(Math.pow(arr[2][0]-arr[0][0],2)+Math.pow(arr[2][1]-arr[0][1],2));
        return perimeter;
    }
    
    public boolean isRightAngleTriangle()
    {
        double side1=(Math.pow(arr[1][0]-arr[0][0],2)+Math.pow(arr[1][1]-arr[0][1],2));
        double side2=(Math.pow(arr[2][0]-arr[1][0],2)+Math.pow(arr[2][1]-arr[1][1],2));
        double side3=(Math.pow(arr[2][0]-arr[0][0],2)+Math.pow(arr[2][1]-arr[0][1],2));
        
        double maxsize=side1;
        if(maxsize<side2)
        {
            maxsize=side2;
        }
        if(maxsize<side3)
        {
            maxsize=side3;
        }
        
        return side1+side2+side3-(2*maxsize)==0;
    }
    
    public boolean isEquilateralTriangle()
    {
        double side1=(Math.pow(arr[1][0]-arr[0][0],2)+Math.pow(arr[1][1]-arr[0][1],2));
        double side2=(Math.pow(arr[2][0]-arr[1][0],2)+Math.pow(arr[2][1]-arr[1][1],2));
        double side3=(Math.pow(arr[2][0]-arr[0][0],2)+Math.pow(arr[2][1]-arr[0][1],2));
        
        return (side1==side2 && side2==side3);
    }
    
    public boolean isIsoscelesTriangle()
    {
        double side1=(Math.pow(arr[1][0]-arr[0][0],2)+Math.pow(arr[1][1]-arr[0][1],2));
        double side2=(Math.pow(arr[2][0]-arr[1][0],2)+Math.pow(arr[2][1]-arr[1][1],2));
        double side3=(Math.pow(arr[2][0]-arr[0][0],2)+Math.pow(arr[2][1]-arr[0][1],2));
        
        return ((side1==side2)||(side1==side3)||(side2==side3));
    }
    
    
}

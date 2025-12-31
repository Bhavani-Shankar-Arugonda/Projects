class RightAngleTriangle extends Triangle
{
    void perimeter()
    {
        double per = 0;
        per = per + Math.sqrt((points[1][0] - points[0][0])*(points[1][0] - points[0][0]) + (points[1][1]-points[0][1])*(points[1][1]-points[0][1]));
        per = per + Math.sqrt((points[2][0] -points[0][0])*(points[2][0] - points[0][0]) + (points[2][1]-points[0][1])*(points[2][1]-points[0][1]));
        per = per + Math.sqrt((points[2][0] - points[1][0])*(points[2][0] - points[1][0]) + (points[2][1]-points[1][1])*(points[2][1]-points[1][1]));
        System.out.println("Perimeter of the Right Angle Triangle = "+per);
    }
    void area()
    {
        double base;
        double height;
        height = Math.sqrt((points[1][0] - points[0][0])*(points[1][0] - points[0][0]) + (points[1][1]-points[0][1])*(points[1][1]-points[0][1]));
        base = Math.sqrt((points[2][0] - points[1][0])*(points[2][0] - points[1][0]) + (points[2][1]-points[1][1])*(points[2][1]-points[1][1]));
        double area = (0.5)*(base)*(height);
        System.out.println("Area of the Right Angle Triangle = "+area);
    }
}
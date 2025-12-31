class Triangle
{
    public int[][] points = new int[3][2];
    void area()
    {
        double area = 0;
        area = ((points[0][0]*points[1][1])-(points[0][1]*points[1][0])+(points[1][0]*points[2][1])-(points[2][0]*points[1][1])+(points[2][0]*points[0][1]) - (points[0][0]*points[2][1]));
        area = area/2;
        if(area<0)
            area= area*-1;
        System.out.println("Area of the give triangle is = " + area);
    }
    void perimeter()
    {
        double per = 0;
        per = per + Math.sqrt((points[1][0] - points[0][0])*(points[1][0] - points[0][0]) + (points[1][1]-points[0][1])*(points[1][1]-points[0][1]));
        per = per + Math.sqrt((points[2][0] - points[0][0])*(points[2][0] - points[0][0]) + (points[2][1]-points[0][1])*(points[2][1]-points[0][1]));
        per = per + Math.sqrt((points[2][0] - points[1][0])*(points[2][0] - points[1][0]) + (points[2][1]-points[1][1])*(points[2][1]-points[1][1]));
        System.out.println("Perimeter of the triangle is =" + per);
    }
}
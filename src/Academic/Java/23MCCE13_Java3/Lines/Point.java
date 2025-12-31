

class Point{
    double x; 
    double y;

    Point(double x, double y) {
        this.x=x;
        this.y=y;
    }

    boolean isOnLine(StraightLines l)
    {
        return 0.0==this.x*l.a+this.y*l.b+l.c;
    }
}
class StraightLines{
    double a;
    double b;
    double c;

    StraightLines(double a, double b, double c)
    {
        this.a=a;
        this.b=b;
        this.c=c;
    }

    boolean isParallel(StraightLines l)
    {
        double m1= -this.b/this.a;
        double m2= -l.b/l.a;
        return m1==m2;   
    }

    boolean isPerpendicular(StraightLines l)
    {
        double m1= -this.b/this.a;
        double m2= -l.b/l.a;
        return m1*m2==-1;   
    }

}
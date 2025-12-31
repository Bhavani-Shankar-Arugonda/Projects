#include<stdio.h>
#include<math.h>

double f1(double x) {
    return (x * log10(x)) - 1.2;
}

double f2(double x) {
    return (x * x * x) - (5 * x) + 1;
}

double f3(double x) {
    return x - exp(-x);
}

double f4(double x) {
    return 2 * (x - sin(x)) - 1;
}

double secant(double a,double b,double c,double d)   // c and d are function values whose x is a and b
{
    double f;
    f=a*d-b*c;
    f=f/(d-c);
    return f;
}
int main()
{
   int i;
   double t,a,b,c;

   a=2;
   b=3;
   for(i=0;i<14;i++)
   {
    if(f1(a)*f1(b)<0)
    {
     t=secant(a,b,f1(a),f1(b));
    } 
    if(f1(a)*f1(b)>0 && i!=0)
    {
        t=secant(c,b,f1(c),f1(b));
    }
    c=a;
    a=b;
    b=t;
     if(f1(t)==0)
     {
        break;
     }
     if(f1(a)==f1(b)) 
     {
        break;
     }

   }
   printf("1st root-%0.4f\n",b);
   a=0;
   b=1;
   for(i=0;i<14;i++)
   {
    if(f2(a)*f2(b)<0)
    {
     t=secant(a,b,f2(a),f2(b));
    } 
    if(f2(a)*f2(b)>0 && i!=0)
    {
        t=secant(c,b,f2(c),f2(b));
    }
    c=a;
    a=b;
    b=t;
     if(f2(t)==0)
     {
        break;
     }
    if(f2(a)==f2(b))
     {
        break;
     }

   }
   printf("2nd root-%0.4f\n",t);
   a=0;
   b=1;
   for(i=0;i<14;i++)
   {

    if(f3(a)*f3(b)<0)
    {
     t=secant(a,b,f3(a),f3(b));
    } 
    if(f3(a)*f3(b)>0 && i!=0)
    {
        t=secant(c,b,f3(c),f3(b));
    }
    c=a;
    a=b;
    b=t;
     if(f3(a)==f3(b))
     {
        break;
     }
     if(f3(t)==0)
     {
        break;
     }
     
   }
   printf("3rd root-%0.4f\n",t);
      a=0;
   b=1;
   for(i=0;i<14;i++)
   {

    if(f4(a)*f4(b)<0)
    {
     t=secant(a,b,f4(a),f4(b));
    } 
    if(f4(a)*f4(b)>0 && i!=0)
    {
        t=secant(c,b,f4(c),f4(b));
    }
    c=a;
    a=b;
    b=t;
     if(f4(a)==f4(b))
     {
        break;
     }
     if(f4(t)==0)
     {
        break;
     }
     
   }
   printf("4th root-%0.4f\n",t);
}

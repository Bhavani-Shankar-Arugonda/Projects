#include<stdio.h>
#include<math.h>
double a1[5] = {1, 1, 2, 1, 1};
double f1(double x)
{
  double ans = a1[0]*pow(x, 4) + a1[1] * pow(x, 3) + a1[2]*pow(x, 2) + a1[3] * pow(x, 1) + a1[4];
  return ans;
}
int main()
{
  int n=4;
  double p=0.5;
  double q=0.5;
  double b[n+1];
  for(int i=0;i<8;i++)
  {
   

    b[0]=1;
    b[1]=a1[1]-p;
    for(int i=2;i<=n;i++)
    {
      b[i]=a1[i]-p*b[i-1]-q*b[i-2];
    }
    double r=a1[n-1]-p*b[n-2]-q*b[n-3];
    double s=a1[n]-q*b[n-2];
    double c[n-1];
    c[0]=1;c[1]=b[1]-p;
    for(int i=2;i<=n;i++)
    {
      c[i]=b[i]-p*c[i-1]-q*c[i-2];
    }
    double dp = -(b[n]c[n-3] - b[n-1]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
    double dq = -(b[n-1](c[n-1] - b[n-1]) - b[n]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
 
    p = p+dp;
    q = q+dq;
  }
  printf("%lf/n",q);
  printf("%lf/n",p);
  
  
  int n=4;
  double p=0.1;
  double q=0.1;

  for(int i=0;i<8;i++)
  {
   

    b[0]=1;
    b[1]=a1[1]-p;
    for(int i=2;i<=n;i++)
    {
      b[i]=a1[i]-p*b[i-1]-q*b[i-2];
    }
    double r=a1[n-1]-p*b[n-2]-q*b[n-3];
    double s=a1[n]-q*b[n-2];
    double c[n-1];
    c[0]=1;c[1]=b[1]-p;
    for(int i=2;i<=n;i++)
    {
      c[i]=b[i]-p*c[i-1]-q*c[i-2];
    }
    double dp = -(b[n]c[n-3] - b[n-1]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
    double dq = -(b[n-1](c[n-1] - b[n-1]) - b[n]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
 
    p = p+dp;
    q = q+dq;
  }
  printf("%lf/n",q);
  printf("%lf/n",p);

  int n=4;
  double p=0.5;
  double q=-0.5;

  for(int i=0;i<8;i++)
  {
   

    b[0]=1;
    b[1]=a1[1]-p;
    for(int i=2;i<=n;i++)
    {
      b[i]=a1[i]-p*b[i-1]-q*b[i-2];
    }
    double r=a1[n-1]-p*b[n-2]-q*b[n-3];
    double s=a1[n]-q*b[n-2];
    double c[n-1];
    c[0]=1;c[1]=b[1]-p;
    for(int i=2;i<=n;i++)
    {
      c[i]=b[i]-p*c[i-1]-q*c[i-2];
    }
    double dp = -(b[n]c[n-3] - b[n-1]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
    double dq = -(b[n-1](c[n-1] - b[n-1]) - b[n]*c[n-2])/(c[n-2]*c[n-2] - c[n-3](c[n-1] - b[n-1]));
 
    p = p+dp;
    q = q+dq;
  }
  printf("%lf/n",q);
  printf("%lf/n",p);
}

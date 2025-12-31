#include <stdio.h>
#include<math.h>
void graffe(double a[5])
{
    
    double b[4] = {0};
    b[0] = a[0];
    int i=0;
    for(int j=0; j<4; j++)
    {
        for(int i=1;i<4;i++)
        {
            b[i] = (a[i]*a[i]) - ((2* a[i-1]) * (a[i+1]));
        }
        for(int i=0;i<4;i++)
        {
            a[i] = b[i];
        }
    }
    
    for(int i=1; i<4; i++)
    {
    	double root=exp(pow(2,-4)*(log(b[i])-log(b[i-1])));
	printf("%lf\n",root);
    }
}
int main() 
{
    int n;
            printf("for question 1 answers\n");
            double a[5] ={1,-6,11,-6,0};
             graffe(a);
      
}

//Newton Raphson method

#include<stdio.h>
#include<math.h>

double f1(double x)
{
	return x*log10(x)-1.2;
}

double d1(double x)
{
	return log10(x)+1;
}

double f2(double x)
{
	return x*x*x-5*x+1;
}

double d2(double x)
{
	return 3*x*x-5;
}

double f3(double x)
{
	return x-exp(-x);
}

double d3(double x)
{
	return 1+exp(-x);
}

double f4(double x)
{
	return 2*(x-sin(x))-1;
}

double d4(double x)
{
	return 2*(1-cos(x));
}

double bisection(double (*f)(double),double (*d)(double),double a)
{
        double m;
        for(int i=0; i<14; i++)
        {
                m=a-(f(a)/d(a));
                a=m;
        }
        return a;
}

int main()
{
	// taking function and approximate roots as input
	printf("\n1. f(x)=xlog10(x)-1.2=0\n2. f(x)=x^3-5x+1=0\n3. f(x)=x-e^(-x)=0\n4. f(x)=2(x-sinx)-1=0\n");
	
	int s;	
	double a;		
	double root;
	
	do
	{
		printf("\nEnter The Number Corresponding To The Function Or -1 To Exit : ");
		scanf("%d",&s);
		
		if(s!=-1)
		{
			printf("\nEnter The First Approximate Root : ");
			scanf("%lf",&a);
		}
		
		switch(s)
		{
			case 1:
				root=bisection(f1,d1,a);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 2:
				root=bisection(f2,d2,a);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 3:
				root=bisection(f3,d3,a);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 4:
				root=bisection(f4,d4,a);
				printf("\nRoot = %.4lf \n",root);
				break;
			
		}
	}while(s!=-1);
}

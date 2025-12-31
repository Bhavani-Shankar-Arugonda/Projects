//biscection method

#include<stdio.h>
#include<math.h>

double f1(double x)
{
	return x*log10(x)-1.2;
}

double f2(double x)
{
	return x*x*x-5*x+1;
}

double f3(double x)
{
	return x-exp(-x);
}

double f4(double x)
{
	return 2*(x-sin(x))-1;
}

double bisection(double (*f)(double),double a, double b)
{
	double m;
	if(f(a)*f(b)<0)
	{
		while(b-a>0.00001)
		{
			m=(a+b)/2;
			if(f(a)*f(m)<0)
			{
				b=m;
			}
			else if(f(b)*f(m)<0)
			{
				a=m;
			}
		}
	}
	
	return m;
}

int main()
{
	// taking function and approximate roots as input
	printf("\n1. f(x)=xlog10(x)-1.2=0\n2. f(x)=x^3-5x+1=0\n3. f(x)=x-e^(-x)=0\n4. f(x)=2(x-sinx)-1=0\n");
	
	int s;	
	double a,b;		
	double root;
	
	do
	{
		printf("\nEnter The Number Corresponding To The Function : ");
		scanf("%d",&s);
		
		if(s!=-1)
		{
			printf("\nEnter The First Approximate Root : ");
			scanf("%lf",&a);
			printf("\nEnter The Second Approximate Root : ");
			scanf("%lf",&b);
		}
		
		switch(s)
		{
			case 1:
				root=bisection(f1,a,b);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 2:
				root=bisection(f2,a,b);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 3:
				root=bisection(f3,a,b);
				printf("\nRoot = %.4lf \n",root);
				break;
			case 4:
				root=bisection(f4,a,b);
				printf("\nRoot = %.4lf \n",root);
				break;
			
		}
	}while(s!=-1);
}

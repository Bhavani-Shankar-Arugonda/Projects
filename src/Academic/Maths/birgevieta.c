
#include<stdio.h>
#include<math.h>

double solve(double a[],double p,int n)
{
        double root;
        double b[n],c[n-1];
        for(int k=0; k<10; k++)
        {

                b[0]=a[0];
                for(int i=1; i<n+1; i++)
                {
                        b[i]=(a[i]+(p*b[i-1]));
                }
                c[0]=b[0];
                for(int j=1; j<n; j++)
                {
                        c[j]=(b[j]+(p*c[j-1]));
                }
                root=p-(b[n]/c[n-1]);
                p=root;
        }
        return root;
}

int main()
{
        printf("\n1. f(x)=x^4-3x^3+3x^2-3x+2=0\n2. f(x)=x^5+2x^4+x^3-x^2-2x-1=0\n3. f(x)=x^3-2x-5=0\n4. f(x)=x^4-5x^3+9x^2-7x+2=0\n5. f(x)=x^4-6x^3+13x^2-12x+4\n");

        int s;
        double root;

        do
        {
                printf("\nEnter The Number Corresponding To The Function Or -1 To Exit : ");
                scanf("%d",&s);


                int n;
                double a[n];

                switch(s)
                {
                        case 1:
                                n=4;
                                a[0]=1,a[1]=-3,a[2]=3,a[3]=-3,a[4]=2;
                                //a[n]={1,-3,3,-3,2};
                                root=solve(a,0.5,n);
                                printf("\nRoot = %.4lf \n",root);
                                break;
                        case 2:
                                n=5;
                                a[0]=1,a[1]=2,a[2]=1,a[3]=-1,a[4]=-2,a[5]=-1;
                                //a[n]={1,2,1,-1,-2,-1};
                                root=solve(a,-0.5,n);
                                printf("\nRoot = %.4lf \n",root);
                                break;
                        case 3:
                                n=3;
                                a[0]=1,a[1]=0,a[2]=-2,a[3]=-5;
                                //a[n]={1,0,-2,-5};
                                root=solve(a,2,n);
                                printf("\nRoot = %.4lf \n",root);
                                break;
                        case 4:
                                n=4;
                                a[0]=1,a[1]=-5,a[2]=9,a[3]=-7,a[4]=2;
                                //a[n]={1,-5,9,-7,2};
                                root=solve(a,0.5,n);
                                printf("\nRoot = %.4lf \n",root);
                                break;
                        case 5:
                                n=4;
                                a[0]=1;a[1]=-6,a[2]=13,a[3]=-12,a[4]=4;
                                //a[n]={1,-6,13,-12,4};
                                root=solve(a,1.5,n);
                                printf("\nRoot = %.4lf \n",root);
                                break;
                }
        }while(s!=-1);
}

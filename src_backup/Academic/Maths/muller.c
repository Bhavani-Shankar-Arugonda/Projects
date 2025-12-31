
#include<stdio.h>
#include<math.h>

// Define the functions
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

// muller method implementation
double muller(double (*f)(double), double x0, double x1, double x2) {
    double h1, h2, l2, d2, c2, g2, l, x3;
    double f0 = f(x0);
    double f1 = f(x1);
    double f2 = f(x2);

    // Iterate to find the root
    for (int i = 0; i < 14; i++) {    
        h2 = (x2 - x1);
        h1 = (x1 - x0);
        l2 = (h2 / h1);
        d2 = (1 + l2);
        c2 = l2 * ((l2 * f0) - (d2 * f1) + f2);
        g2 = (l2 * l2 * f0) - (d2 * d2 * f1) + ((l2 + d2) * f2);
        
        // Calculate the step size l
        if (g2 > 0) {    
            l = (-2 * d2 * f2) / (g2 + sqrt((g2 * g2) - (4 * d2 * f2 * c2)));
        } else {
            l = (-2 * d2 * f2) / (g2 - sqrt((g2 * g2) - (4 * d2 * f2 * c2)));
        }

        // Update the value of x3
        x3 = x2 + (l * (x2 - x1));
        
        // Update x0, x1, and x2 for the next iteration
        x0 = x1;
        x1 = x2;
        x2 = x3;      
    }

    return x3;
}

int main() {
    // Taking function and approximate roots as input
    printf("\n1. f(x)=xlog10(x)-1.2=0\n2. f(x)=x^3-5x+1=0\n3. f(x)=x-e^(-x)=0\n4. f(x)=2(x-sinx)-1=0\n");
    
    int s;    
    double root;
    
    do {
        printf("\nEnter The Number Corresponding To The Function Or -1 To Exit : ");
        scanf("%d", &s);
        
        switch (s) {
            case 1:
                root = muller(f1, 1, 2, 3);
                printf("\nRoot = %.4lf \n", root);
                break;
            case 2:
                root = muller(f2, -1, 0, 1);
                printf("\nRoot = %.4lf \n", root);
                break;
            case 3:
                root = muller(f3, -1, 0, 1);
                printf("\nRoot = %.4lf \n", root);
                break;
            case 4:
                root = muller(f4, 0, 1, 2);
                printf("\nRoot = %.4lf \n", root);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (s != -1);

    return 0;
}


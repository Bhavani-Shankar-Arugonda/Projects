#include <stdio.h>
#include <math.h>

// Define the functions
double f1(double x) {
    return x * log10(x) - 1.2;
}

double f2(double x) {
    return x * x * x - 5 * x + 1;
}

double f3(double x) {
    return x - exp(-x);
}

double f4(double x) {
    return 2 * (x - sin(x)) - 1;
}

// Muller method implementation
double muller(double (*f)(double), double x0, double x1, double x2) {
    double f0 = f(x0);
    double f1 = f(x1);
    double f2 = f(x2);
    double h0 = x1 - x0;
    double h1 = x2 - x1;
    double d0 = (f1 - f0) / h0;
    double d1 = (f2 - f1) / h1;
    double a = (d1 - d0) / (h1 + h0);
    double b = a * h1 + d1;
    double c = f2;
    
    for (int i = 0; i < 14; i++) {
        double discriminant = b * b - 4 * a * c;
        if (fabs(discriminant) < 1e-10) {
            printf("Warning: Discriminant is too small, might lead to numerical instability.\n");
            return x2; // Return current approximation
        }
        
        double sqrt_discriminant = sqrt(fabs(discriminant));
        double denom1 = b + sqrt_discriminant;
        double denom2 = b - sqrt_discriminant;
        
        double x3;
        if (fabs(denom1) > fabs(denom2)) {
            x3 = x2 - (2 * c) / denom1;
        } else {
            x3 = x2 - (2 * c) / denom2;
        }
        
        // Update x0, x1, and x2 for the next iteration
        x0 = x1;
        x1 = x2;
        x2 = x3;
        
        // Update function values
        f0 = f(x0);
        f1 = f(x1);
        f2 = f(x2);
        h0 = x1 - x0;
        h1 = x2 - x1;
        d0 = (f1 - f0) / h0;
        d1 = (f2 - f1) / h1;
        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        c = f2;
    }

    return x2;
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


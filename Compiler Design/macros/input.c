#include<stdio.h>

#define PI 3.14
#define SQUARE(x) x*x
#define ADD(a,b) a+b
#define max 5
#define min(y)  y*y

int main() {
    float area = PI * SQUARE(5);
    int sum = ADD(3,4);
    int arr[max];
    int a[min(5)];
    float b= max * min(10);
    return 0;
}
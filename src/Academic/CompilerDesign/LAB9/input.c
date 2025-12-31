#include <stdio.h>
#include <math.h>

#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    printf("%d\n", SQUARE(5));
    printf("%d\n", MAX(10, 20));
    return 0;
}
/*
*  Group Information :
*  23MCCE05 - vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program takes a number in charecters and tells if the number is divisible by 3 or not.
*/

#include <stdio.h>

void fromA(char *state, int input) {
    if (input % 3 == 0)
        *state = 'A';
    else if (input % 3 == 1)
        *state = 'B';
    else
        *state = 'C';
}

void fromB(char *state, int input) {
    if (input % 3 == 0)
        *state = 'B';
    else if (input % 3 == 1)
        *state = 'C';
    else
        *state = 'A';
}

void fromC(char *state, int input) {
    if (input % 3 == 0)
        *state = 'C';
    else if (input % 3 == 1)
        *state = 'A';
    else
        *state = 'B';
}

void transition(char* state, int input) {
    if (*state == 'A') {
        fromA(state, input);
    } else if (*state == 'B') {
        fromB(state, input);
    } else if (*state == 'C') {
        fromC(state, input);
    }
}

int main() {
    char state = 'A';

    char number[100];
    printf("Enter a number: ");
    scanf("%s", number);

    int i = 0;
    while (number[i] != '\0') {
        int digit = number[i] - '0';//string into integer
        transition(&state, digit);
        i++;
    }

    if (state == 'A') {
        printf("This number is divisible by 3.\n");
    } else {
        printf("This number is not divisible by 3.\n");
    }

    return 0;
}

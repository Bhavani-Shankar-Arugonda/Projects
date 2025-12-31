/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program implements PDF for EQUAL
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int sp = 0;              
char pdastore[100];      

void pushSymbol(char sym) {
    if (sp < 100) {
        pdastore[sp] = sym;
        sp++;
    } else {
        printf("Stack overflow!\n");
    }
}


char popSymbol() {
    sp--;
    return pdastore[sp];
}


void clearStack() {
    sp = 0;
}

int processAlphaVersion(const char inputStr[100]) {
    clearStack();
    bool hasSwitched = false;
    for (int i = 0; i < (int)strlen(inputStr); i++) {
        if (inputStr[i] == 'a') {
            if (hasSwitched) {
                return -1;
            }
            pushSymbol('A');
        } else if (inputStr[i] == 'b') {
            hasSwitched = true;
            char ch = popSymbol();
            if (ch != 'A') {
                return -1;
            }
        } else {
            return -1;
        }
    }
    return (sp == 0) ? 0 : -1;
}

int processBetaVersion(const char inputStr[100]) {
    clearStack();
    bool hasSwitched = false;
    for (int i = 0; i < (int)strlen(inputStr); i++) { 
        if (inputStr[i] == 'b') {
            if (hasSwitched) {
                return -1;
            }
            pushSymbol('B');
        } else if (inputStr[i] == 'a') {
            char ch = popSymbol();
            hasSwitched = true;
            if (ch != 'B') {
                return -1;
            }
        } else {
            return -1;
        }
    }
    return (sp == 0) ? 0 : -1;
}

int processZeroVersion(const char inputStr[100]) {
    clearStack();
    bool hasSwitched = false;
    for (int i = 0; i < (int)strlen(inputStr); i++) {
        if (inputStr[i] == '0') {
            if (hasSwitched) {
                return -1;
            }
            pushSymbol('0');
        } else if (inputStr[i] == '1') {
            char ch = popSymbol();
            hasSwitched = true;
            if (ch != '0') {
                return -1;
            }
        } else {
            return -1;
        }
    }
    return (sp == 0) ? 0 : -1;
}

int processOneVersion(const char inputStr[100]) {
    clearStack();
    bool hasSwitched = false;
    for (int i = 0; i < (int)strlen(inputStr); i++) {
        if (inputStr[i] == '1') {
            if (hasSwitched) {
                return -1;
            }
            pushSymbol('1');
        } else if (inputStr[i] == '0') {
            char ch = popSymbol();
            hasSwitched = true;
            if (ch != '1') {
                return -1;
            }
        } else {
            return -1;
        }
    }
    return (sp == 0) ? 0 : -1;
}

bool isEqualAlphaLanguage(const char inp[100]) {
    if (strlen(inp) == 0)
        return true;
    
    int resAlpha = processAlphaVersion(inp);
    int resBeta  = processBetaVersion(inp);
    return (resAlpha == 0 || resBeta == 0);
}

bool isEqualBinaryLanguage(const char inp[100]) {
    if (strlen(inp) == 0)
        return true;
    
    int resZero = processZeroVersion(inp);
    int resOne  = processOneVersion(inp);
    return (resZero == 0 || resOne == 0);
}

int main() {
    int choice;
    printf("Choose an option:\n");
    printf("Enter 1 for binary input or 2 for alphabet input: ");
    scanf("%d", &choice);
    
    char userInput[100];
    bool accepted = false;
    
    if (choice == 1) {
        printf("Input the binary string: ");
        scanf("%s", userInput);
        accepted = isEqualBinaryLanguage(userInput);
    } else if (choice == 2) {
        printf("Input the alphabet string: ");
        scanf("%s", userInput);
        accepted = isEqualAlphaLanguage(userInput);
    } else {
        return 0;
    }
    
    if (accepted) {
        printf("The provided string is accepted under the EQUAL language.\n");
    } else {
        printf("The provided string is not accepted by the EQUAL language.\n");
    }
    
    return 0;
}

/*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program takes CFG and removes lambda productions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 100

const char LAMBDA = 'e';

typedef struct Production {
    char LHS;
    char RHS[MAX_SYMBOLS][MAX_SYMBOLS];
    int num_RHS;
} Production;

Production productions[MAX_PRODUCTIONS];
int num_productions = 0;

void printProductions() {
    for (int i = 0; i < num_productions; i++) {
        printf("%c -> ", productions[i].LHS);
        for (int j = 0; j < productions[i].num_RHS; j++) {
            if (strcmp(productions[i].RHS[j], "") == 0) {
                printf("%c", LAMBDA);
            } else {
                printf("%s", productions[i].RHS[j]);
            }
            if (j != productions[i].num_RHS - 1) {
                printf("|");
            }
        }
        printf("\n");
    }
}

int contains_char(const char* str, char ch) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == ch) return i;
    }
    return -1;
}

void delete_production(int i, int j) {
    for (int k = j; k < productions[i].num_RHS - 1; k++) {
        strcpy(productions[i].RHS[k], productions[i].RHS[k + 1]);
    }
    productions[i].num_RHS--;
}

void remove_lambda() {
    int derives_lambda[MAX_PRODUCTIONS] = {0};

    for (int i = 0; i < num_productions; i++) {
        for (int j = 0; j < productions[i].num_RHS; j++) {
            if (strcmp(productions[i].RHS[j], "e") == 0) {
                delete_production(i, j);
                derives_lambda[i] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < num_productions; i++) {
        if (derives_lambda[i]) {
            char nullable = productions[i].LHS;
            for (int j = 0; j < num_productions; j++) {
                int added = 0;
                int original_count = productions[j].num_RHS;

                for (int k = 0; k < original_count; k++) {
                    char* rhs = productions[j].RHS[k];
                    int pos = contains_char(rhs, nullable);

                    if (pos != -1) {
                        int len = strlen(rhs);
                        if (len == 1 && rhs[0] == nullable) continue;

                        char new_rhs[MAX_SYMBOLS];
                        int index = 0;
                        for (int m = 0; m < len; m++) {
                            if (m != pos) new_rhs[index++] = rhs[m];
                        }
                        new_rhs[index] = '\0';

                        int exists = 0;
                        for (int t = 0; t < productions[j].num_RHS; t++) {
                            if (strcmp(productions[j].RHS[t], new_rhs) == 0) {
                                exists = 1;
                                break;
                            }
                        }
                        if (!exists && strlen(new_rhs) > 0) {
                            strcpy(productions[j].RHS[productions[j].num_RHS++], new_rhs);
                            added = 1;
                        }
                    }
                }
                if (added) j--;
            }
        }
    }
}

int main() {
    //test case
    //Input 
    // S-XYX   
    // X-0X|e
    // Y-1Y|e

    // output
    // S -> XYX|YX|Y|XX|X
    // X -> 0X|0
    // Y -> 1Y|1
    char line[1000];
    printf("Enter the input production in this way S-AB|e and to stop giving input put '.'\n");

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '.') break;

        char* LHS = strtok(line, "-");
        char* RHS_part = strtok(NULL, "\n");

        if (!LHS || !RHS_part) continue;

        productions[num_productions].LHS = LHS[0];
        productions[num_productions].num_RHS = 0;

        char* symbol = strtok(RHS_part, "|");
        while (symbol != NULL) {
            strcpy(productions[num_productions].RHS[productions[num_productions].num_RHS++], symbol);
            symbol = strtok(NULL, "|");
        }
        num_productions++;
    }

    printf("Original productions:\n");
    printProductions();

    remove_lambda();

    printf("\nProductions after removing lambda productions:\n");
    printProductions();

    return 0;
}
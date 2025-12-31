/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program converts context free grammar to cnf
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RULES        100
#define MAX_PRODUCTIONS   20
#define MAX_LENGTH        30
#define MAX_SYMBOLS       26

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_LENGTH];
    int  count;
} Rule;


void printGrammar(Rule R[], int n, const char *title) {
    printf("\n%s:\n", title);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < R[i].count; j++) {
            printf("%c -> %s\n", R[i].lhs, R[i].rhs[j]);
        }
    }
}

bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

char generateNonTerminal(Rule R[], int n) {
    bool used[MAX_SYMBOLS] = {false};
    for (int i = 0; i < n; i++)
        used[R[i].lhs - 'A'] = true;
    for (int i = 0; i < MAX_SYMBOLS; i++)
        if (!used[i]) return 'A' + i;
    return 'X';
}

void addProduction(Rule R[], int *n, char A, const char *rhs) {
    int idx = -1;
    for (int i = 0; i < *n; i++) {
        if (R[i].lhs == A) { idx = i; break; }
    }
    if (idx < 0) {
        idx = (*n)++;
        R[idx].lhs = A;
        R[idx].count = 0;
    }
    for (int j = 0; j < R[idx].count; j++)
        if (strcmp(R[idx].rhs[j], rhs) == 0)
            return;
    if (R[idx].count < MAX_PRODUCTIONS)
        strncpy(R[idx].rhs[R[idx].count++], rhs, MAX_LENGTH);
}

void computeNullable(Rule R[], int n, bool nullable[]) {
    memset(nullable, 0, MAX_SYMBOLS);
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < n; i++) {
            int A = R[i].lhs - 'A';
            if (nullable[A]) continue;
            for (int j = 0; j < R[i].count; j++) {
                const char *s = R[i].rhs[j];
                if (strcmp(s, "e") == 0) {
                    nullable[A] = true;
                    changed = true;
                    break;
                }
                bool all = true;
                for (int k = 0; s[k]; k++) {
                    char c = s[k];
                    if (!isNonTerminal(c) || !nullable[c - 'A']) {
                        all = false;
                        break;
                    }
                }
                if (all && s[0] != '\0') {
                    nullable[A] = true;
                    changed = true;
                    break;
                }
            }
        }
    }
}

void removeUnitProductions(Rule R[], int *n) {
    bool unit[MAX_SYMBOLS][MAX_SYMBOLS] = {{false}};
    for (int i = 0; i < *n; i++) {
        int A = R[i].lhs - 'A';
        unit[A][A] = true;
        for (int j = 0; j < R[i].count; j++) {
            const char *s = R[i].rhs[j];
            if (strlen(s)==1 && isNonTerminal(s[0]))
                unit[A][s[0]-'A'] = true;
        }
    }
    for (int k = 0; k < MAX_SYMBOLS; k++)
    for (int i = 0; i < MAX_SYMBOLS; i++)
    for (int j = 0; j < MAX_SYMBOLS; j++)
        if (unit[i][k] && unit[k][j]) unit[i][j] = true;

    Rule T[MAX_RULES]; int tn = 0;
    for (int i = 0; i < *n; i++) {
        char A = R[i].lhs;
        for (int j = 0; j < R[i].count; j++) {
            const char *s = R[i].rhs[j];
            if (!(strlen(s)==1 && isNonTerminal(s[0])))
                addProduction(T, &tn, A, s);
        }
    }
    for (int A = 0; A < MAX_SYMBOLS; A++) {
        for (int B = 0; B < MAX_SYMBOLS; B++) if (unit[A][B] && A!=B) {
            char X = 'A' + A, Y = 'A' + B;
            for (int i = 0; i < *n; i++) if (R[i].lhs==Y) {
                for (int j = 0; j < R[i].count; j++) {
                    const char *s = R[i].rhs[j];
                    if (!(strlen(s)==1 && isNonTerminal(s[0])))
                        addProduction(T, &tn, X, s);
                }
            }
        }
    }
    memcpy(R, T, tn * sizeof(Rule));
    *n = tn;
}

void binarizeProductions(Rule R[], int *n) {
    int orig = *n;
    for (int i = 0; i < orig; i++) {
        char A = R[i].lhs;
        for (int j = 0; j < R[i].count; j++) {
            while (strlen(R[i].rhs[j]) > 2) {
                char nv = generateNonTerminal(R, *n);
                char a = R[i].rhs[j][0], b = R[i].rhs[j][1];
                addProduction(R, n, nv, (char[]){a,b,'\0'});
                memmove(&R[i].rhs[j][1], &R[i].rhs[j][2], strlen(&R[i].rhs[j][2])+1);
                R[i].rhs[j][0] = nv;
            }
        }
    }
}

void separateTerminals(Rule R[], int *n) {
    int orig = *n;
    for (int i = 0; i < orig; i++) {
        char A = R[i].lhs;
        for (int j = 0; j < R[i].count; j++) {
            const char *s = R[i].rhs[j];
            if (strlen(s)==2) {
                for (int k = 0; k < 2; k++) {
                    if (!isNonTerminal(s[k])) {
                        char nv = '\0';
                        for (int x=0; x<*n; x++) {
                            if (R[x].count==1 && R[x].rhs[0][0]==s[k] && isNonTerminal(R[x].lhs)) {
                                nv = R[x].lhs; break;
                            }
                        }
                        if (!nv) nv = generateNonTerminal(R, *n);
                        addProduction(R, n, nv, (char[]){s[k],'\0'});
                        ((char*)R[i].rhs[j])[k] = nv;
                    }
                }
            }
        }
    }
}

void generateCombinations(Rule R[], int *n, char A, const char *rhs, bool nullable[]) {
    int L = strlen(rhs);
    int pos[MAX_LENGTH], pc = 0;
    for (int i = 0; i < L; i++)
        if (isNonTerminal(rhs[i]) && nullable[rhs[i] - 'A'])
            pos[pc++] = i;
    for (int mask = 1; mask < (1 << pc); mask++) {
        char buf[MAX_LENGTH];
        int b = 0;
        for (int i = 0; i < L; i++) {
            bool drop = false;
            for (int x = 0; x < pc; x++)
                if (pos[x] == i && (mask & (1 << x))) { drop = true; break; }
            if (!drop) buf[b++] = rhs[i];
        }
        buf[b] = '\0';
        if (b > 0) addProduction(R, n, A, buf);
    }
}

void removeEpsilonProductions(Rule R[], int *n, char *start) {
    bool nullable[MAX_SYMBOLS];
    computeNullable(R, *n, nullable);

    Rule T[MAX_RULES]; int tn = 0;
    for (int i = 0; i < *n; i++) {
        char A = R[i].lhs;
        for (int j = 0; j < R[i].count; j++) {
            const char *s = R[i].rhs[j];
            if (strcmp(s, "e") == 0) continue;
            addProduction(T, &tn, A, s);
            generateCombinations(T, &tn, A, s, nullable);
        }
    }
    if (nullable[*start - 'A']) {
        char S2 = generateNonTerminal(T, tn);
        addProduction(T, &tn, S2, (char[]){*start, '\0'});
        *start = S2;
    }
    memcpy(R, T, tn * sizeof(Rule));
    *n = tn;
}

int main() {
    Rule R[MAX_RULES];
    int  n;
    char start;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); 

    printf("Enter productions one by one (use 'e' for ε), in the form A-  Aa |B|...:\n");
    char line[256];
    for (int i = 0; i < n; i++) {
        printf("Production %d: ", i+1);
        if (!fgets(line, sizeof line, stdin)) {
            fprintf(stderr, "Error reading production %d\n", i+1);
            exit(1);
        }
        line[strcspn(line, "\n")] = '\0';
        R[i].lhs   = line[0];
        if (i == 0) start = R[i].lhs;
        R[i].count = 0;

        char *p = line + 2;  
        char *tok = strtok(p, "|");
        while (tok) {
            strncpy(R[i].rhs[R[i].count], tok, MAX_LENGTH-1);
            R[i].rhs[R[i].count][MAX_LENGTH-1] = '\0';
            R[i].count++;
            tok = strtok(NULL, "|");
        }
    }

    printGrammar(R, n, "Input CFG Grammar");

    removeEpsilonProductions(R, &n, &start);
    printGrammar(R, n, "After Removing ε-Productions");

    removeUnitProductions(R, &n);
    printGrammar(R, n, "After Removing Unit Productions");

    binarizeProductions(R, &n);
    printGrammar(R, n, "After Binarization");

    separateTerminals(R, &n);
    printGrammar(R, n, "Final CNF Grammar");

    return 0;
}

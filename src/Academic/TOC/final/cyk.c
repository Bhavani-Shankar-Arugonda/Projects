/*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :  Cocke–Younger–Kasami(cyk) algorithm
*/

#include<stdio.h>
#include<string.h>

#define Max 100

typedef struct {
    char LHS;
    char RHS[2]; //in cnf RHS will have max no. of if it has 2 non-terminal symbols
} productionRules;

typedef struct {
    char cell[Max];
} element;

void cyk(productionRules p[Max], int n,char str[Max]){

    int len = strlen(str);
    element table[len][len];

    //1st phase : filling the string in the table
    for(int i=0 ; i < len ;i++){
        int pos = 0;
        for(int j=0 ; j<n ;j++){
            if(p[j].RHS[1] == '\0' && str[i] == p[j].RHS[0]){
                table[0][i].cell[pos++] = p[j].LHS;
                
            }
        }
        table[0][i].cell[pos] = '\0';
    }

    // 2nd phase : filling the remaining table
    for (int j = 1; j < len; j++) {
        for (int i = 0; i < len - j; i++) {
            char temp[Max];
            int pos = 0;
            for (int k = 0; k < j; k++) {
                for (int r = 0; r < n; r++) {
                    if (p[r].RHS[1] != '\0') {
                        char C = p[r].LHS;
                        char D = p[r].RHS[0];
                        char E = p[r].RHS[1];
                        if (strchr(table[k][i].cell, D) != NULL && strchr(table[j - k - 1][i + k + 1].cell, E) != NULL) {
                            int found = 0;
                            for (int m = 0; m < pos; m++) {
                                if (temp[m] == C) {
                                    found = 1;
                                    break;
                                }
                            }
                            if (!found) {
                                temp[pos++] = C;
                            }
                        }
                    }
                }
            }
            temp[pos] = '\0';
            strcpy(table[j][i].cell, temp);
        }
    }

    if (strchr(table[len - 1][0].cell, 'S') != NULL) {
        printf("This string belongs to this grammar.\n");
    } else {
        printf("This string doesn't belongs to this grammar.\n");
    }

}

int main(){

    //Below commented code is for manual input of productionRules
    // printf("Enter the no. of production rules for the CNF\n");
    // int n; 
    // scanf("%d",&n);

    // productionRules p[Max];
    // for( int i=0;i<n;i++ ){
    //     printf("Enter the production rule\n");
    //     scanf(" %c %s", &p[i].LHS, p[i].RHS);
    //     printf("%c -> %s\n", p[i].LHS, p[i].RHS);
    // }

    int n = 5;
    productionRules p[Max] = {
        { .LHS = 'S', .RHS = "AB"},//ab, bbb, aab and abbb belongs to this grammer
        { .LHS = 'A', .RHS = "BB"},
        { .LHS = 'A', .RHS = "a"},//a, b, aa and ba  doesn't belongs to this grammer
        { .LHS = 'B', .RHS = "AB"},
        { .LHS = 'B', .RHS = "b"},
    };

    char str[Max];
    printf("Enter the Input string : ");
    scanf("%s",str);

    cyk(p, n, str);

    return 0;
}
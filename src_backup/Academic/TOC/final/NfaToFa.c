/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program converts NFA to FA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10

typedef struct {
    int states[MAX_STATES];
    int count;
} DFAState;

int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int nfa_states, nfa_symbols;
DFAState dfa_states[100];
int dfa_trans[100][MAX_SYMBOLS];
int dfa_state_count = 0;

int findDFAState(DFAState state) {
    for (int i = 0; i < dfa_state_count; i++) {
        if (state.count == dfa_states[i].count) {
            int match = 1;
            for (int j = 0; j < state.count; j++) {
                if (state.states[j] != dfa_states[i].states[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) return i;
        }
    }
    return -1;
}

void getClosure(int state, int* closure, int* closure_size, int* visited) {
    if (visited[state]) return;  
    visited[state] = 1;
    closure[(*closure_size)++] = state;

    for (int i = 0; i < nfa_states; i++) {
        if (nfa[state][0][i]) {  
            getClosure(i, closure, closure_size, visited);
        }
    }
}

void NFAtoDFA() {
    int closure[MAX_STATES];
    int closure_size;
    int visited[MAX_STATES];

    memset(visited, 0, sizeof(visited));
    closure_size = 0;
    getClosure(0, closure, &closure_size, visited);

    memcpy(dfa_states[0].states, closure, sizeof(int) * closure_size);
    dfa_states[0].count = closure_size;
    dfa_state_count = 1;

    for (int i = 0; i < dfa_state_count; i++) {
        for (int sym = 1; sym < nfa_symbols; sym++) {
            DFAState newState = {0};
            int newStateSize = 0;

            for (int j = 0; j < dfa_states[i].count; j++) {
                int curr_nfa_state = dfa_states[i].states[j];

                for (int k = 0; k < nfa_states; k++) {
                    if (nfa[curr_nfa_state][sym][k]) {
                        memset(visited, 0, sizeof(visited));
                        closure_size = 0;
                        getClosure(k, closure, &closure_size, visited);

                        for (int l = 0; l < closure_size; l++) {
                            int found = 0;
                            for (int m = 0; m < newStateSize; m++) {
                                if (newState.states[m] == closure[l]) {
                                    found = 1;
                                    break;
                                }
                            }
                            if (!found) {
                                newState.states[newStateSize++] = closure[l];
                            }
                        }
                    }
                }
            }

            newState.count = newStateSize;

            for (int a = 0; a < newStateSize; a++) {
                for (int b = a + 1; b < newStateSize; b++) {
                    if (newState.states[a] > newState.states[b]) {
                        int temp = newState.states[a];
                        newState.states[a] = newState.states[b];
                        newState.states[b] = temp;
                    }
                }
            }

            int existingState = findDFAState(newState);
            if (existingState == -1 && newStateSize > 0) {
                memcpy(&dfa_states[dfa_state_count], &newState, sizeof(DFAState));
                dfa_trans[i][sym] = dfa_state_count;
                dfa_state_count++;
            } else if (newStateSize > 0) {
                dfa_trans[i][sym] = existingState;
            } else {
                dfa_trans[i][sym] = -1;  
            }
        }
    }
}

int main() {
    printf("Enter number of states in NFA: ");
    scanf("%d", &nfa_states);

    printf("Enter number of symbols (including epsilon as 0): ");
    scanf("%d", &nfa_symbols);

    printf("Enter NFA transition table (1 for transition, 0 for no transition):\n");
    for (int i = 0; i < nfa_states; i++) {
        for (int j = 0; j < nfa_symbols; j++) {
            for (int k = 0; k < nfa_states; k++) {
                printf("Transition from state %d to state %d for symbol %d: ", i, k, j);
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    NFAtoDFA();

    printf("\nResulting DFA:\n");
    printf("Number of states: %d\n", dfa_state_count);
    printf("\nTransition Table:\n");

    printf("State\t");
    for (int i = 1; i < nfa_symbols; i++) {
        printf("Symbol %d\t", i);
    }
    printf("\n");

    for (int i = 0; i < dfa_state_count; i++) {
        printf("{");
        for (int j = 0; j < dfa_states[i].count; j++) {
            printf("%d", dfa_states[i].states[j]);
            if (j < dfa_states[i].count - 1) printf(",");
        }
        printf("}\t");

        for (int j = 1; j < nfa_symbols; j++) {
            if (dfa_trans[i][j] == -1) {
                printf("-\t");
            } else {
                printf("{");
                for (int k = 0; k < dfa_states[dfa_trans[i][j]].count; k++) {
                    printf("%d", dfa_states[dfa_trans[i][j]].states[k]);
                    if (k < dfa_states[dfa_trans[i][j]].count - 1) printf(",");
                }
                printf("}\t");
            }
        }
        printf("\n");
    }

    return 0;
}

/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program takes Minimize the states of FA
*/
#include <stdio.h>
#include <stdbool.h> 

#define MAX_STATES 100  
#define MAX_INPUT 26

int numberOfStates;
int noOfInput;
int initialState;
int noOfFinalStates;
int transition[MAX_STATES][MAX_INPUT];
int finalStates[MAX_INPUT];
char inputs[MAX_INPUT];
int partitions = 2;  
int partitonedFA[2 * MAX_STATES]; 

void removeUnreachableStates() {
    bool visited[MAX_STATES] = {false};

    visited[initialState] = true; 
    for (int i = 0; i < numberOfStates; i++) {
        for (int j = 0; j < noOfInput; j++) {
            int nextState = transition[i][j];
            if (nextState >= 0 && nextState < numberOfStates) {
                visited[nextState] = true;
            }
        }
    }

    for (int i = 0; i < numberOfStates; i++) {
        if (!visited[i]) {
            for (int j = 0; j < noOfInput; j++) {
                transition[i][j] = -1;  
            }
        }
    }
}

void initialPartitioning() {
    for (int i = 0; i < numberOfStates; i++) {
        if (transition[i][0] == -1) {  
            partitonedFA[2 * i] = -1;
            partitonedFA[2 * i + 1] = -1;
            continue;
        } else {
            partitonedFA[2 * i] = i;
        }

        bool isFinal = false;
        for (int j = 0; j < noOfFinalStates; j++) {
            if (i == finalStates[j]) {
                isFinal = true;
                break;
            }
        }
        partitonedFA[2 * i + 1] = isFinal ? 2 : 1;  
    }
}

void refinementOfPartitioning() {
    bool changed;
    int iteration = 0;  
    int maxIterations = numberOfStates * 5; 

    do {
        changed = false;
        iteration++;

        if (iteration > maxIterations) {
            printf("Refinement process exceeded safe iterations limit! Exiting...\n");
            break;
        }

        int newPartitions[2 * numberOfStates];

        for (int i = 0; i < 2 * numberOfStates; i += 2) {
            if (partitonedFA[i] == -1) {
                newPartitions[i] = -1;
                newPartitions[i + 1] = -1;
                continue;
            }

            int currentPartition = partitonedFA[i + 1];
            int newPartition = currentPartition;

            for (int j = 0; j < noOfInput; j++) {
                int nextState = transition[partitonedFA[i]][j];

                if (nextState != -1) {
                    int nextPartition = partitonedFA[2 * nextState + 1];

                    if (nextPartition != currentPartition) {
                        if (newPartition == currentPartition) {
                            newPartition = partitions++;
                            changed = true;
                        }
                    }
                }
            }

            newPartitions[i] = partitonedFA[i];
            newPartitions[i + 1] = newPartition;
        }

        for (int i = 0; i < 2 * numberOfStates; i++) {
            partitonedFA[i] = newPartitions[i];
        }

    } while (changed);  
}
  

void printMinimizedDFA() {
    printf("\n--- Minimized DFA ---\n");

    printf("\nSet of States Q = { ");
    for (int i = 0; i < 2 * numberOfStates; i += 2) {
        if (partitonedFA[i] != -1) {
            printf("q%d ", partitonedFA[i]);
        }
    }
    printf("}\n");

    printf("\nAlphabet Σ = { ");
    for (int i = 0; i < noOfInput; i++) {
        printf("%c ", inputs[i]);
    }
    printf("}\n");

    printf("\nInitial State: q%d\n", initialState);

    printf("\nFinal States F = { ");
    for (int i = 0; i < noOfFinalStates; i++) {
        printf("q%d ", finalStates[i]);
    }
    printf("}\n");

    printf("\nTransition Function δ:\n");
    for (int i = 0; i < 2 * numberOfStates; i += 2) {
        if (partitonedFA[i] != -1) {
            printf("δ(q%d) -> ", partitonedFA[i]);
            for (int j = 0; j < noOfInput; j++) {
                int nextState = transition[partitonedFA[i]][j];
                if (nextState != -1) {
                    printf("(%c → q%d) ", inputs[j], partitonedFA[2 * nextState]);
                } else {
                    printf("(%c → -) ", inputs[j]); 
                }
            }
            printf("\n");
        }
    }
    printf("\n------------------------------------\n");
}

int main() {
    printf("Enter the number of states: ");
    scanf("%d", &numberOfStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &noOfInput);

    printf("Enter input symbols (e.g. a b): ");
    for (int i = 0; i < noOfInput; i++) {
        scanf(" %c", &inputs[i]);
    }

    printf("\nEnter transitions:\n");
    for (int state = 0; state < numberOfStates; state++) {
        for (int input = 0; input < noOfInput; input++) {
            printf("δ(q%d, %c) = q", state, inputs[input]);
            scanf("%d", &transition[state][input]);

            while (transition[state][input] < 0 || transition[state][input] >= numberOfStates) {
                printf("INVALID INPUT. Please enter a valid state (0-%d): ", numberOfStates - 1);
                scanf("%d", &transition[state][input]);
            }
        }
    }

    printf("Enter initial state: ");
    scanf("%d", &initialState);

    printf("Enter number of final states: ");
    scanf("%d", &noOfFinalStates);
    printf("Enter final states: ");
    for (int i = 0; i < noOfFinalStates; i++) {
        scanf("%d", &finalStates[i]);
    }

    printf("\nStarting DFA Minimization...\n");

    removeUnreachableStates();
    printf("Unreachable states removed!\n");

    initialPartitioning();
    printf("Initial partitioning completed!\n");

    refinementOfPartitioning();
    printf("Refinement of partitioning completed!\n");

    printMinimizedDFA();
    printf("DFA minimization completed!\n");

    return 0;
}

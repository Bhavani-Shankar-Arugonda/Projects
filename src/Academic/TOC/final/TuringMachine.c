/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program implements turing machine
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1000

typedef struct {
    char tape[MAX_LEN];
    int head;
    int current_state;
} TuringMachine;

void print_state(int state) {
    printf("q%d", state);
}

void print_configuration(TuringMachine *tm) {
    printf("Tape: ");
    for(int i = 0; tm->tape[i]; i++) {
        if(i == tm->head) {
            printf("[%c]", tm->tape[i]);
        } else {
            printf("%c", tm->tape[i]);
        }
    }
    printf("\nCurrent state: ");
    print_state(tm->current_state);
    printf("\nHead position: %d\n\n", tm->head);
}

bool run_turing_machine(TuringMachine *tm) {
    tm->current_state = 0; 
    tm->head = 0;
    
    printf("Initial configuration:\n");
    print_configuration(tm);
    
    while(true) {
        switch(tm->current_state) {
            case 0: 
                if(tm->tape[tm->head] == 'a') {
                    tm->tape[tm->head] = 'X';
                    tm->head++;
                    tm->current_state = 1;  
                    printf("Marked 'a' and moving right to find 'b'\n");
                    print_configuration(tm);
                } else if(tm->tape[tm->head] == 'X'||tm->tape[tm->head] == 'Y'||tm->tape[tm->head] == 'Z') {
                    tm->head++;
                    printf("Skipping marked symbol\n");
                    print_configuration(tm);
                } else {
                    
                    
                    tm->current_state = 5;  
                }
                break;
                
            case 1: 
                if(tm->tape[tm->head] == 'a' || tm->tape[tm->head] == 'Y') {
                    tm->head++;
                } else if(tm->tape[tm->head] == 'b') {
                    tm->tape[tm->head] = 'Y';
                    tm->head++;
                    tm->current_state = 2;  
                    printf("Found and marked 'b', moving right to find 'c'\n");
                    print_configuration(tm);
                } else {
                    tm->current_state = 4; 
                }
                break;
                
            case 2: 
                if(tm->tape[tm->head] == 'b'||tm->tape[tm->head] == 'Z') {
                    tm->head++;
                } else if(tm->tape[tm->head] == 'c') {
                    tm->tape[tm->head] = 'Z';
                    tm->head = 0;
                    tm->current_state = 0;  
                    printf("Found and marked 'c', moving back to start\n");
                    print_configuration(tm);
                } else {
                    tm->current_state = 4;  
                }
                break;
                
            case 4: 
                printf("Reached reject state q4\n");
                return false;
                
            case 5: 
                if(tm->tape[tm->head] == '\0') {
                    
                   

                   bool all_marked = true;
                    for(int i = 0; tm->tape[i]; i++) {
                        if(tm->tape[i] != 'X' && tm->tape[i] != 'Y' && 
                           tm->tape[i] != 'Z') {
                            printf("%c",tm->tape[i]);
                            all_marked = false;
                            break;
                        }
                    }
                    printf("Reached accept state q5\n");
                    return all_marked;
                }
            
               return false;
        }
    }
}

int main() {
    TuringMachine tm;
    
    printf("State description:\n");
    printf("q0: Initial state (scanning for 'a')\n");
    printf("q1: Looking for 'b' state\n");
    printf("q2: Looking for 'c' state\n");
    printf("q4: Reject state\n");
    printf("q5: Accept state\n\n");
    
    printf("Enter string (format: a's followed by b's followed by c's): ");
    scanf("%s", tm.tape);
    
    if(run_turing_machine(&tm)) {
        printf("Accepted: String is of the form a^n b^n c^n\n");
    } else {
        printf("Rejected: String is not of the form a^n b^n c^n\n");
    }
    
    return 0;
}

/*
*
*  Group Information :
*  23MCCE05 - Vinith
*  23MCCE11 - Aravind
*  23MCCE13 - Bhavani Shankar
*/

/*
* Program Description :
* This program removes all het useless symbols from a CFG
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_SYMBOLS 100
#define MAX_LENGTH 100

typedef struct 
{
    char lhs;
    char rhs[MAX_LENGTH];
} Production;

typedef struct 
{
    Production rules[MAX_RULES];
    int num_rules;
    char terminals[MAX_SYMBOLS];
    int num_terminals;
    char non_terminals[MAX_SYMBOLS];
    int num_non_terminals;
    char start_symbol;
} CFG;

int isTerminal(char symbol, CFG* cfg) 
{
    for(int i = 0; i < cfg->num_terminals; i++) 
    {
        if(cfg->terminals[i] == symbol)
            return 1;
    }
    return 0;
}

int isNonTerminal(char symbol, CFG* cfg) 
{
    for(int i = 0; i < cfg->num_non_terminals; i++) 
    {
        if(cfg->non_terminals[i] == symbol)
            return 1;
    }
    return 0;
}

void findGeneratingSymbols(CFG* cfg, int* generating) 
{
    int changed;
    for(int i = 0; i < cfg->num_terminals; i++)
    {
        generating[cfg->terminals[i]] = 1;
    }
    do {
        changed = 0;
        for(int i = 0; i < cfg->num_rules; i++) 
        {
            char lhs = cfg->rules[i].lhs;
            if(!generating[lhs]) 
            {
                int can_generate = 1;
                for(int j = 0; cfg->rules[i].rhs[j] != '\0'; j++) 
                {
                    if(!generating[cfg->rules[i].rhs[j]]) 
                    {
                        can_generate = 0;
                        break;
                    }
                }
                if(can_generate) 
                {
                    generating[lhs] = 1;
                    changed = 1;
                }
            }
        }
    } while(changed);
}
void findReachableSymbols(CFG* cfg, int* reachable) 
{
    int changed;
    reachable[cfg->start_symbol] = 1;
    do {
        changed = 0;
        for(int i = 0; i < cfg->num_rules; i++) 
        {
            char lhs = cfg->rules[i].lhs;
            if(reachable[lhs]) 
            {
                for(int j = 0; cfg->rules[i].rhs[j] != '\0'; j++) 
                {
                    if(!reachable[cfg->rules[i].rhs[j]]) 
                    {
                        reachable[cfg->rules[i].rhs[j]] = 1;
                        changed = 1;
                    }
                }
            }
        }
    } while(changed);
}
void removeUselessSymbols(CFG* cfg) 
{
    int generating[128] = {0}; 
    int reachable[128] = {0};
    printf("\nStep 1: Finding generating symbols...\n");
    findGeneratingSymbols(cfg, generating);
    printf("Generating symbols: ");
    for(int i = 0; i < cfg->num_terminals; i++) 
    {
        if(generating[cfg->terminals[i]])
            printf("%c ", cfg->terminals[i]);
    }
    for(int i = 0; i < cfg->num_non_terminals; i++) 
    {
        if(generating[cfg->non_terminals[i]])
            printf("%c ", cfg->non_terminals[i]);
    }
    printf("\n");
    int new_num_rules = 0;
    for(int i = 0; i < cfg->num_rules; i++) 
    {
        int valid = 1;
        for(int j = 0; cfg->rules[i].rhs[j] != '\0'; j++) 
        {
            if(!generating[cfg->rules[i].rhs[j]]) 
            {
                valid = 0;
                break;
            }
        }
        if(valid && generating[cfg->rules[i].lhs]) 
        {
            if(i != new_num_rules)
                cfg->rules[new_num_rules] = cfg->rules[i];
            new_num_rules++;
        }
    }
    cfg->num_rules = new_num_rules;
    printf("\nStep 2: Finding reachable symbols...\n");
    findReachableSymbols(cfg, reachable);  
    printf("Reachable symbols: ");
    for(int i = 0; i < cfg->num_terminals; i++) 
    {
        if(reachable[cfg->terminals[i]])
            printf("%c ", cfg->terminals[i]);
    }
    for(int i = 0; i < cfg->num_non_terminals; i++) 
    {
        if(reachable[cfg->non_terminals[i]])
            printf("%c ", cfg->non_terminals[i]);
    }
    printf("\n");
    new_num_rules = 0;
    for(int i = 0; i < cfg->num_rules; i++) 
    {
        if(reachable[cfg->rules[i].lhs]) 
        {
            int valid = 1;
            for(int j = 0; cfg->rules[i].rhs[j] != '\0'; j++) 
            {
                if(!reachable[cfg->rules[i].rhs[j]]) 
                {
                    valid = 0;
                    break;
                }
            }
            if(valid) 
            {
                if(i != new_num_rules)
                    cfg->rules[new_num_rules] = cfg->rules[i];
                new_num_rules++;
            }
        }
    }
    cfg->num_rules = new_num_rules;
    int new_num_non_terminals = 0;
    for(int i = 0; i < cfg->num_non_terminals; i++) 
    {
        if(generating[cfg->non_terminals[i]] && reachable[cfg->non_terminals[i]]) 
        {
            cfg->non_terminals[new_num_non_terminals++] = cfg->non_terminals[i];
        }
    }
    cfg->num_non_terminals = new_num_non_terminals;
    int new_num_terminals = 0;
    for(int i = 0; i < cfg->num_terminals; i++) 
    {
        if(reachable[cfg->terminals[i]]) 
        {
            cfg->terminals[new_num_terminals++] = cfg->terminals[i];
        }
    }
    cfg->num_terminals = new_num_terminals;
}

int main() {
    CFG cfg;
    char input[MAX_LENGTH];
    printf("Enter the start symbol: ");
    scanf(" %c", &cfg.start_symbol);
    getchar();
    printf("Enter number of terminals: ");
    scanf("%d", &cfg.num_terminals);
    getchar();
    printf("Enter the terminals (space separated): ");
    fgets(input, MAX_LENGTH, stdin);
    for(int i = 0; i < cfg.num_terminals; i++) {
        cfg.terminals[i] = input[i*2];
    }
    
    printf("Enter number of non-terminals: ");
    scanf("%d", &cfg.num_non_terminals);
    getchar(); 
    printf("Enter the non-terminals (space separated): ");
    fgets(input, MAX_LENGTH, stdin);
    for(int i = 0; i < cfg.num_non_terminals; i++) 
    {
        cfg.non_terminals[i] = input[i*2];
    }
    printf("Enter number of productions: ");
    scanf("%d", &cfg.num_rules);
    getchar();
    printf("Enter the productions (one per line, format: A->BC or A->a):\n");
    for(int i = 0; i < cfg.num_rules; i++)
    {
        fgets(input, MAX_LENGTH, stdin);
        cfg.rules[i].lhs = input[0];
        strcpy(cfg.rules[i].rhs, input + 3);
        cfg.rules[i].rhs[strcspn(cfg.rules[i].rhs, "\n")] = 0;
    }
    printf("\nOriginal Grammar:\n");
    printf("Start Symbol: %c\n", cfg.start_symbol);
    printf("Non-terminals: ");
    for(int i = 0; i < cfg.num_non_terminals; i++) 
    {
        printf("%c ", cfg.non_terminals[i]);
    }
    printf("\n");
    
    printf("Terminals: ");
    for(int i = 0; i < cfg.num_terminals; i++)
    {
        printf("%c ", cfg.terminals[i]);
    }
    printf("\n");
    
    printf("Productions:\n");
    for(int i = 0; i < cfg.num_rules; i++) 
    {
        printf("%c->%s\n", cfg.rules[i].lhs, cfg.rules[i].rhs);
    }
    removeUselessSymbols(&cfg);
    printf("\nGrammar after removing useless symbols:\n");
    printf("Start Symbol: %c\n", cfg.start_symbol);
    printf("Non-terminals: ");
    for(int i = 0; i < cfg.num_non_terminals; i++) 
    {
        printf("%c ", cfg.non_terminals[i]);
    }
    printf("\n");
    printf("Terminals: ");
    for(int i = 0; i < cfg.num_terminals; i++) 
    {
        printf("%c ", cfg.terminals[i]);
    }
    printf("\n");
    printf("Productions:\n");
    for(int i = 0; i < cfg.num_rules; i++) 
    {
        printf("%c->%s\n", cfg.rules[i].lhs, cfg.rules[i].rhs);
    }
    
    return 0;
}

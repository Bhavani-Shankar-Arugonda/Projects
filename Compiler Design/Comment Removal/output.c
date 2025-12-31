#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define max_productions 20
#define max_production_length 50

char alpha[max_productions][max_production_length][max_production_length]={'\0'};
char beta[max_productions][max_production_length][max_production_length]={'\0'};

typedef struct Production{
    char lhs;
    char rhs[max_productions][max_production_length];
    int rhs_count;
}Production;

typedef struct Grammar{
    Production rules[max_productions];
    int rule_count;
    char start_symbol;
}Grammar;

void remove_spaces(char* line)
{
    int i=0,j=0;
    while(line[i])
    {
        if(line[i]!=' ')
        {
            line[j++]=line[i];
        }
        i++;
    }
    line[j]='\0';
}

void remove_duplicates(char* string)
{
    int len = strlen(string);
    if(len == 0) {
        return;
    }
    int k = 0;
    for(int i = 0; i < len; i++)
    {
        if(string[i] == ' ') {
            string[k++] = ' ';
            continue;
        }
        int found = 0;
        for(int j = 0; j < k; j++)
        {
            if(string[i] == string[j])
            {
                found = 1;
                break;
            }
        }
        if(!found) {
            string[k++] = string[i];
        }
    }
    string[k] = '\0';
}

bool isNonTerminal(char symbol)
{
    return (symbol>='A' && symbol<='Z');
}


int findRuleIndex(Grammar* grammar, char lhs) {
    for(int i = 0; i < grammar->rule_count; i++) {
        if(grammar->rules[i].lhs == lhs) {
            return i;
        }
    }
    return -1;
}


char getNewNonTerminal(Grammar* grammar) {
    bool used[26] = {false};
    
    
    for(int i = 0; i < grammar->rule_count; i++) {
        if(grammar->rules[i].lhs >= 'A' && grammar->rules[i].lhs <= 'Z') {
            used[grammar->rules[i].lhs - 'A'] = true;
        }
    }
    
    
    for(int i = 0; i < 26; i++) {
        if(!used[i]) {
            return 'A' + i;
        }
    }
    return 'Z'; 
}


void removeDirectLeftRecursion(Grammar* grammar, int rule_index) {
    Production* rule = &grammar->rules[rule_index];
    char A = rule->lhs;
    
    int alpha_count = 0, beta_count = 0;
    
    
    for(int i = 0; i < rule->rhs_count; i++) {
        if(rule->rhs[i][0] == A) {
            
            strcpy(alpha[rule_index][alpha_count], rule->rhs[i] + 1); 
            alpha_count++;
        } else {
            
            strcpy(beta[rule_index][beta_count], rule->rhs[i]);
            beta_count++;
        }
    }
    
    if(alpha_count > 0) {
        
        char A_prime = getNewNonTerminal(grammar);
        
        
        rule->rhs_count = 0;
        
        
        for(int i = 0; i < beta_count; i++) {
            strcpy(rule->rhs[rule->rhs_count], beta[rule_index][i]);
            char temp_str[2] = {A_prime, '\0'};
            strcat(rule->rhs[rule->rhs_count], temp_str);
            rule->rhs_count++;
        }
        
        
        Production new_rule;
        new_rule.lhs = A_prime;
        new_rule.rhs_count = 0;
        
        
        for(int i = 0; i < alpha_count; i++) {
            strcpy(new_rule.rhs[new_rule.rhs_count], alpha[rule_index][i]);
            char temp_str[2] = {A_prime, '\0'};
            strcat(new_rule.rhs[new_rule.rhs_count], temp_str);
            new_rule.rhs_count++;
        }
        
        
        strcpy(new_rule.rhs[new_rule.rhs_count], "ε");
        new_rule.rhs_count++;
        
        
        grammar->rules[grammar->rule_count] = new_rule;
        grammar->rule_count++;
        
        printf("Direct left recursion removed for %c\n", A);
        printf("New non-terminal %c added\n", A_prime);
    }
}


void substituteProductions(Grammar* grammar, int i, int j) {
    Production* rule_i = &grammar->rules[i];
    Production* rule_j = &grammar->rules[j];
    char Aj = rule_j->lhs;
    
    char temp_productions[max_productions][max_production_length];
    int temp_count = 0;
    
    for(int k = 0; k < rule_i->rhs_count; k++) {
        if(rule_i->rhs[k][0] == Aj) {
            
            char remaining[max_production_length];
            strcpy(remaining, rule_i->rhs[k] + 1); 
            
            
            for(int l = 0; l < rule_j->rhs_count; l++) {
                strcpy(temp_productions[temp_count], rule_j->rhs[l]);
                strcat(temp_productions[temp_count], remaining);
                temp_count++;
            }
        } else {
            
            strcpy(temp_productions[temp_count], rule_i->rhs[k]);
            temp_count++;
        }
    }
    
    
    rule_i->rhs_count = temp_count;
    for(int k = 0; k < temp_count; k++) {
        strcpy(rule_i->rhs[k], temp_productions[k]);
    }
}


void removeIndirectLeftRecursion(Grammar* grammar) {
    printf("\nRemoving indirect left recursion...\n");
    
    for(int i = 0; i < grammar->rule_count; i++) {
        for(int j = 0; j < i; j++) {
            
            char Ai = grammar->rules[i].lhs;
            char Aj = grammar->rules[j].lhs;
            
            
            bool hasIndirectRecursion = false;
            for(int k = 0; k < grammar->rules[i].rhs_count; k++) {
                if(grammar->rules[i].rhs[k][0] == Aj) {
                    hasIndirectRecursion = true;
                    break;
                }
            }
            
            if(hasIndirectRecursion) {
                printf("Substituting %c productions into %c\n", Aj, Ai);
                substituteProductions(grammar, i, j);
            }
        }
        
        
        removeDirectLeftRecursion(grammar, i);
    }
}

void Direct_Left_recursion(Grammar* grammar, char* terminals) {
    printf("Original Grammar:\n");
    for(int i = 0; i < grammar->rule_count; i++) {
        printf("%c -> ", grammar->rules[i].lhs);
        for(int j = 0; j < grammar->rules[i].rhs_count; j++) {
            printf("%s", grammar->rules[i].rhs[j]);
            if(j < grammar->rules[i].rhs_count - 1) printf(" | ");
        }
        printf("\n");
    }
    
    printf("\nTerminals found: %s\n", terminals);
    
    
    removeIndirectLeftRecursion(grammar);
    
    printf("\nGrammar after removing left recursion:\n");
    for(int i = 0; i < grammar->rule_count; i++) {
        printf("%c -> ", grammar->rules[i].lhs);
        for(int j = 0; j < grammar->rules[i].rhs_count; j++) {
            printf("%s", grammar->rules[i].rhs[j]);
            if(j < grammar->rules[i].rhs_count - 1) printf(" | ");
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Error : Enter input file name as arguments while executing!!");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Error opening the file.");
        return 1;
    }
    
    Grammar grammar;
    grammar.rule_count = 0;
    char line[256];
    
    while(fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        remove_spaces(line);
        if(strlen(line) == 0) continue;
        
        char *lhs = strtok(line, "->");
        char *rhs = strtok(NULL, "->");
        if(lhs == NULL || rhs == NULL) continue;
        
        grammar.rules[grammar.rule_count].lhs = *lhs;
        grammar.rules[grammar.rule_count].rhs_count = 0;
        
        if(grammar.rule_count == 0)
        {
            grammar.start_symbol = grammar.rules[0].lhs;
        }
        
        char *token = strtok(rhs, "|");
        while(token != NULL && grammar.rules[grammar.rule_count].rhs_count < max_productions)
        {
            strcpy(grammar.rules[grammar.rule_count].rhs[grammar.rules[grammar.rule_count].rhs_count], token);
            grammar.rules[grammar.rule_count].rhs_count++;
            token = strtok(NULL, "|");
        }
        grammar.rule_count++;
        if(grammar.rule_count >= max_productions) break;
    }
    
    fclose(file);
    
    char Terminals[100] = "";
    for(int i = 0; i < grammar.rule_count; i++)
    {
        for(int j = 0; j < grammar.rules[i].rhs_count; j++)
        {
            int len = strlen(grammar.rules[i].rhs[j]);
            for(int l = 0; l < len; l++)
            {
                char temp = grammar.rules[i].rhs[j][l];
                if(!(temp >= 'A' && temp <= 'Z'))
                {
                    char temp2[2] = {temp, '\0'};
                    strcat(Terminals, temp2);
                }
            }
        }
    }
    remove_duplicates(Terminals);
    
    Direct_Left_recursion(&grammar, Terminals);
    
    return 0;
}
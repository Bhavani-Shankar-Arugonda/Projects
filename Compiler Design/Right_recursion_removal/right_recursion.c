#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define max_productions 20
#define max_production_length 100

typedef struct Production{
    char lhs;
    char rhs[max_productions][max_production_length];
    int rhs_length;
}P;

typedef struct Grammar{
    P rules[max_productions];
    int rule_count;
    char start_symbol;
}G;

void remove_spaces(char *line)
{
    int i=0,j=0;
    int len=strlen(line);

    while(i<len)
    {
        if(line[i]!=' ')
        {
            line[j++]=line[i];
        }
        i++;
    }

    line[j]='\0';
    //return line;
}

void right_recursion(G *grammar)
{
    bool found;
    for(int i=0;i<grammar->rule_count;i++)
    {
        found=false;
        for(int j=0;j<grammar->rules[i].rhs_length;j++)
        {
            int len=strlen(grammar->rules[i].rhs[j]);
            if(grammar->rules[i].rhs[j][len-1]==grammar->rules[i].lhs)
            {
                found=true;
            }
        }

        if(found)
        {
            P temp1,temp2;
            temp1.lhs='Z'-i;
            temp1.rhs_length = 0;
            temp2.lhs=grammar->rules[i].lhs;
            temp2.rhs_length = 0;
            
            for(int j=0;j<grammar->rules[i].rhs_length;j++)
            {
                int len=strlen(grammar->rules[i].rhs[j]);
                if(grammar->rules[i].rhs[j][len-1]==grammar->rules[i].lhs)
                {
                    char t[max_production_length] = "";
                    char t2[2] = {temp1.lhs, '\0'};
                    strcat(t, t2);
                    strcat(t, grammar->rules[i].rhs[j]);
                    t[strlen(t)-1]='\0';
                    strcpy(temp1.rhs[temp1.rhs_length++], t);
                }
                else{
                    char t[max_production_length] = "";
                    char t2[2] = {temp1.lhs, '\0'};
                    strcat(t, t2);
                    strcat(t,grammar->rules[i].rhs[j]);
                    strcpy(temp2.rhs[temp2.rhs_length++],t);
                }
            }
            strcpy(temp1.rhs[temp1.rhs_length++],"e");
            grammar->rules[i] = temp2;
            if(grammar->rule_count < max_productions)
            {
                grammar->rules[grammar->rule_count++] = temp1;
            }
        }
    }
}

void print_grammar(G grammar) {
    //printf("--- %s ---\n", title);
    printf("Start Symbol: %c\n", grammar.start_symbol);
    printf("Rule Count: %d\n", grammar.rule_count);
    for (int i = 0; i < grammar.rule_count; i++) {
        // Print the LHS
        printf("%c -> ", grammar.rules[i].lhs);
        
        // Print all the RHS productions, separated by |
        for (int j = 0; j < grammar.rules[i].rhs_length; j++) {
            printf("%s", grammar.rules[i].rhs[j]);
            if (j < grammar.rules[i].rhs_length - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }
    printf("---------------------------------------\n\n");
}

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        return 0;
    }

    FILE *file=fopen(argv[1],"r");

    G grammar;
    grammar.rule_count=0;
    char line[256];

    while(fgets(line,sizeof(line),file))
    {
        if(strlen(line)==0)continue;
        line[strcspn(line,"\n")]=0;
        remove_spaces(line);

        char *lhs=strtok(line,"->");
        char *rhs=strtok(NULL,"->");

        grammar.rules[grammar.rule_count].lhs=lhs[0];
        grammar.rules[grammar.rule_count].rhs_length=0;

        if(grammar.rule_count==0)grammar.start_symbol=lhs[0];

        char *tok=strtok(rhs,"|");
        while(tok != NULL && grammar.rules[grammar.rule_count].rhs_length < max_productions)
        {
            strcpy(grammar.rules[grammar.rule_count].rhs[grammar.rules[grammar.rule_count].rhs_length++],tok);
            tok=strtok(NULL,"|");
        }

        grammar.rule_count++;
    }

    right_recursion(&grammar);
    print_grammar(grammar);
}
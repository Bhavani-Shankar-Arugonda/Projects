#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define max_productions 20
#define max_production_length 50

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



int main(int argc ,char **argv)
{
    if(argc!=2)
    {
        printf("Input not read!!");
        return 1;
    }

    FILE *file=fopen(argv[1],"r");

    if(file==NULL)
    {
        printf("Error opening the file!");
        return 0;
    }

    Grammar grammar;
    grammar.rule_count=0;
    char line[256];

    while(fgets(line,sizeof(line),file))
    {
        line[strcspn(line,"\n")]=0;
        remove_spaces(line);
        if(strlen(line)==0)continue;
        char *lhs=strtok(line,"->");
        char *rhs=strtok(NULL,"->");

        if(lhs==NULL || rhs==NULL)continue;

        grammar.rules[grammar.rule_count].lhs=*lhs;
        grammar.rules[grammar.rule_count].rhs_count=0;
        char *token=strtok(rhs,"|");
        while(token!=NULL && grammar.rules[grammar.rule_count].rhs_count<max_productions)
        {
            strcpy(grammar.rules[grammar.rule_count].rhs[grammar.rules[grammar.rule_count].rhs_count],token);
            grammar.rules[grammar.rule_count].rhs_count++;
            token=strtok(NULL,"|");
        }
        grammar.rule_count++;
        if(grammar.rule_count >= max_productions) break;
    }


}
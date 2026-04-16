#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define max_productions 20
#define max_production_length 50

//char parsingTable[100][100];

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

char *Leading(Grammar grammar,char symbol,char from)
{
    char *leading = (char*)malloc(100 * sizeof(char));
    leading[0] = '\0';
    for(int i=0;i<grammar.rule_count;i++)
    {
        if(grammar.rules[i].lhs==symbol)
        {
            for(int j=0;j<grammar.rules[i].rhs_count;j++)
            {
                char* rhs=grammar.rules[i].rhs[j];
                if(from!=rhs[0] && isNonTerminal(rhs[0]))
                {
                    char *temp=Leading(grammar,rhs[0],symbol);
                    strcat(leading,temp);
                    if(!isNonTerminal(rhs[1]))
                    {
                        char temp1[2];
                        temp1[0]=rhs[1];
                        temp1[1]='\0';
                        strcat(leading,temp1);
                    }
                }
                else if(!isNonTerminal(rhs[0]))
                {
                    char temp2[2];
                    temp2[0]=rhs[0];
                    temp2[1]='\0';
                    strcat(leading,temp2);
                }
            }
        }
    }
    remove_spaces(leading);
    remove_duplicates(leading);
    return leading;
}

char * Trailing(Grammar grammar,char symbol,char from)
{
    char *trailing = (char*)malloc(100 * sizeof(char));
    trailing[0] = '\0';
    for(int i=0;i<grammar.rule_count;i++)
    {
        if(grammar.rules[i].lhs==symbol)
        {
            for(int j=0;j<grammar.rules[i].rhs_count;j++)
            {
                int last=strlen(grammar.rules[i].rhs[j])-1;
                char* rhs=grammar.rules[i].rhs[j];
                if(from!=rhs[last] && isNonTerminal(rhs[last]))
                {
                    char *temp=Trailing(grammar,rhs[last],symbol);
                    strcat(trailing,temp);
                    if(!isNonTerminal(rhs[last-1]))
                    {
                        char temp1[2];
                        temp1[0]=rhs[last-1];
                        temp1[1]='\0';
                        strcat(trailing,temp1);
                    }
                }
                else if(!isNonTerminal(rhs[last]))
                {
                    char temp2[2];
                    temp2[0]=rhs[last];
                    temp2[1]='\0';
                    strcat(trailing,temp2);
                }
            }
        }
    }
    remove_spaces(trailing);
    remove_duplicates(trailing);
    return trailing;
}

// int getTerminalIndex(char* Terminals,char symbol)
// {
    
//     int len=strlen(Terminals);
//     if(symbol=='$'){
//         return len;
//     }
//     for(int i=0;i<len;i++)
//     {
//         if(Terminals[i]==symbol)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// void ParsingTable(Grammar grammar,char *terminals)
// {
//     for(int i=0;i<grammar.rule_count;i++)
//     {
//         for(int j=0;j<grammar.rules[i].rhs_count;j++)
//         {
//             for(int k=0;k<strlen(grammar.rules[i].rhs[j])-1;k++)
//             {
//                 char *rhs=grammar.rules[i].rhs[j];
//             }
//         }
//     }
// }

int main(int argc,char **argv)
{
   if(argc !=2)
   {
       printf("Error : Enter input file name as arguments while executing!!");
       return 1;
   }


   FILE *file=fopen(argv[1],"r");
   if(file==NULL)
   {
       printf("Error opening the file.");
       return 1;
   }


   Grammar grammar;
   grammar.rule_count=0;
   char line[256];


   while(fgets(line,sizeof(line),file))
   {
       line[strcspn(line, "\n")] = 0;
       remove_spaces(line);
       if(strlen(line)==0) continue;

       char *lhs=strtok(line,"->");
       char *rhs=strtok(NULL,"->");

       if(lhs == NULL || rhs == NULL) continue;

       grammar.rules[grammar.rule_count].lhs=*lhs;
       grammar.rules[grammar.rule_count].rhs_count=0;
       if(grammar.rule_count==0)
       {
           grammar.start_symbol=grammar.rules[0].lhs;
       }

       char *token=strtok(rhs,"|");
       while(token != NULL && grammar.rules[grammar.rule_count].rhs_count < max_productions)
       {
           strcpy(grammar.rules[grammar.rule_count].rhs[grammar.rules[grammar.rule_count].rhs_count],token);
           grammar.rules[grammar.rule_count].rhs_count++;
           token=strtok(NULL,"|");
       }

       grammar.rule_count++;
       if(grammar.rule_count >= max_productions) break;
   }

    for(int i=0;i<grammar.rule_count;i++)
    {
        printf("Leading of %c is %s\n",grammar.rules[i].lhs,Leading(grammar,grammar.rules[i].lhs,'\0'));
    }

    for(int i=0;i<grammar.rule_count;i++)
    {
        printf("Trailing of %c is %s\n",grammar.rules[i].lhs,Trailing(grammar,grammar.rules[i].lhs,'\0'));
    }

//     char Terminals[100] = "";
//     for(int i=0;i<grammar.rule_count;i++)
//     {
//             for(int j=0;j<grammar.rules[i].rhs_count;j++)
//             {
//                 int len=strlen(grammar.rules[i].rhs[j]);
//                 for(int l=0;l<len;l++)
//                 {
//                     char temp=grammar.rules[i].rhs[j][l];
//                     if(!(temp>='A' && temp<='Z'))
//                     {
//                         char temp2[2]={temp,'\0'};
//                         strcat(Terminals,temp2);
//                     }
//                 }        
//             }
//     }
//    remove_duplicates(Terminals);
}
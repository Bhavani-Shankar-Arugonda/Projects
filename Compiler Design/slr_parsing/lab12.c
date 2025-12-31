#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

typedef struct entry{
    char type;
    int val;
}entry;

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

int getSymbolIndex(char* symbols,char symbol)
{
    
    int len=strlen(symbols);
    for(int i=0;i<len;i++)
    {
        if(symbols[i]==symbol)
        {
            return i;
        }
    }
    return -1;
}

void parseString(Grammar grammar,char *string,char *Symbols,entry parsingTable[100][strlen(Symbols)])
{
    char stack[100];
    int inputTop=0;
    int stackTop=0;
    stack[stackTop]=0;

    typedef struct R{
        char S;
        int len;
    }R;

    R r[max_productions];
    int k=1;
    for(int i=0;i<grammar.rule_count;i++)
    {
        for(int j=0;j<grammar.rules[i].rhs_count;j++)
        {
            r[k].S=grammar.rules[i].lhs;
            r[k].len=strlen(grammar.rules[i].rhs[j]);
            k++;
        }
    }

    while(inputTop!=strlen(Symbols) && stackTop!=-1)
    {
        int index=getSymbolIndex(Symbols,string[inputTop]);
        if(parsingTable[(int)stack[stackTop]][index].type=='NULL')
        {
            printf("string not accepted, no value in table");
            return;
        }
        if(parsingTable[(int)stack[stackTop]][index].type=='A')
        {
            printf("string accepted");
            return;
        }
        if(parsingTable[(int)stack[stackTop]][index].type=='S')
        {
            char temp=parsingTable[(int)stack[stackTop]][index].val;
            stack[++stackTop]=string[inputTop++];
            stack[++stackTop]=(char)temp;
        }
        if(parsingTable[(int)stack[stackTop]][index].type=='R')
        {
            int f=parsingTable[(int)stack[stackTop]][index].val;
            int l=r[f].len;
            stackTop=stackTop-2*l;
            stack[++stackTop]=r[f].S;
            if(parsingTable[(int)stack[stackTop-1]][getSymbolIndex(Symbols,stack[stackTop])].val<1)
            {
                printf("not parsed goto entry not found");
                return;
            }
            stack[++stackTop]=parsingTable[(int)stack[stackTop-1]][getSymbolIndex(Symbols,stack[stackTop])].val;
        }
    }
}

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
   char Symbols[100] = "";
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
        for(int j=0;j<grammar.rules[i].rhs_count;j++)
        {
            int len=strlen(grammar.rules[i].rhs[j]);
            for(int l=0;l<len;l++)
            {
                char temp=grammar.rules[i].rhs[j][l];
                if(!(temp>='A' && temp<='Z'))
                {
                    char temp2[2]={temp,'\0'};
                    strcat(Symbols,temp2);
                }
            }        
        }
   }
   strcat(Symbols,"$");
   for(int i=0;i<grammar.rule_count;i++)
   {
        if(getSymbolIndex(Symbols,grammar.rules[i].lhs)==-1)
        {
            char t[2]={grammar.rules[i].lhs,'\0'};
            strcat(Symbols,t);
        }
        for(int j=0;j<grammar.rules[i].rhs_count;j++)
        {
            int len=strlen(grammar.rules[i].rhs[j]);
            for(int l=0;l<len;l++)
            {
                char temp=grammar.rules[i].rhs[j][l];
                if((temp>='A' && temp<='Z')&&(getSymbolIndex(Symbols,temp)==-1))
                {
                    char temp2[2]={temp,'\0'};
                    strcat(Symbols,temp2);
                }
            }        
        }
   }
   remove_duplicates(Symbols);

   entry parsingTable[100][strlen(Symbols)];

   char inputString[100];
   printf("\n");
   scanf("%s",inputString);
   strcat(inputString,"$");

   

   parsingTable[0][getSymbolIndex(Symbols,'i')].type='S';
   parsingTable[0][getSymbolIndex(Symbols,'i')].val=5;

   parsingTable[0][getSymbolIndex(Symbols,'(')].type='S';
   parsingTable[0][getSymbolIndex(Symbols,'(')].val=4;

   parsingTable[0][getSymbolIndex(Symbols,'E')].type='G';
   parsingTable[0][getSymbolIndex(Symbols,'E')].val=1;

   parsingTable[0][getSymbolIndex(Symbols,'T')].type='G';
   parsingTable[0][getSymbolIndex(Symbols,'T')].val=2;

   parsingTable[0][getSymbolIndex(Symbols,'F')].type='G';
   parsingTable[0][getSymbolIndex(Symbols,'F')].val=3;

   parsingTable[1][getSymbolIndex(Symbols,'+')].type='S';
   parsingTable[1][getSymbolIndex(Symbols,'+')].val=6;

   parsingTable[1][getSymbolIndex(Symbols,'$')].type='A';
   
   parsingTable[2][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[2][getSymbolIndex(Symbols,'+')].val=2;

   parsingTable[2][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[2][getSymbolIndex(Symbols,')')].val=2;

   parsingTable[2][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[2][getSymbolIndex(Symbols,'$')].val=2;

   parsingTable[2][getSymbolIndex(Symbols,'*')].type='S';
   parsingTable[2][getSymbolIndex(Symbols,'*')].val=7;

   parsingTable[3][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[3][getSymbolIndex(Symbols,'+')].val=4;

   parsingTable[3][getSymbolIndex(Symbols,'*')].type='R';
   parsingTable[3][getSymbolIndex(Symbols,'*')].val=4;

   parsingTable[3][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[3][getSymbolIndex(Symbols,')')].val=4;

   parsingTable[3][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[3][getSymbolIndex(Symbols,'$')].val=4;

   parsingTable[4][getSymbolIndex(Symbols,'i')].type='S';
   parsingTable[4][getSymbolIndex(Symbols,'i')].val=5;

   parsingTable[4][getSymbolIndex(Symbols,'(')].type='S';
   parsingTable[4][getSymbolIndex(Symbols,'(')].val=4;

   parsingTable[4][getSymbolIndex(Symbols,'E')].type='G';
   parsingTable[4][getSymbolIndex(Symbols,'E')].val=8;

   parsingTable[4][getSymbolIndex(Symbols,'T')].type='G';
   parsingTable[4][getSymbolIndex(Symbols,'T')].val=2;

   parsingTable[4][getSymbolIndex(Symbols,'F')].type='G';
   parsingTable[4][getSymbolIndex(Symbols,'F')].val=3;

   parsingTable[5][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[5][getSymbolIndex(Symbols,'+')].val=6;

   parsingTable[5][getSymbolIndex(Symbols,'*')].type='R';
   parsingTable[5][getSymbolIndex(Symbols,'*')].val=6;

   parsingTable[5][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[5][getSymbolIndex(Symbols,')')].val=6;

   parsingTable[5][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[5][getSymbolIndex(Symbols,'$')].val=6;

   parsingTable[6][getSymbolIndex(Symbols,'i')].type='S';
   parsingTable[6][getSymbolIndex(Symbols,'i')].val=5;

   parsingTable[6][getSymbolIndex(Symbols,'(')].type='S';
   parsingTable[6][getSymbolIndex(Symbols,'(')].val=4;

   parsingTable[6][getSymbolIndex(Symbols,'T')].type='G';
   parsingTable[6][getSymbolIndex(Symbols,'T')].val=9;

   parsingTable[6][getSymbolIndex(Symbols,'F')].type='G';
   parsingTable[6][getSymbolIndex(Symbols,'F')].val=3;

   parsingTable[7][getSymbolIndex(Symbols,'i')].type='S';
   parsingTable[7][getSymbolIndex(Symbols,'i')].val=5;

   parsingTable[7][getSymbolIndex(Symbols,'(')].type='S';
   parsingTable[7][getSymbolIndex(Symbols,'(')].val=4;

   parsingTable[7][getSymbolIndex(Symbols,'F')].type='G';
   parsingTable[7][getSymbolIndex(Symbols,'F')].val=10;

   parsingTable[8][getSymbolIndex(Symbols,'+')].type='S';
   parsingTable[8][getSymbolIndex(Symbols,'+')].val=6;

   parsingTable[8][getSymbolIndex(Symbols,')')].type='S';
   parsingTable[8][getSymbolIndex(Symbols,')')].val=11;

   parsingTable[9][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[9][getSymbolIndex(Symbols,'+')].val=1;

   parsingTable[9][getSymbolIndex(Symbols,'*')].type='S';
   parsingTable[9][getSymbolIndex(Symbols,'*')].val=7;
   
   parsingTable[9][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[9][getSymbolIndex(Symbols,')')].val=1;

   parsingTable[9][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[9][getSymbolIndex(Symbols,'$')].val=1;

   parsingTable[10][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[10][getSymbolIndex(Symbols,'+')].val=3;

   parsingTable[10][getSymbolIndex(Symbols,'*')].type='R';
   parsingTable[10][getSymbolIndex(Symbols,'*')].val=3;
   
   parsingTable[10][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[10][getSymbolIndex(Symbols,')')].val=3;

   parsingTable[10][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[10][getSymbolIndex(Symbols,'$')].val=3;

   parsingTable[11][getSymbolIndex(Symbols,'+')].type='R';
   parsingTable[11][getSymbolIndex(Symbols,'+')].val=5;

   parsingTable[11][getSymbolIndex(Symbols,'*')].type='R';
   parsingTable[11][getSymbolIndex(Symbols,'*')].val=5;
   
   parsingTable[11][getSymbolIndex(Symbols,')')].type='R';
   parsingTable[11][getSymbolIndex(Symbols,')')].val=5;

   parsingTable[11][getSymbolIndex(Symbols,'$')].type='R';
   parsingTable[11][getSymbolIndex(Symbols,'$')].val=5;

   //printf("%s",Symbols);
   parseString(grammar,inputString,Symbols,parsingTable);
   //printf("%s",inputString);
   return 0;
}
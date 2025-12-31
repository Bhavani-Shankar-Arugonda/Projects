#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max_productions 20
#define max_production_length 50

int parsingTable[100][100];

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

char *FIRST(Grammar grammar,char symbol)
{
   char* first = (char*)malloc(200);
   first[0]='\0';

   if(!(symbol>= 'A' && symbol<='Z'))
   {
       first[0] = symbol;
       first[1] = '\0';
       return first;
   }


   for(int i=0;i<grammar.rule_count;i++)
   {
       if(grammar.rules[i].lhs==symbol)
       {
           for(int j=0;j<grammar.rules[i].rhs_count;j++)
           {
               char X=grammar.rules[i].rhs[j][0];
               if(!(X>='A' && X<='Z'))
               {
                   char temp[2] = {X, '\0'};
                   strcat(first,temp);
                   strcat(first," ");
               }
               else{
                   char *first_X=FIRST(grammar,X);
                   if(strchr(first_X,'e')==NULL)
                   {
                       strcat(first,first_X);
                   }
                   else{
                       char buffer[100];
                       strcpy(buffer,first_X);
                       buffer[strcspn(buffer,"e")]=' ';
                       strcat(first,buffer);
                       int num=1;
                       int len = strlen(grammar.rules[i].rhs[j]);
                       while(1)
                       {
                           char Y = (num < len) ? grammar.rules[i].rhs[j][num] : '\0';

                           if (Y == '\0') {
                               strcat(first, "e");
                               break;
                           }

                           if(!(Y>='A' && Y<='Z'))
                           {
                               char s[2]={Y,'\0'};
                               strcat(first,s);
                               strcat(first," ");
                               break;
                           }
                           else{
                               char *first_Y=FIRST(grammar,Y);


                               if(strchr(first_Y,'e')==NULL)
                               {
                                   strcat(first, first_Y);
                                   free(first_Y);
                                   break;
                               }
                               else{
                                   char buf[200];
                                   strcpy(buf, first_Y);
                                   buf[strcspn(buf, "e")] = ' '; 
                                   strcat(first, buf);
                                   free(first_Y);
                                   num++;                        
                                   continue;   
                               }
                           }
                       }
                   }
                   free(first_X);
               }
           }
       }
   }
   remove_spaces(first);
   remove_duplicates(first);
   return first;
}

char *FOLLOW(Grammar grammar,char symbol,char from)
{
   char* follow=(char*)malloc(200);
   follow[0] = '\0';
   if(symbol==grammar.start_symbol)
   {
       strcat(follow,"$");
   }

   for(int i=0;i<grammar.rule_count;i++)
   {
       for(int j=0;j<grammar.rules[i].rhs_count;j++)
       {
           char *temp=grammar.rules[i].rhs[j];
           int temp_len=strlen(grammar.rules[i].rhs[j]);
           char s[2]={symbol,'\0'};
           if(strcspn(temp,s)>=0 && strcspn(temp,s)<temp_len-1)
           {
               char buffer[100];
               strcpy(buffer,temp);
               
               int pos = strcspn(temp,s) + 1;
               
               while(pos < temp_len)
               {
                   char first[100];
                   char* temp_first = FIRST(grammar, buffer[pos]);
                   strcpy(first, temp_first);
                   free(temp_first);
                   
                   int temp_len_first = strlen(first);
                   for(int k = 0; k < temp_len_first; k++)
                   {
                       if(first[k] != 'e')
                       {
                           char temp_char[2] = {first[k], '\0'};
                           strcat(follow, temp_char);
                           strcat(follow, " ");
                       }
                   }
                   
                   if(strchr(first, 'e') == NULL)
                   {
                       break;
                   }
                   
                   
                   pos++;
                   
                   if(pos >= temp_len)
                   {
                       if(symbol != grammar.rules[i].lhs && grammar.rules[i].lhs != from)
                       {
                           char* temp_follow = FOLLOW(grammar, grammar.rules[i].lhs, symbol);
                           strcat(follow, temp_follow); 
                           free(temp_follow);
                       }
                   }
               }
           }
           else if(strcspn(temp,s)==temp_len-1 && symbol != grammar.rules[i].lhs && from != grammar.rules[i].lhs)
           {
               char* temp_follow=FOLLOW(grammar,grammar.rules[i].lhs,symbol);
               strcat(follow,temp_follow);
               free(temp_follow);  
           }
       }
   }
   remove_duplicates(follow);
   remove_spaces(follow);
   return follow;
}

int getNonTerminalIndex(char* Terminals,char symbol)
{
    
    int len=strlen(Terminals);
    if(symbol=='$'){
        return len;
    }
    for(int i=0;i<len;i++)
    {
        if(Terminals[i]==symbol)
        {
            return i;
        }
    }
    return -1;
}

void parsingtable(Grammar grammar,char* Terminals)
{
    int nonTerminalCount = grammar.rule_count;
    int terminalCount = strlen(Terminals);
    
    for(int i = 0; i < nonTerminalCount; i++) {
        for (int k = 0; k <= terminalCount; k++) {
            parsingTable[i][k] = -1;
        }
    }

    for(int i=0;i<nonTerminalCount;i++)
    {   
        for(int j=0;j<grammar.rules[i].rhs_count;j++)
        {    
            int temp=0;
            char symbol=grammar.rules[i].rhs[j][temp];
            char* first = (char*)malloc(200);
            first[0] = '\0';
            while(temp<strlen(grammar.rules[i].rhs[j]))
            {
                char *temp2=FIRST(grammar,symbol);
                if(temp==strlen(grammar.rules[i].rhs[j])-1)
                {
                    strcat(first,temp2);
                    break;
                }

                if(strchr(temp2,'e')==NULL)
                {
                    strcat(first,temp2);
                    break;
                } 
                else{
                    int temp3=strlen(temp2);
                    for(int d=0;d<temp3;d++)
                    {
                        if(temp2[d]!='e')
                        {
                            char temp4[2]={temp2[d],'\0'};
                            strcat(first,temp4);
                        }
                    }
                    symbol=grammar.rules[i].rhs[j][++temp];
                }
            }
            //first is computed
            temp=strlen(first);

            if(strchr(first,'e')==NULL)
            {
                for(int l=0;l<temp;l++)
                {
                    int nonTerminalIndex=getNonTerminalIndex(Terminals,first[l]);
                    parsingTable[i][nonTerminalIndex]=j;
                }
            }
            else{
                for(int l=0;l<temp;l++)
                {
                    if(first[l]!='e')
                    {
                        int nonTerminalIndex=getNonTerminalIndex(Terminals,first[l]);
                        if(parsingTable[i][nonTerminalIndex]==-1)
                        {
                            parsingTable[i][nonTerminalIndex]=j;
                        }
                        else{
                            printf("\nGrammar is not LL(1). A conflict was found during table generation.\n\n");
                            return;
                        }
                    }
                }

                char* follow=FOLLOW(grammar,grammar.rules[i].lhs,'\0');
                temp=strlen(follow);
                for(int l=0;l<temp;l++)
                {
                    if(follow[l]!='e')
                    {
                        int nonTerminalIndex=getNonTerminalIndex(Terminals,follow[l]);
                        if(parsingTable[i][nonTerminalIndex]==-1)
                        {
                            parsingTable[i][nonTerminalIndex]=j;
                        }
                        else{
                            printf("\nGrammar is not LL(1). A conflict was found during table generation.\n\n");
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("\nParsing Table:\n   ");
    printf("\t");
    int t=-1;
    for (int j = 0; j < strlen(Terminals); j++) {
        if(Terminals[j]!='e')
        {
            printf("%c\t", Terminals[j]);
        }
        else{
            t=j;
        }
    }
    printf("$\n");

    for(int i=0; i<grammar.rule_count;i++)
    {   
        printf("%c|\t", grammar.rules[i].lhs);
        for(int j=0;j<=strlen(Terminals);j++)
        {
            if(j!=t)
            {
                if(parsingTable[i][j] == -1)
                {printf(".\t");}
                else
                {printf("%c->%s\t",grammar.rules[i].lhs,grammar.rules[i].rhs[parsingTable[i][j]]);}
            }
        }
        printf("\n");
    }
}

void parseString(Grammar grammar,char *string)
{
    char stack[100];
    int stack_top=0;
    stack[0]='$';

    char input[100];
    int input_top=0;
    input[0]='$';

    strcat(input,string);
    // while(stack_top!=-1 && input_top!=-1)
    // {
    //     if(stack[stack_top]==input[input_top] && stack[stack_top]!='$')
    //     {
    //         stack_top--;
    //         input_top--;
    //     }
    //     if()
    // }
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
   char Terminals[100] = "";
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


   for(int i=0; i<grammar.rule_count;i++)
   {
       char*first = FIRST(grammar,grammar.rules[i].lhs);
       printf("First of %c is : ",grammar.rules[i].lhs);

       printf("{");
       for(int i=0; i<strlen(first);i++)
       {
           printf("%c,",first[i]);
       }
       printf("}\n");
      
   }
   printf("\n\n");
   for(int i=0; i<grammar.rule_count;i++)
   {
       char*follow = FOLLOW(grammar,grammar.rules[i].lhs,'\0');
       printf("Follow of %c is : ",grammar.rules[i].lhs);
       printf("{");
       for(int i=0; i<strlen(follow);i++)
       {
           printf("%c,",follow[i]);
       }
       printf("}\n");
   }

   //get terminals
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
                    strcat(Terminals,temp2);
                }
            }        
        }
   }
   remove_duplicates(Terminals);

    parsingtable(grammar,Terminals);
    
   
   //parsing string
   char inputString[100];
   printf("\n");
   scanf("%s",inputString);
   //printf("input string : %s",inputString);
   parseString(grammar,inputString);
   return 0;
}


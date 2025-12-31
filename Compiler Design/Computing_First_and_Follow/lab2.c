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

char *FOLLOW(Grammar grammar,char symbol)
{
    char* follow=(char*)malloc(200);
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
                char first[100];
                strcpy(buffer,temp);
                strcpy(first,FIRST(grammar,buffer[strcspn(temp,s)+1]));
                if(strchr(first,'e')!=NULL)
                {
                    while(strchr(first,'e')!=NULL)
                    {
                        char e[2]={'e','\0'};
                        first[strcspn(first,e)]=' ';
                    }
                    if(symbol != grammar.rules[i].lhs)
                    {
                        char* temp_follow=FOLLOW(grammar,grammar.rules[i].lhs);
                        strcat(follow,temp_follow);

                        // if(if_loop_possible(grammar,symbol,grammar.rules[i].lhs)==1)
                        // {
                        //     char* temp_follow=FOLLOW(grammar,grammar.rules[i].lhs);
                        //     strcat(follow,temp_follow);
                        // }
                        
                    }
                    
                }
                strcat(follow,first);
            }
            else if(strcspn(temp,s)==temp_len-1 && symbol != grammar.rules[i].lhs)
            {
                char* temp_follow=FOLLOW(grammar,grammar.rules[i].lhs);
                strcat(follow,temp_follow);   
                // if(if_loop_possible(grammar,symbol,grammar.rules[i].lhs)==1)
                // {
                //     char* temp_follow=FOLLOW(grammar,grammar.rules[i].lhs);
                //     strcat(follow,temp_follow);
                // }
            }
        }
    }
    remove_duplicates(follow);
    remove_spaces(follow);
    return follow;
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
        char*follow = FOLLOW(grammar,grammar.rules[i].lhs);
        printf("Follow of %c is : ",grammar.rules[i].lhs);
        printf("{");
        for(int i=0; i<strlen(follow);i++)
        {
            printf("%c,",follow[i]);
        }
        printf("}\n");
    }
    return 0;

}
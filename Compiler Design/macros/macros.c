#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_MACROS 50
#define MAX_LEN 500
#define MAX_ARGUMENTS 20

typedef struct {
    char name[100];
    char body[MAX_LEN];
    int is_function;
    int argument_count;
    char arguments[MAX_ARGUMENTS][MAX_LEN];
} Macro;

Macro macros[MAX_MACROS];
int macro_count = 0;

void parseMacro(char *line) {
    if (macro_count >= MAX_MACROS) return;

    char *ptr = line + 7;
    while (*ptr == ' ' || *ptr == '\t') ptr++;

    char name[100];
    int i = 0;
    while (i < 99 && *ptr != '(' && *ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n') {
        name[i++] = *ptr++;
    }
    name[i] = '\0';
    strcpy(macros[macro_count].name, name);

    if (*ptr == '(') {
        macros[macro_count].is_function = 1;
        macros[macro_count].argument_count=0;
        int k=0;
        while (*ptr != ')' && *ptr != '\0') 
        {
            int s=0;
            while(*ptr!=',' && *ptr != ')'&& *ptr!='\0')
            {
                macros[macro_count].arguments[k++][s++]=*ptr;
                ptr++;
            }

            if(*ptr==',')
            {
                if(macros[macro_count].argument_count==0){macros[macro_count].argument_count=2;}
                else{macros[macro_count].argument_count++;}
                ptr++;
            }
        }
        if (*ptr == ')') ptr++;
    } else {
        macros[macro_count].is_function = 0;
    }

    while (*ptr == ' ' || *ptr == '\t') ptr++;
    int len = 0;
    while (len < MAX_LEN - 1 && *ptr != '\0' && *ptr != '\n') {
        macros[macro_count].body[len++] = *ptr++;
    }
    macros[macro_count].body[len] = '\0';

    macro_count++;
}

int Boundary(char c) {
    return !isalnum(c) && c != '_';
}

void expandMacros(char *output, int max_len) {
    for (int m = 0; m < macro_count; m++) {
        char temp[MAX_LEN];
        char *ptr = output;
        int dest = 0;
        int name_len = strlen(macros[m].name);

        if (macros[m].is_function) {
            while (*ptr != '\0' && dest < max_len - 1) {
                if (strncmp(ptr, macros[m].name, name_len) == 0 && *(ptr + name_len) == '(') {
                    ptr = ptr + name_len + 1;
                    int depth = 1;
                    while (*ptr != '\0' && depth > 0) {
                        if (*ptr == '(') depth++;
                        else if (*ptr == ')') depth--;   
                        ptr++;
                    }
    
                    char *body = macros[m].body;
                    while (*body != '\0' && dest < max_len - 1) {
                        temp[dest++] = *body++;
                    }
                } else {
                    temp[dest++] = *ptr++;
                }
            }
        } else {
            while (*ptr != '\0' && dest < max_len - 1) {
                if (strncmp(ptr, macros[m].name, name_len) == 0) {
                    char before = (ptr == output) ? ' ' : *(ptr - 1);
                    char after = *(ptr + name_len);

                    if (Boundary(before) && Boundary(after)) {
                        char *body = macros[m].body;
                        while (*body != '\0' && dest < max_len - 1) {
                            temp[dest++] = *body++;
                        }
                        ptr += name_len;
                    } else {
                        temp[dest++] = *ptr++;
                    }
                } else {
                    temp[dest++] = *ptr++;
                }
            }
        }

        temp[dest] = '\0';
        strncpy(output, temp, max_len - 1);
        output[max_len - 1] = '\0';
    }
}


int main() {
    FILE *in = fopen("input.c", "r");
    FILE *out = fopen("output.c", "w");

    if (!in || !out) {
        printf("Error opening files\n");
        return 1;
    }

    char line[MAX_LEN];

    while (fgets(line, MAX_LEN, in)) {
        if (strncmp(line, "#define", 7) == 0) {
            parseMacro(line);
        }
    }

    rewind(in);
    while (fgets(line, MAX_LEN, in)) {
        if (strncmp(line, "#define", 7) == 0) {
            continue;
        }

        char output[MAX_LEN];
        strncpy(output, line, MAX_LEN - 1);
        output[MAX_LEN - 1] = '\0';

        expandMacros(output, MAX_LEN);
        fputs(output, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
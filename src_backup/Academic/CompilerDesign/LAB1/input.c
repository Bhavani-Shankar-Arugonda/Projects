#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_MACROS 50
#define MAX_LEN 500

typedef struct {
    char name[100];
    char body[MAX_LEN];
    int is_function; // 1 if function-like, 0 if object-like
} Macro;

Macro macros[MAX_MACROS];
int macro_count = 0;

void parseMacro(char *line) {
    if(macro_count >= MAX_MACROS) return;
    
    char *ptr = line + 7; // skip "#define"
    while(*ptr == ' ' || *ptr == '\t') ptr++;
    
    // Extract macro name
    char name[100];
    int i = 0;
    while(i < 99 && *ptr != '(' && *ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n') {
        name[i++] = *ptr++;
    }
    name[i] = '\0';
    strcpy(macros[macro_count].name, name);
    
    // Check if function-like or object-like
    if(*ptr == '(') {
        macros[macro_count].is_function = 1;
        // Skip parameters - we don't need to parse them for simple replacement
        while(*ptr != ')' && *ptr != '\0') ptr++;
        if(*ptr == ')') ptr++;
    } else {
        macros[macro_count].is_function = 0;
    }
    
    // Extract body
    while(*ptr == ' ' || *ptr == '\t') ptr++;
    int len = 0;
    while(len < MAX_LEN - 1 && *ptr != '\0' && *ptr != '\n') {
        macros[macro_count].body[len++] = *ptr++;
    }
    macros[macro_count].body[len] = '\0';
    
    macro_count++;
}

int isWordBoundary(char c) {
    return !isalnum(c) && c != '_';
}

void expandMacros(char *output, int max_len) {
    for (int m = 0; m < macro_count; m++) {
        char temp[MAX_LEN];
        char *ptr = output;
        int dest = 0;
        int name_len = strlen(macros[m].name);

        if (macros[m].is_function) {
            // Function-like macro: look for macroName followed by '('
            while (*ptr != '\0' && dest < max_len - 1) {
                if (strncmp(ptr, macros[m].name, name_len) == 0 && *(ptr + name_len) == '(') {
                    ptr += name_len + 1; // skip name and '('
                    
                    // Skip the argument list
                    int depth = 1;
                    while (*ptr != '\0' && depth > 0) {
                        if (*ptr == '(') depth++;
                        else if (*ptr == ')') depth--;
                        ptr++;
                    }
                    
                    // Replace with macro body
                    char *body = macros[m].body;
                    while (*body != '\0' && dest < max_len - 1) {
                        temp[dest++] = *body++;
                    }
                } else {
                    temp[dest++] = *ptr++;
                }
            }
        } else {
            // Object-like macro
            while (*ptr != '\0' && dest < max_len - 1) {
                if (strncmp(ptr, macros[m].name, name_len) == 0) {
                    char before = (ptr == output) ? ' ' : *(ptr - 1);
                    char after = *(ptr + name_len);
                    
                    if (isWordBoundary(before) && isWordBoundary(after)) {
                        // Replace with body
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
    
    if(!in || !out) {
        printf("Error opening files\n");
        return 1;
    }
    
    char line[MAX_LEN];
    
    // First pass: collect macros
    while(fgets(line, MAX_LEN, in)) {
        if(strncmp(line, "#define", 7) == 0) {
            parseMacro(line);
        }
    }
    
    // Second pass: expand and write
    rewind(in);
    while(fgets(line, MAX_LEN, in)) {
        if(strncmp(line, "#define", 7) == 0) {
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
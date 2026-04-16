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
    char arguments[MAX_ARGUMENTS][100];
} Macro;

Macro macros[MAX_MACROS];
int macro_count = 0;

void trimWhitespace(char *str) {
    int start = 0, end = strlen(str) - 1;
    while (start <= end && (str[start] == ' ' || str[start] == '\t')) start++;
    while (end >= start && (str[end] == ' ' || str[end] == '\t')) end--;
    int len = end - start + 1;
    memmove(str, str + start, len);
    str[len] = '\0';
}

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

    macros[macro_count].argument_count = 0;

    if (*ptr == '(') {
        macros[macro_count].is_function = 1;
        ptr++;
        int arg_idx = 0;

        while (*ptr != ')' && *ptr != '\0') {
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            
            int s = 0;
            while (*ptr != ',' && *ptr != ')' && *ptr != '\0' && s < 99) {
                macros[macro_count].arguments[arg_idx][s++] = *ptr++;
            }
            macros[macro_count].arguments[arg_idx][s] = '\0';
            trimWhitespace(macros[macro_count].arguments[arg_idx]);
            
            if (s > 0) {
                arg_idx++;
                macros[macro_count].argument_count++;
            }

            if (*ptr == ',') {
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

void extractArguments(char *args_str, char args[MAX_ARGUMENTS][MAX_LEN], int *arg_count) {
    *arg_count = 0;
    int depth = 0;
    int current_arg_len = 0;
    
    while (*args_str != '\0' && *arg_count < MAX_ARGUMENTS) {
        if (*args_str == '(' || *args_str == '{' || *args_str == '[') {
            depth++;
            args[*arg_count][current_arg_len++] = *args_str;
        } else if (*args_str == ')' || *args_str == '}' || *args_str == ']') {
            depth--;
            args[*arg_count][current_arg_len++] = *args_str;
        } else if (*args_str == ',' && depth == 0) {
            args[*arg_count][current_arg_len] = '\0';
            trimWhitespace(args[*arg_count]);
            (*arg_count)++;
            current_arg_len = 0;
        } else {
            args[*arg_count][current_arg_len++] = *args_str;
        }
        args_str++;
    }
    
    args[*arg_count][current_arg_len] = '\0';
    trimWhitespace(args[*arg_count]);
    if (current_arg_len > 0) (*arg_count)++;
}

void expandFunctionMacro(Macro *macro, char *args_str, char *result, int max_len) {
    char actual_args[MAX_ARGUMENTS][MAX_LEN];
    int actual_arg_count = 0;
    
    extractArguments(args_str, actual_args, &actual_arg_count);

    if (actual_arg_count != macro->argument_count) {
        strncpy(result, "", max_len);
        return;
    }

    char *body = macro->body;
    int result_len = 0;
    
    while (*body != '\0' && result_len < max_len - 1) {
        if (isalpha(*body) || *body == '_') {
            int param_len = 0;
            char param[100];
            char *body_ptr = body;
            
            while ((isalnum(*body_ptr) || *body_ptr == '_') && param_len < 99) {
                param[param_len++] = *body_ptr++;
            }
            param[param_len] = '\0';

            int found = -1;
            for (int i = 0; i < macro->argument_count; i++) {
                if (strcmp(param, macro->arguments[i]) == 0) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                char *arg_value = actual_args[found];
                while (*arg_value != '\0' && result_len < max_len - 1) {
                    result[result_len++] = *arg_value++;
                }
                body = body_ptr;
            } else {
                result[result_len++] = *body++;
            }
        } else {
            result[result_len++] = *body++;
        }
    }
    
    result[result_len] = '\0';
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
                    char *args_start = ptr + name_len + 1;
                    char *args_end = args_start;
                    int depth = 1;
                    
                    while (*args_end != '\0' && depth > 0) {
                        if (*args_end == '(') depth++;
                        else if (*args_end == ')') depth--;
                        if (depth > 0) args_end++;
                    }

                    char args_str[MAX_LEN];
                    int args_len = args_end - args_start;
                    strncpy(args_str, args_start, args_len);
                    args_str[args_len] = '\0';

                    char expanded[MAX_LEN];
                    expandFunctionMacro(&macros[m], args_str, expanded, MAX_LEN);

                    char *body = expanded;
                    while (*body != '\0' && dest < max_len - 1) {
                        temp[dest++] = *body++;
                    }

                    ptr = args_end + 1;
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
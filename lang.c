#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The maximum number of variables available
#define MAX_VAR_SIZE 20
#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 30
#define BREAK -1
#define INTEGER 0
#define STRING 1
#define OPERATOR 2
#define ASSIGN 3
#define END 4
#define PRINT 5
#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define DIVIDE 4
#define MODULO 5


typedef struct {
    char name[MAX_TOKEN_LEN];
    int value;
} var;

typedef struct {
    char string[MAX_TOKEN_LEN];
    int type;           // 0 -> int, 1 -> identifier, 2 -> operator, 3 -> assignment, -1 -> expression break, 4 -> end of tokens, 5 -> print
} token;

var vars[MAX_VAR_SIZE];
token tokens[MAX_TOKENS];
int token_no = 0;
int totalVars = -1;


// function prototypes here
char *load_file(char* filename);
void tokenize(char* buff);
char* get_token(char *ch, int type);
void execute(token *tokens);
token* statement(token* statement);
int LHS(token** curr);
int RHS(token** curr);
int getNum(char* ch);
int operate(int eval, int value, int operation);
int searchVar(char string[]);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./lang <filename>.txt\n");
        return 0;
    }

    char *buff = load_file(argv[1]);

    tokenize(buff);
    free(buff);

    execute(tokens);

    return 0;
}

char *load_file(char* filename)
{
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buff = (char *) malloc((size + 1) * sizeof(char));
    fread(buff, 1, size, file);
    buff[size] = '\0';

    fclose(file);
    return buff;
}

void tokenize(char* buff)
{
    char *ch = buff;

    while (*ch)
    {
        if (*ch == '\n')
        {
            tokens[token_no].type = BREAK;
            token_no++;
            ch++;
            continue;
        }

        if (*ch == '=')
        {
            tokens[token_no].type = ASSIGN;
            token_no++;
            ch++;
            continue;
        }
        
        if (isspace(*ch))
        {
            ch++;
            continue;
        }

        if ((*ch >= 'A' && *ch <= 'Z') || (*ch >= 'a' && *ch <= 'z'))
        {
            ch = get_token(ch, STRING);
            continue;
        }

        if (*ch >= '0' && *ch <= '9')
        {
            ch = get_token(ch, INTEGER);
            continue;
        }

        if (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/' || *ch == '%')
        {
            ch = get_token(ch, OPERATOR);
            continue;
        }

        printf("ERROR: Unknown character.\n");
        break;
    }

    tokens[token_no].type = END;
}

char* get_token(char *ch, int type)
{
    char tmp[MAX_TOKEN_LEN];
    int i = 0;

    while (!isspace((int) *ch) && *ch)
    {
        tmp[i++] = *(ch++);
    }
    tmp[i] = '\0';

    strcpy(tokens[token_no].string, tmp);
    tokens[token_no].type = type;
    token_no++;

    return ch;
}

void execute(token *tokens)
{
    token* curr = tokens;

    for (int i = 0; i < MAX_TOKENS; i++)
    {
        char *print = "print\0";
        if (strcmp(tokens[i].string, print) == 0)
        {
            tokens[i].type = PRINT;
        }
    }

    for (int i = 0; i < MAX_VAR_SIZE; i++)
    {
        vars[i].name[0] = '\0';
    }
    
    while (curr->type != END)
    {
        curr = statement(curr);
    }
}

token* statement(token* statement)
{
    token* curr = statement;

    if (curr->type == PRINT)
    {
        curr++;
        int eVal = RHS(&curr);
        printf("%d\n", eVal);
        return curr;
    }

    int currVar = LHS(&curr);

    if (curr->type != ASSIGN)
    {
        printf("Syntax Error: Expected '=' after identifier.\n");
    }

    curr++;
    int expressionVal = RHS(&curr);
    vars[currVar].value = expressionVal;

    return curr;
}

int LHS(token** curr)
{
    int currVar;

    if (searchVar((*curr)->string) != -1)
    {
        currVar = searchVar((*curr)->string);
    }
    else
    {
        totalVars++;
        currVar = totalVars;
        strcpy(vars[currVar].name, (*curr)->string);
    }

    (*curr)++;
    return currVar;
}

int RHS(token** curr)
{
    int expressionVal = 0;
    int operator = ADD;

    while ((*curr)->type != BREAK)
    {
        if ((*curr)->type == INTEGER)
        {
            expressionVal = operate(expressionVal, getNum((*curr)->string), operator);
        }
        else if ((*curr)->type == STRING)
        {
            expressionVal = operate(expressionVal, vars[searchVar((*curr)->string)].value, operator);
        }

        (*curr)++;

        if ((*curr)->type == OPERATOR)
        {
            char op = (*curr)->string[0];
            if (op == '+') operator = ADD;
            if (op == '-') operator = SUBTRACT;
            if (op == '*') operator = MULTIPLY;
            if (op == '/') operator = DIVIDE;
            if (op == '%') operator = MODULO;

            (*curr)++;
        }
    }

    (*curr)++;
    return expressionVal;
}

int getNum(char* ch)
{
    int number = 0;
    while (*ch >= '0' && *ch <= '9')
    {
        number *= 10;
        number += *ch - '0';
        ch++;
    }

    return number;
}

int operate(int eval, int value, int operation)
{
    switch (operation)
    {
        case ADD:
        {
            return eval + value;
            break;
        }
        case SUBTRACT:
        {
            return eval - value;
            break;
        }
        case MULTIPLY:
        {
            return eval * value;
            break;
        }
        case DIVIDE:
        {
            return eval / value;
            break;
        }
        case MODULO:
        {
            return eval % value;
        }
        default:
        {
            return value;
        }
    }
}

int searchVar(char string[])
{
    for (int i = 0; i < MAX_VAR_SIZE; i++)
    {
        if (strcmp(string, vars[i].name) == 0) return i;
    }

    return -1;
}
#include <stdio.h>
#include <stdlib.h>

// The maximum number of variables available
#define MAX_VAR_SIZE 10

typedef struct variable {
    int value;              // All variables are int type with single letter names
    char name;
} var;

int LHS(FILE *file, int *ch, var *vars);
void crossEqualSign(int *ch, FILE *file);
int RHS(FILE *file, int *ch, var *vars);
int getNum(int *ch, FILE *file);
int tokenType(char c, var *vars);
void print_vars(var *vars);
int isWhitespace(char c);
int operate(int eval, char operation, int value);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./lang <filename>.txt\n");
        return 0;
    }
    
    var vars[MAX_VAR_SIZE];

    for (int j = 0; j < MAX_VAR_SIZE; j++)
    {
        vars[j].value = 0;
        vars[j].name = '\0';
    }

    FILE *file = fopen(argv[1], "r");
    int* ch = (int *) malloc(sizeof(int));

    //*ch = fgetc(file);
    while ((*ch = fgetc(file)) != EOF)
    {
        // Break the file into lines
        while (*ch != '\n' && *ch != EOF)
        {
            int var_i = LHS(file, ch, vars);
            crossEqualSign(ch, file);
            int eval = RHS(file, ch, vars);

            vars[var_i].value = eval;
        }
    }

    // Print all the exisiting variables
    print_vars(vars);

    fclose(file);

    return 0;
}



int LHS(FILE *file, int *ch, var *vars)
{
    while (isWhitespace(*ch))
    {
        *ch = fgetc(file);
    }


    if (*ch >= 'a' && *ch <= 'z')
    {
        int i = 0;
        // Checks if this variable already exists
        while (vars[i].name != '\0')
        {
            if (vars[i].name == *ch)
            {
                return i;
            }

            i++;
        }

        // Creates new variable
        vars[i].name = *ch;
        return i;
    }
    else
    {
        return -1;
    }
}

void crossEqualSign(int *ch, FILE *file)
{
    while (*ch != '=')
    {
        *ch = fgetc(file);
    }

    *ch = fgetc(file);

    return;
}

int RHS(FILE *file, int *ch, var *vars)
{
    int eval = 0;
    char operation = '+';   // initialized + because eval is 0

    while (*ch != '\n')
    {
        while (isWhitespace(*ch))
        {
            *ch = fgetc(file);
        }
        
        while (!isWhitespace(*ch) && *ch != '\n')
        {
            if (*ch == EOF)
            {
                return eval;
            }

            int tType = tokenType(*ch, vars);

            if (tType >= 0 && tType < MAX_VAR_SIZE)
            {
                eval = operate(eval, operation, vars[tType].value);
                *ch = fgetc(file);
            }
            else if (tType == MAX_VAR_SIZE)
            {
                operation = *ch;
                *ch = fgetc(file);
            }
            else if (tType > MAX_VAR_SIZE)
            {
                eval = operate(eval, operation, getNum(ch, file));
            }
            else
            {
                return -1;
            }
        }
    }

    return eval;
}

int getNum(int *ch, FILE *file)
{
    int number = 0;
    while (*ch >= '0' && *ch <= '9')
    {
        number *= 10;
        number += *ch - '0';
        *ch = fgetc(file);
    }

    return number;
}

int tokenType(char c, var *vars)
{

    /*
    Returns: 
        variable index for existing variable (1 - max)
        max for operations
        max + 1 for literal integers
        -1 elsewhere
    */

    for (int i = 0; i < MAX_VAR_SIZE; i++)
    {
        if (vars[i].name == c)
        {
            return i;
        }
    }
    
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
    {
        return MAX_VAR_SIZE;
    }

    if (c >= '0' && c <= '9')
    {
        return MAX_VAR_SIZE + 1;
    }

    return -1;
}

void print_vars(var *vars)
{
    for (int i = 0; i < 10; i++)
    {
        if (vars[i].name != '\0')
        {
            printf("%c = %d\n", vars[i].name, vars[i].value);
        }
    }
}


int isWhitespace(char c)
{
    if (c == ' ' || c == '\t')
    {
        return 1;
    }

    return 0;
}

int operate(int eval, char operation, int value)
{
    switch (operation)
    {
        case '+':
        {
            return eval + value;
            break;
        }
        case '-':
        {
            return eval - value;
            break;
        }
        case '*':
        {
            return eval * value;
            break;
        }
        case '/':
        {
            return eval / value;
            break;
        }
        case '%':
        {
            return eval % value;
        }
        default:
        {
            return value;
        }
    }
}
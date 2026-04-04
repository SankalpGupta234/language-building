#include <stdio.h>
#include <stdlib.h>

typedef struct variable {
    int value;
    char name;
} var;

int operate(int eval, char operation, int value);

int main(int argc, char *argv[])
{
    // Let's take a maximum of 10 variables in our program
    // All variables are int type in our language
    var vars[10];
    int num_tmp = 0;
    int k = 0;
    int eval = 0;
    char operation = '\0';
    int variable;

    for (int j = 0; j < 10; j++)
    {
        vars[j].value = 0;
        vars[j].name = '\0';
    }

    FILE *file = fopen(argv[1], "r");
    int character;

    character = fgetc(file);
    while (character != EOF)
    {
        // Break the file into lines
        while (character != '\n' && character != EOF)
        {
            int sideFlag = 0;
            // Break the expression into LHS and RHS

            // LHS
            while (character != '=' && character != EOF && sideFlag == 0)
            {
                // Should be a variable name with single small letter
                if (character >= 'a' && character <= 'z')
                {
                    // Check if the variable exists, create a new one if not
                    int varExists = 0;
                    for (int i = 0; i < k; i++)
                    {
                        if (vars[i].name == character)
                        {
                            varExists = 1;
                            variable = i;
                        }
                    }

                    if (varExists == 0)
                    {
                        vars[k].name = character;
                        variable = k;
                        k++;
                    }
                }
                character = fgetc(file);
            }

            sideFlag = 1;
            
            // RHS
            character = fgetc(file);
            while (character == ' ' || character == '\t' || character == '\r')
            {
                character = fgetc(file);
            }
            if (character == '+' || character == '-' || character == '*' || character == '/')
            {
                operation = character;
                character = fgetc(file);
                while (character == ' ' || character == '\t' || character == '\r')
                {
                    character = fgetc(file);
                }
            }

            // Taking an integer as a whole and storing it in num_tmp
            while (character >= '0' && character <= '9')
            {
                num_tmp *= 10;
                num_tmp += character - '0';
                character = fgetc(file);
            }

            // Will handle a single number or 2 numbers
            eval = operate(eval, operation, num_tmp);
            num_tmp = 0;

            // Identifying a variable on the RHS and replacing it with its value
            // Not actually replacing, but directly evaluating the result
            for (int i = 0; i < 10; i++)
            {
                if (vars[i].name == character)
                {
                    if (operation == '\0')
                    {
                        eval = vars[i].value;
                    }
                    else
                    {
                        eval = operate(eval, operation, vars[i].value);
                    }
                }
            }
        }

        // Resets operation after a line completes
        operation = '\0';

        vars[variable].value = eval;
        eval = 0;

        if (character == '\n')
        {
            character = fgetc(file);
        }
    }

    // Print all the exisiting variables
    for (int i = 0; i < 10; i++)
    {
        if (vars[i].name != '\0')
        {
            printf("%c = %d\n", vars[i].name, vars[i].value);
        }
    }

    fclose(file);

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
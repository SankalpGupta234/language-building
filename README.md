Version 2.0
=========

## Usage

Try the following:

```
gcc -o lang lang.c
./lang file.txt
```
You can do simple variable assignments and arithmetic operations in your .txt file like this:

```
apple = 3
banana = apple + 2
player2 = banana - apple + 4
```

Added print statements in v2.0, 

```
print player2
print apple

```

This will print the following to the console:

```
6
3
```

## Language Constraints

The following limits are set in the code, they can be changed by changing the appropriate parameters declared at the start.

The variable names can be strings of maximum length 10 characters containing any alphanumeric or special characters.

The program can have a maximum of 20 variables.

You can perform only arithmetic operations +, -, *, /, and %.

NOTE: The program requires an empty newline to be added at the end of the text file. You might get sengmentation faults without it.

## Operator Precedence

There is no pre-defined precedence of arithmetic operations. The parser will evaluate expressions from left to right.

Since there are no floating points, only integer division will be performed.


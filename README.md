**Finally Working!!!**

## Usage

Try the following:

```
gcc -o lang lang.c
./lang file.txt
```
You can do simple variable assignments and arithmetic operations in file.txt like this:

```
x = 3
y = x + 2
z = y - x + 4
```

The program should return you the final value of each variable:

```
x = 3
y = 5
z = 6
```

## Language Constraints

The parser is only able to handle variable names having a single lowercase letter.

The program can have a maximum of 10 variables.

You can perform only binary arithmetic operations +, -, *, /, and %.

# Operator Precedence

There is no pre-defined precedence of arithmetic operations. The parser will evaluate expressions from left to right.

Since there are no floating points, only integer division will be performed.


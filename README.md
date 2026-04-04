**Under Construction**

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
z = y - x
```

Ideally, the program should return you the final value of each variable:

```
x = 3
y = 5
z = 2
```

But since my code has bugs it will return something like

```
x = 3
y = 0
z = 0
```

so... yeah.

## Language Constraints

The parser is only able to handle variable names having a single lowercase letter.

The program can have a maximum of 10 variables.

You can perform only binary arithmetic operations +, -, *, /, and %.


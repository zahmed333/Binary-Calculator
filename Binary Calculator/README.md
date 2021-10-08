# Project 01: Binary calculator

## Overview
In this project, you'll implement a simple binary calculator that supports some basic operations on binary operands.

### Learning objectives
After completing this project, you should be able to:
* Negate and add integers encoded using two's complement
* Apply bitwise operations (not, or, and)
* Write and call functions in C
* Read/create/modify strings in C

### Logistics
The project is divided into two parts. Part A must be completed by **Thursday, September 16 at 11pm**. Part B, along with revisions to your code for Part A, must be completed by **Thursday, September 30 at 11pm**. 

You will receive feedback and a grade on Part A by **Friday, September 24**. You should review this feedback and attempt to revise your code to correct errors/deficiencies. For each error/deficiency you correct, you will earn back half of the points you lost. Note that you will not have an opportunity to revise your code or earn back points for Part B, so you should use the feedback you receive on Part A to avoid making similar mistakes in Part B.

### Important tips
* Read the entirety of the project description before you write any code.
* Work on the project over multiple sessions. Do not try to complete the project in a single session on the day (before) each part of the project is due. This will give you time to think about how to solve problems, allow you to ask questions, and result in better outcomes.
* Ensure you follow good program design, coding, testing, and debugging practices (details below).

## Getting started
Clone your repository on the COSC 208 servers. As a reminder, the steps are:
1. Click the opposing arrows icon in the lower-left corner of your VS Code window. Choose `Connect to Host...`, then select `cosc208.cs.colgate.edu`. 
2. A new VS Code window will open, and you will be prompted to enter your password (which you set in Lab 1). After you have authenticated, `SSH: cosc208.cs.colgate.edu` will appear after the opposing arrows icon in the lower-left of your VS Code window.
3. Click the source control icon on the left side of your VS Code window, the click the `Clone Repository` button. 
4. Select `Clone from GitHub` from the drop-down. 
5. Enter `colgate-cosc208-fall21/` in the `Repository name` text box, then select your `proj01` repository from the drop-down. 
6. VS Code will then allow you to select a directory in which to clone the repository; select your home directory—i.e., `/users/USERNAME` (where `USERNAME` is your Colgate username).

The code you need to write for this project will be added to the `binarycalc.c` file included in your repository. When you want to compile your code, run the command
```bash
$ make
```
in the terminal (excluding the dollar sign (`$`)). (Note: your terminal should start with `~/proj01-TEAMNAME` as your working directory; if not, use the `cd` command to change your working directory.) Running make will compile your code using the commands in the `Makefile` included in your repository. 

To use the binary calculator, run the command:
```bash
$ ./binarycalc "FORMULA"
```
replacing `FORMULA` with an acceptable binary formula (details below). For example:
```bash
$ ./binarycalc "10 + 11"
```
Make sure you include the leading `./` and specify the compiled executable file `binarycalc`, not the source code file `binarycalc.c`. Also, you **must include the double quotes around the formula**.

## Part A: Parse and extend binary formulas

### Check the binary formula
Your calculator must support binary formulas with the following format:
* An optional modifier (`~`, `-`)
* At least one and up to `MAX_DIGITS` ones and zeros
* A space
* An operator (`+`, `&`, `^`)
* A space
* An optional modifier (`~`, `-`)
* At least one and up to `MAX_DIGITS` ones and zeros

For example, the following are valid binary formulas:
* `1 + 0`
* `101 ^ 10`
* `~111 & 000`
* `10101010 + -01010101`

Similarly, the following are invalid binary formulas:
* `1+ 0` — formulas must contain a space before and after the operator
* `111` — formulas must contain an operation (`+`, `&`, `^`)
* `1 * 1` — formulas must contain a valid operation (`+`, `&`, `^`)
* `11 ^ 1~0` — modifiers (`~`, `-`) must appear before an operand
* `--10 ^ 11` — only one modifier can appear before each operand
* `102 + 101` — operands must contain only binary digits (i.e., ones and zeros)
* `10101010101010 + 11` — operands must contain fewer than `MAX_DIGITS` (default is 8) binary digits
* `0b11 + 0b00` — operands should not be proceeded by `0b`; all operands and results are expressed binary, so there is no need to identify the number base

If the user provides an invalid binary formula, your calculator should display the error message `Invalid binary formula` and exit.

### Zero-extend the operands
After verifying the binary formulas is valid, you must extend the length of each operand to `MAX_DIGITS` by prepending zeros to the front of the operand. For example, if the first operand is `1010` and `MAX_DIGITS` is 8, the operand should be extended to `00001010`. Your calculator should only extend operands, it should not shrink them. If the user enters an operand with more than `MAX_DIGITS`, this is an invalid formula.

Your calculator should print the formula with the extended operands. Below are several examples of valid binary formulas before and after the operands have been extended when `MAX_DIGITS` is 8:
* `1 + 0` becomes `00000001 + 00000000`
* `101 ^ 10` becomes `00000101 ^ 00000010`
* `~111 & 000` becomes `~00000111 & 00000000`
* `10101010 + -01010101` stays the same (both operators are already `MAX_DIGITS`)

Your code must work with **any** value for `MAX_DIGITS`. By default, this value is 8, but you can change the line on which `MAX_DIGITS` is defined to try your code with other values (e.g., `4` or `12`). You **must recompile** your code after you change `MAX_DIGITS`.

## Part B: Apply modifiers and operators

### Apply modifiers
Your first task for Part B is to apply the modifier symbols (if any) to the associated operands.

The modifier symbols have the following semantics (i.e., meaning):
* `~` — bitwise not (see _Dive Into Systems_ [Section 4.6.4](https://diveintosystems.org/antora/diveintosystems/1.0/Binary/bitwise.html#_bitwise_not)
* `-` — negation (see _Dive Into Systems_ [Section 4.3.2](https://diveintosystems.org/antora/diveintosystems/1.0/Binary/signed.html#_negation)

Your calculator should print the formula with the modified operands. Below are several examples of valid binary formulas before and after the modifiers have been applied:
* `00000001 + 00000000` stays the same (there are no modifiers)
* `00000101 ^ 00000010` stays the same (there are no modifiers)
* `~00000111 & 00000000` becomes `11111000 & 00000000`
* `10101010 + -01010101` becomes `10101010 + 10101011` 

### Apply operators
Your second task for Part B is to apply the operators to the modified operands.

The operator symbols have the following semantics (i.e., meaning):
* `+` — addition (see _Dive Into Systems_ [Section 4.4.1](https://diveintosystems.org/antora/diveintosystems/1.0/Binary/arithmetic_addition.html)
* `&` — bitwise and (see _Dive Into Systems_ [Section 4.6.1](https://diveintosystems.org/antora/diveintosystems/1.0/Binary/bitwise.html#_bitwise_and)
* `^` — bitwise xor (see _Dive Into Systems_ [Section 4.6.3](https://diveintosystems.org/antora/diveintosystems/1.0/Binary/bitwise.html#_bitwise_xor_exclusive_of)

Your calculator should print the result. Below are several examples of valid binary formulas before and after the operators have been applied:
* `00000001 + 00000000` becomes `00000001`
* `00000101 ^ 00000010` becomes `00000111`
* `11111000 & 00000000` becomes `00000000`
* `10101010 + 10101011` becomes `01010101`

If the operation results in overflow or underflow, the program should also print `Overflow` or `Underflow` after printing the result. For example, the last formula above results in underflow.

## Sample output
Here is a sample run of the program:
```bash
$ ./binarycalc "~1010 + 1111"
~00001010 + 00001111
11110101 + 00001111
00000100
```

Here is another example
```bash
$ ./binarycalc "1000000 + 1000000"
01000000 + 01000000
01000000 + 01000000
10000000
Overflow
```

## Program design

You **must follow good program design and coding practices**, including:
* Making multiple commits to your git repository — Do not wait until your entire program is working before you commit it to your git repository. You should commit your code each time you write and debug a piece of functionality (e.g., after writing and testing code to check the binary formula, after writing and testing the code for extending the length of operands, etc.)
* Properly indenting your code — Recall that indentation is not semantically significant in C, but it makes your code much easier to read.
* Using multiple functions — Do not put all of your code in the `main` function. You should use multiple functions, where each function: is Short, does One thing, takes Few parameters, and maintains a single level of Abstraction. In other words, follow the _SOFA_ criteria from COSC 101.
* Include comments — Each function (except for `main`), must be preceded by a short comment that describes what the function does. The body of the function must also include comments; generally, you should include a comment before each conditional statement, loop, and set of statements that perform some calculation. **Do not** include a comment for every line of code, and **do not** simply restate the code: e.g., `Checks if the length of the binary string is longer than MAX_DIGITS and prints "Invalid formula"` is a _bad_ comment, whereas `Ensures operand is not too long` is a _good_ comment.)

## Testing and debugging your code

You should test your code on a variety of formulas to ensure your code works correctly. Furthermore, you should write and test your code in stages. For example, after writing code to check the binary formula, test the code with both invalid and invalid formulas; then, write the code for extending the length of operands, and test the code with operands of varying lengths. 

Your repository includes a shell script (`test.sh`) that you can use to easily run your program on many different inputs. To use the script, run:
```bash
$ ./test.sh
```

The first step in debugging your code is to fix any errors or warnings output by the compiler. You may be tempted to ignore the warnings, but they almost always mean there is a bug in your code.

If the program compiles without errors or warnings but still doesn't work as expected, then add `printf` statements in strategic locations to help you understand what your program is doing.

## Submission instructions
You should **commit and push** your updated `binarycalc.c` file to your git repository by the deadlines for Part A and Part B. However, as noted above, do not wait until your entire program is working before you commit it to your git repository; you should commit your code each time you write and debug a piece of functionality. You should visit the GitHub page for your repository and view the log and the `binarycalc.c` file to confirm you have correctly committed and pushed your changes.
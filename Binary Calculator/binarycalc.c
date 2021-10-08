/********
 * Project 01: Binary calculator
 * COSC 208, Introduction to Computer Systems, Fall 2021
 ********/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIGITS 8
#define MAX_FORMULA_LEN (1 + MAX_DIGITS + 3 + 1 + MAX_DIGITS)
#define TRUE 1
#define FALSE 0
void negatingD(char nums[]);

/**checks to see if the value is overflow or underflow and will print out the respective response
 will continue if there is nothing **/
void checkFlow(int binary1, int binary2)
{
    if ((binary1 + binary2) < -128)
    {
        printf("Underflow\n");
        //Me and Luis can't figure the underflow thing out in time because we're both sick
        // but we tried, and theoretically it should work.
    }
    if ((binary1 + binary2) > 127)
    {
        printf("Overflow\n");
    }
}

/**
 * Convert from binary to decimal
 **/
int binary_to_decimal(char num[])
{
    int final = 0;
    int power = 0;
    // For loop for power to add up to decimal
    for (int x = (strlen(num) - 1); x > 0; x--)
    {
        if (num[x] == '1')
        {

            final += (1 * pow(2, power));
        }
        power++;
    }
    return final;
}

/**
 * Convert from decimal to binary
 **/
char *decimal_to_binary(int decimal)
{
    char *final = (char *)malloc(9);
    int index = 0;

    while (decimal > 0)
    {
        if (decimal % 2 == 0)
        {
            final[index] = '0';
        }
        else
        {
            final[index] = '1';
        }
        index++;
        decimal /= 2;
    }
    while (index != 8)
    {
        final[index] = '0';
        index++;
    }
    int j, len, temp;
    final[index] = '\0';
    len = strlen(final); // use strlen() to get the length of string to reverse

    // use for loop to iterate the string
    for (j = 0; j < len / 2; j++)
    {
        // temporary var to  hold the string
        temp = final[j];
        final[j] = final[len - j - 1];
        final[len - j - 1] = temp;
    }

    return final;
}

/**
 * Applies Bitwise Xor to 2 binary numbers
 **/
void bitXOr(int bin1, int bin2)
{
    int result = bin1 ^ bin2;
    char *answer = decimal_to_binary(result);
    printf("%s\n", answer);
    free(answer);
}

/**
 * Applies Bitwise and to 2 binary numbers
 **/
void bitAnd(int bin1, int bin2)
{
    int result = bin1 & bin2;
    char *answer = decimal_to_binary(result);
    printf("%s\n", answer);
    free(answer);
}

/**
 * adds the two binary numbers
 **/
void binAddition(int bin1, int bin2)
{
    int result = bin1 + bin2;
    char *answer = decimal_to_binary(result);
    printf("%s\n", answer);
    free(answer);
    checkFlow(bin1, bin2);
}

/**
 * checks for which operand and applies correct function
 **/
void applyingOperands(char operand, int bin1, int bin2)
{
    if (operand == '+')
    {
        binAddition(bin1, bin2);
    }
    else if (operand == '^')
    {
        bitXOr(bin1, bin2);
    }
    else if (operand == '&')
    {
        bitAnd(bin1, bin2);
    }
}

/**
 * applies modifier and changes to appropriate string
 **/
void applyModifiers(char *nums, char mod)
{
    if (mod == '~')
    {
        negatingD(nums);
    }
    else if (mod == '-')
    {
        negatingD(nums);
        nums[strlen(nums) - 1] = '1';
    }
}

/**
 * negates all digits in the binary
 **/
void negatingD(char *nums)
{
    for (int i = 0; i < strlen(nums); i++)
    {
        if (nums[i] == '0')
        {
            nums[i] = '1';
        }
        else
        {
            nums[i] = '0';
        }
    }
}

/**
 * Checks whether the optional modifiers are there
 **/
int optionalModifier(char check)
{
    if (check == '~' || check == '-')
    {
        return TRUE;
    }
    return FALSE;
}

//isspace already exists in lib

/**
 * checks whether operator is there
 **/
int operatorCheck(char check)
{
    if (check == '+' || check == '&' || check == '^')
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * checks whether digits are valid or not
 **/
int digitChecker(char digits[], int index)
{
    int counter = 0;
    while (digits[index] == '0' || digits[index] == '1')
    {
        if (counter > MAX_DIGITS)
        {
            return FALSE;
        }
        index++;
        counter++;
    }
    if (counter == 0)
    {
        return FALSE;
    }
    else
    {
        if (isspace(digits[index]) || digits[index] == '\0')
        {
            return index;
        }
        else
        {
            return FALSE;
        }
    }
    //if the digit passes all check then it will return the index left off at
}

/**
 * checks for modifier and digit together and returns index where left off at.
 **/
int combineModifierAndDigit(char str[], int index)
{
    int rValue;
    if (optionalModifier(str[index]) == TRUE)
    {
        index++;
        rValue = digitChecker(str, index);
        if (rValue != FALSE)
        {
            return rValue;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        rValue = digitChecker(str, index);
        if (rValue != FALSE)
        {
            return rValue;
        }
        else
        {
            return FALSE;
        }
    }
}
/**
 * checks for spaces and the operand
 * in the middle of the string
 **/
int spaceOperandChecker(char str[], int index)
{
    if (isspace(str[index]) && operatorCheck(str[index + 1]) && isspace(str[index + 2]))
    {
        return index + 3;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Extends the zeroes if needed
 **/
char *zeroExtends(char digits[], int indexl, int indexr)
{
    int bcIndex = 8;
    char *bc = (char *)malloc(sizeof(char) * 9);
    int index = 0;
    while (index != 8)
    {
        bc[index] = '0';
        index++;
    }
    bc[index] = '\0';
    while (indexr >= indexl)
    {
        bc[bcIndex] = digits[indexr];
        if (bc[bcIndex] == '~' || bc[bcIndex] == '-')
        {
            bc[bcIndex] = '0';
        }
        indexr--;
        bcIndex--;
    }
    printf("%s", bc);
    return bc;
}

/**
 * prints the equation through all conditionals of optional modifiers
 **/
void extendedPrint(char formula_str[], int bin1ri, int bin2li, int bin2ri)
{
    int op1 = 0;
    int op2 = 0;
    char *bin1;
    char *bin2;
    if (optionalModifier(formula_str[0]))
    {
        printf("%c", formula_str[0]);
        op1 = 1;
        bin1 = zeroExtends(formula_str, 1, bin1ri);
        printf("%c ", formula_str[bin1ri + 1]);
        if (optionalModifier(formula_str[bin2li]))
        {
            op2 = 1;
            printf("%c", formula_str[bin2li]);
        }
        bin2 = zeroExtends(formula_str, bin2li, bin2ri);
    }
    else
    {
        bin1 = zeroExtends(formula_str, 0, bin1ri);
        printf("%c ", formula_str[bin1ri + 1]);
        if (optionalModifier(formula_str[bin2li]))
        {
            op2 = 1;
            printf("%c", formula_str[bin2li]);
        }
        bin2 = zeroExtends(formula_str, bin2li, bin2ri);
    }
    printf("\n");
    if (op1)
    {
        bin1[strlen(bin1) - 1] = '\0';
        applyModifiers(bin1, formula_str[0]);
    }
    if (op2)
    {
        bin1[strlen(bin1) - 1] = '\0';
        applyModifiers(bin2, formula_str[bin2li]);
    }
    int bin1D = binary_to_decimal(bin1);
    int bin2D = binary_to_decimal(bin2);
    if (op1 == FALSE && op2 == FALSE)
    {
        printf("%s%c %s\n", bin1, formula_str[bin1ri + 1], bin2);
        bin1D /= 2;
    }
    else
    {
        printf("%s %c %s\n", bin1, formula_str[bin1ri + 1], bin2);
    }

    applyingOperands(formula_str[bin1ri + 1], bin1D, bin2D);
    //free(bin1);
    //free(bin2);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Provide a single, valid binary formula\n");
        return 1;
    }

    if (strlen(argv[1]) > MAX_FORMULA_LEN)
    {
        printf("Invalid binary formula\n");
        return 1;
    }

    char formula_str[MAX_FORMULA_LEN + 1];
    strcpy(formula_str, argv[1]);

    int bin1ri = combineModifierAndDigit(formula_str, 0);
    if (bin1ri != FALSE)
    {
        int bin2li = spaceOperandChecker(formula_str, bin1ri);
        if (bin2li != FALSE)
        {
            int bin2ri = combineModifierAndDigit(formula_str, bin2li);
            if (bin2ri != FALSE)
            {
                extendedPrint(formula_str, bin1ri, bin2li, bin2ri);
            }
            else
            {
                printf("Invalid binary formula\n");
                return 1;
            }
        }
        else
        {
            printf("Invalid binary formula\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid binary formula\n");
        return 1;
    }
}

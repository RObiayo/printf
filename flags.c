#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)/*the `get_flags` function of integer type is declared with two arguments, a pointer to a constant character array `format` and a pinter to the integer `i`*/
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};/*several variables used with the function `get_flags` are declared and initialized. Integer variables `j` and `i` are used as counters within the loop. `flags` variable holds the the active flags, `FLAGS_CH`, a constant character array, holds the flag characters like `#`, `FLAGS_ARR`, a constant integer array, holds the flag values associated with each character*/

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)/*a for loop that initializes `curr_i` to the value of the integer pointed to by `i` plus 1. The loop continues while the character at the `curr_i` index of the `format` string is not the null terminator ('\0'). After each iteration, the loop increments `curr_i`*/
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)/*Within the previous for loop, another for loop initializes `j` to 0 and continues while the character at the `j` index of the `FLAGS_CH` array is not the null terminator ('\0')*/
			if (format[curr_i] == FLAGS_CH[j])/* The loop checks if the character at the `curr_i` index of the `format` string matches the character at the `j` index of the `FLAGS_CH` array*/
			{
				flags |= FLAGS_ARR[j];
				break;/*If there is a match, the corresponding flag value in the `FLAGS_ARR` array is OR'd with the `flags` variable using the bitwise OR operator `|=` and the loop is broken using the `break` statement*/
			}

		if (FLAGS_CH[j] == 0)/*After the inner for loop, the function checks if the character at the `j` index of the `FLAGS_CH` array is the null terminator ('\0')*/
			break;/* If it is, the outer for loop is broken using the `break` statement*/
	}

	*i = curr_i - 1;/*Finally, the function sets the value of the integer pointed to by `i` to `curr_i - 1`*/

	return (flags);/*the function returns the `flags` variable as the function's result*/
	

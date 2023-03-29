#include "main.h"// This line includes the header file main.h

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;// Define and initialize variables

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)// Loop through the formatted string starting at the next index width by 10 and add the value of the digit
	{
		if (is_digit(format[curr_i]))// If the current character is an asterisk (*), skip to the next character, and set the width to the next argument in the list
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;// If the current character is neither a digit nor an asterisk, exit the loop
	}

	*i = curr_i - 1;// Update the current index (i) to the current index minus 1

	return (width);// Return the calculated width
}

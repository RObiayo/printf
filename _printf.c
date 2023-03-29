#include "main.h"

void print_buffer(char buffer[], int *buff_ind);/*The function prototype, `print_buffer` is declared and takes two arguments,
`buffer[]` which is a character array and `*buff_find` which is a pointer to an integer*/

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)/*The function `_printf` is defined. It returns an integer type that represents the number of that are passed using the variable arguments list `(...)`. for the first argument, the funtion takes a format string.*/
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;/*variables used within the `_printf` function are declared*/
	va_list list;/*`list` variable iterates through the variable arguments passed into the function `_printf`*/
	char buffer[BUFF_SIZE];/*the array of characters, `buffer`, is used to store the output of the `_printf` function*/

	if (format == NULL)
		return (-1);

	va_start(list, format);/*the `va_list` object, `list` is initialized to start iterating over the variable arguments passed to the function after the format argument*/

	for (i = 0; format && format[i] != '\0'; i++)/*using a `for` loop, `i` is initialized to zero and a loop iterates through each character in the format string `format` until it encounters a null byte character `/0`. The loop also checks if the `format` string is not `NULL`*/
	{
		if (format[i] != '%')/*this line checks if the current character in the `format` string is not `%`*/
		{
			buffer[buff_ind++] = format[i];/*if the current character in the `format` string is not `%`, the character is added to the `buffer` array and increments the `buff_ind` variable that represents the index to add the next character to the buffer*/ 
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);/*if the variable `buff_find` is equal to `BUFF_SIZE`, the `_printf` function calls the `print_buffer` function to flush out the buffer and print the contents to the standard output stream*/
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);/*if the current character in the `format` string is `%`, the `_printf` function is called to flush out the contents of the buffer and print its contents to the standard output stream*/
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);/*several helper functions are called to parse the `format` string an extract relevant formatting information;flags, width, precision and size*/ 
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);/*after parsing the format string and getting the relevant information, the `_printf` function calls the `handle_print` function to handle printing the formatted output to the buffer. The `handle_print` function returns the number of characters printed(printed)*/ 
			if (printed == -1)
				return (-1);/*If the `handle_print` function returns -1 , indicating that an error has occurred, the `_printf` function returns -1*/
			printed_chars += printed;/*the number of variables printed, `printed`, is added to the `printed_chars` variable*/
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

#include "main.h"// include header file `main.h`
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;// declare variables to  be used within the `handle_print` function
	fmt_t fmt_types[] = {// define struct for mapping format characters to functions that handle them
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)// loop through the format characters until we find one that matches the current format string character
		if (fmt[*ind] == fmt_types[i].fmt)// call the appropriate function for the format character
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')// if we didn't find a matching format character, handle it as an unknown specifier
	{
		if (fmt[*ind] == '\0')
			return (-1);// end of string, return error code
		unknow_len += write(1, "%%", 1);// write out a single percent sign
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);// if there was a space before the percent sign, write out another space
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);// if there was a width specifier, move back to the beginning of the specifier and return
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);// write out the unknown specifier character
		return (unknow_len);// return the number of characters printed
	}
	return (printed_chars);
}

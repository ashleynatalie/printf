#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/

/**
 * print_unsigned - Prints an unsigned number
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	int i = BUFF_SIZE - 2;

	unsigned long int num = va_arg(args, unsigned long int);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buf, fl, wd, pr, sz));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL ****************/

/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	int i = BUFF_SIZE - 2;

	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wd);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (fl & F_HASH && init_num != 0)
		buf[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buf, fl, wd, pr, sz));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	return (print_hexa(args, "0123456789abcdef", buf, fl, 'x', wd, pr, sz));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	return (print_hexa(args, "0123456789ABCDEF", buf, fl, 'X', wd, pr, sz));
}

/************** PRINT HEX NUM IN LOWER OR UPPER **************/

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: List of arguments
 * @map_to: Array of values to map the number to
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @flag_ch: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list args, char map_to[], char buf[], int fl, char flag_ch,
		int wd, int pr, int sz)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wd);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = map_to[num % 16];
		num /= 16;
	}

	if (fl & F_HASH && init_num != 0)
	{
		buf[i--] = flag_ch;
		buf[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buf, fl, wd, pr, sz));
}

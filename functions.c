#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a character
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	char c = va_arg(args, int);

	return (handle_write_char(c, buf, fl, wd, pr, sz));
}

/************************* PRINT STRING *************************/

/**
 * print_string - Prints a string
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	int len = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wd);
	UNUSED(pr);
	UNUSED(sz);

	if (str == NULL)
	{
		str = "(null)";
		if (pr >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;
	if (pr >= 0 && pr < len)
		len = pr;
	if (wd > len)
	{
		if (fl & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = wd - len; i > 0; i--)
				write(1, " ", 1);
			return (wd);
		}
		else
		{
			for (i = wd - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (wd);
		}

	}

	return (write(1, str, len));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	UNUSED(args);
	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wd);
	UNUSED(pr);
	UNUSED(sz);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

/**
 * print_int - Print int
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	int i = BUFF_SIZE - 2;
	int is_neg = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, sz);

	if (n == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_neg, i, buf, fl, wd, pr, sz));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - Prints an unsigned number in binary representation
 * @args: List of arguments
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wd: Width
 * @pr: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list args, char buf[], int fl, int wd, int pr, int sz)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wd);
	UNUSED(pr);
	UNUSED(sz);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

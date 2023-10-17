#include "shell.h"
/**
* _erroratoi - converts a string to an intger
* @str: the string to be converted
* Return: 0 if a strung,  converted number otherwise, -1 on error
*/

int _erroratoi(char *str)
{
	int i = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			output *= 10;
			output += (str[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}
/**
* print_err - print an error message
* @information: return info struct
* @errstr: string containing specified error message
*
* Return: 0 if no number in the string, converted number otherwise, -1 on error
*/
void print_err(information_t *information, char *errstr)
{
	_eput(information->fname);
	_eput(": ");
	print_dec(information->line_count, STDERR_FILENO);
	_eput(information->argv[0]);
	_eput(": ");
	_eput(errstr);
}
/**
* print_dec - prints a decimal integer
* @in: the input
* @fd: the fieldscriptor
*
* Return: number of chars printed
*/
int print_dec(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchars;
	if (in < 0)
	{
		_abs = -in;
		__putchar('-');
		count++;
	}
	else
		_abs = in;
	curr = _abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}
/**
* _convert_num - convert function, a clone of itoa
* @number: number
* @b: base
* @flags: argiments flags
*
* Return: string
*/
char *_convert_num(long int number, int b, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
* rem_coms - replace first instance of '#' with '\0'
* @buff: address of the string to be modified
*
* Return: always 0
*/
void rem_coms(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

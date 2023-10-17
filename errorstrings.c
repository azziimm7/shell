#include "shell.h"
/**
 * _eput - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eput(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] !=  '\0')
	{
		_eputchars(str[i]);
		i++;
	}
}
/**
 * _eputchars - writes a char to stderr
 * @ch: the char to print
 *
 * Return: on success 1, errno is set, on error -1
 */
int _eputchars(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
/**
 * _putfds - write the char ch to the given fd
 * @ch: the char to prit
 * @fds: the field scriptor
 *
 * Return: on success 1, errno is set, on error -1
 */
int _putfds(char ch, int fds)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fds, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
/**
 * _putsfds - prints an input string
 * @str: the string to be printed
 * @fds: the fieldscriptor
 *
 * Return: the num of char to put
 */
int _putsfds(char *str, int fds)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfds(*str++, fds);
	}
	return (1);
}




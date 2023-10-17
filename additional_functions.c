#include "shell.h"

/**
* interactive - return true if the shell is in interacive mode
* @information: struct address
*
* Return: 1 if interactive mode , 0 otherwise
*
*/
int interactive(information_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}
/**
* is_delim - checks if a char is a delimiter
* @c: the char to check
* @delimiter: the delimiter string
*
* Return: 1 if true 0 otherwise
*/
int is_delim(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
* _is_alpha - chacks for alphapetic char
* @ch: the char input
*
* Return: 1 if alphapet 0 otherwise
*/
int _is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
/**
* _isdigit - Check for a digit.
* @c: The character to check
* Return: 1 if c is digit 0 otherwise.
*/
int _isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
* is_atoi - Check if a string is convertable to digit
* @str: The string to check
*
* Return: If the string is convertable - 1
*	   otherwise - 0
*/
int is_atoi(char *str)
{
	while (str)
	{
		if (_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}


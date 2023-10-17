#include "shell.h"
/**
 * *start_with - checks if needle starts with heystack
 * @needle: the substring to find
 * @heystack: string to search
 *
 * Return: pointer to the next char of heystack NULL otherwise
 */

char *start_with(const char *heystack, const char *needle)
{
	while (*needle)
		if (*needle != *heystack++)
			return (NULL);
	return ((char *)heystack);
}
/**
 * _strcat - concatenate two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: A pointer to the destination
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
/**
 * _puts - prints an input strings
 * @src: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *src)
{
	unsigned int i = 0;

	if (!src)
		return;
	while (src[i] != '\0')
	{
		_putchar(src[i]);
		i++;
	}
}
/**
 * _putchar - writes a char c to the stdout
 * @c: the char to print
 * Return: 1 on success, -1 on error , and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;

	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, &buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}




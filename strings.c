#include "shell.h"
/**
 * _strlen - Returns the length of the string
 * @str: The string to calculate its length
 *
 * Return: The length of the string
 */
int _strlen(const char *str)
{
	unsigned int i, length = 0;

	i = 0;

	while (str[i] != '\0')
	{
		length++;
		i++;
	}

	return (length);
}
/**
 * _strdup - Copy a string given as a parameter into
 *		  a newly allocated memory space
 * @str: The string to be copied
 *
 * Return: A pointer to the duplicated string, NULL otherwise
 */
char *_strdup(const char *str)
{
	unsigned int i, lens;
	char *p;

	if (str == NULL)
		return (NULL);

	lens = _strlen(str);

	p = malloc((lens + 1) * sizeof(char));

	if (p == NULL)
		return (p);

	for (i = 0; i <= lens; i++)
		*(p + i) = *(str + i);

	return (p);
}

/**
 * _strcopy - Copy a string in one variable into another variable
 * @src: The string to be copied
 * @dest: The destination of the copied string
 *
 * Return: The pointer to the destination.
 */
char *_strcopy(char *dest, const char *src)
{
	int i = 0;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcomp - Compare two strings
 * @str1: The first string
 * @str2: The string to compare with the first
 * Return: Zero if both strings are identical,
 *	   greater than zero when the matching
 *	   character of left string has greater
 *	   ASCII value than the character of
 *	   the right string, less than zero
 *	   when the left character has a smaller
 *	   value.
 */

int _strcomp(const char *str1, const char *str2)
{
	unsigned int i = 0;

	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;

	return (str1[i] - str2[i]);
}
/**
 * _strchr - Locate a character in a string
 * @str: The string to be searched
 * @c: The character to find
 *
 * Return: A pointer to the first occurrence of the character c
 *	   in the string s, or NULL if the character is
 *	   not found
 */

char *_strchr(char *str, char c)
{
	for ( ; *str; str++)
	{
		if (*str == c)
			return (str);
		if (c == '\0')
			return (str);
	}
	return (0);
}

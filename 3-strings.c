#include "shell.h"
/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: number of chars to be copied
 *
 * Return: Apointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 * *_strncat - concatinates two strings
 * @str1: the first string
 * @str2: the second string
 * @n: maximum number of bytes to be used
 *
 * Return: the concatenated string
 */
char *_strncat(char *str1, char *str2, int n)
{
	int i, j;
	char *s = str1;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
		i++;
	while (str2[j] != '\0' && j < n)
	{
		str1[i] = str2[j];
		i++;
		j++;
	}
	if (j < n)
		str1[i] = '\0';
	return (s);
}
/**
 * **strtoword - splits a string into a words
 * @str: the input string
 * @d: the delimiter
 *
 * Return: A pointer to an array of strings, NULL otherwise
 */

char **strtoword(char *str, char *d)
{
	int i, j, k, m, numofwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numofwords++;
	if (numofwords == 0)
		return (NULL);
	s = malloc((i + numofwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numofwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc(sizeof(char) * (k + 1));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * **strtoword2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 *
 * Return: a pointer to an array of strings
 */
char **strtoword2(char *str, char d)
{
	int i, j, k, m, numofwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) || (str[i] != d && !str[i + 1])
				|| (str[i + 1] == d))
			numofwords++;
	}
	if (numofwords == 0)
		return (NULL);
	s  = malloc(sizeof(char *) * (1 + numofwords));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numofwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
		k++;
		s[j] = malloc(sizeof(char) * (k + 1));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

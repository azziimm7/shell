#include "shell.h"
/**
 * *_memset - fills memory with a constant bytes
 * @str: pointer to the memory array to be filled
 * @c: the byte to fill *str with
 * @n: number of ytes to filled
 *
 * Return: A pointer to the memory area
 */

char *_memset(char *str, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		str[i] = c;
	}
	return (str);
}

/**
 * clean - frees a string of strings
 * @str: the string of strings
 */

void clean(char **str)
{
	char **temp = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(temp);
}
/**
 * _realloc - reallocate a block of memory
 * @ptr: a pointer to the previous block
 * @old_size: old size of the previous block
 * @new_size: old byte size of the block
 *
 * Return: pointer to the memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * pfree - frees the pointer and NULLs the space
 * @ptr: the address of the pointer to free
 *
 * Return: 1 on success, 0 otherwise
 */
int pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


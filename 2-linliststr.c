#include "shell.h"
/**
* length_list - determine the length of the list
* @h: pointer to the first node
*
* Return: size of the list
*/

size_t length_list(list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
* list_str - return an array of strings
* @head: pointer to the first node
*
* Return: array of strings
*/
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t i = length_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
	str = _strcopy(str, node->str);
	strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
* print_llist - prints all the elements of the linked list
* @head: pointer to the first node
*
* Return: size of the list
*/
size_t print_llist(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(_convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
* node_start_w - return nodes whos strings starts with a prefix
* @node: pointer to the list head
* @pre: string to match
* @ch: the next char after prefix to match
*
* Return: match node or null
*/
list_t *node_start_w(list_t *node, char *pre, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_with(node->str, pre);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
* get_index - get the index of the node
* @head: pointer to the head node
* @node: pointer to the node
*
* Return: index of node or -1
*/

ssize_t get_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

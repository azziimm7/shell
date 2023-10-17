#include "shell.h"
/**
* start_node - adds node to the start of the list
* @head: pointer to the head
* @str: string field of the node
* @number: node index
*
* Return: length of the list
*/

list_t *start_node(list_t **head, const char *str, int number)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = number;

	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}
/**
* end_node - adds a node to the end of the list
* @head: pointer to the head node
* @str: str field of the node
* @number: node index
*
* Return: length of the list
*/
list_t *end_node(list_t **head, const char *str, int number)
{
	list_t *new, *node;

	if (!head)
		return (NULL);

	node = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = number;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}
/**
* print_list_string - print the string field of thelinked list
* @first: pointer to the first node
*
* Return: size of the list
*/
size_t print_list_string(const list_t *first)
{
	size_t i = 0;

	while (first)
	{
		_puts(first->str ? first->str : "(nil)");
		_puts("\n");
		first = first->next;
		i++;
	}
	return (i);
}

/**
* del_node_at - deletes node at a given index
* @head: pointer to first node
* @index: index of the node to delete
*
* Return: 1 on success, 0 otherwise
*/

int del_node_at(list_t **head, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		p_node = node;
		node = node->next;
	}
	return (0);
}
/**
* freelist - delete all the nodof the list
* @head: pointer to the first node
*
* Return: void
*/

void freelist(list_t **head)
{
	list_t *node, *next_node, *h;

	if (!head || !*head)
		return;
	h = *head;
	node = h;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head = NULL;
}

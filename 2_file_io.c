#include "shell.h"
/**
 * renumber_history - renumber the history linked list
 * @information: struct
 *
 * Return: the new histcount
 */
int renumber_history(information_t *information)
{
	list_t *node = information->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (information->histcount = i);
}
/**
 * history_list - adds entry to the history linked list
 * @information: struct
 * @buf: buffer
 * @linecount: the history linecount
 *
 * Return: always 0
 */
int history_list(information_t *information, char *buf, int linecount)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	end_node(&node, buf, linecount);

	if (!information->history)
		information->history = node;
	return (0);
}

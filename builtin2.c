#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @information: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _history(information_t *information)
{
	print_llist(information->history);
	return (0);
}

/**
 * unset_alias - remove alias
 * @information: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(information_t *information, char *str)
{
	char *p, ch;
	int ret;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	ch = *p;
	*p = 0;
	ret = del_node_at(&(information->alias),
		get_index(information->alias, node_start_w(information->alias, str, -1)));
	*p = ch;
	return (ret);
}

/**
 * _setalias - sets alias to string
 * @information: struct
 * @str: string
 *
 * Return: 0 on success, 1 on error
 */
int _setalias(information_t *information, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	return (1);
	if (!*++p)
	return (unset_alias(information, str));

	unset_alias(information, str);
	return (end_node(&(information->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
	for (a = node->str; a <= p; a++)
		_putchar(*a);
	_putchar('\'');
	_puts(p + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @information: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_alias(information_t *information)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (information->argc == 1)
	{
		node = information->alias;
		while (node)
		{
		print_alias(node);
		node = node->next;
		}
		return (0);
	}
	for (i = 1; information->argv[i]; i++)
	{
		p = _strchr(information->argv[i], '=');
		if (p)
			_setalias(information, information->argv[i]);
		else
			print_alias(node_start_w(information->alias, information->argv[i], '='));
		}
		return (0);
}

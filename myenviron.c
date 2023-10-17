#include "shell.h"
/**
 * _env - prints the cureent environment
 * @information: structure
 *
 * Return: always 0
 */
int _env(information_t *information)
{
	print_list_string(information->env);
	return (0);
}
/**
 * _getenv - gets the value of an environ variable
 * @information: structure
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(information_t *information, const char *name)
{
	list_t *node = information->env;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _set_new_env - intialize new environmet variable
 *
 * @information: structure
 *
 * Return: always 0
 */
int _set_new_env(information_t *information)
{
	if (information->argc != 3)
	{
		_eput("Incorrect number o arguments\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}
/**
 * _rmenv - remove an environment variable
 * @information: struct
 *
 * Return: always 0
 */
int _rmenv(information_t *information)
{
	int i;

	if (information->argc == 1)
	{
		_eput("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= information->argc; i++)
		rm_env_var(information, information->argv[i]);
	return (0);
}
/**
 * pop_env_list - populates environment linked list
 * @information: structure
 *
 * Return: always 0
 */
int pop_env_list(information_t *information)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		end_node(&node, environ[i], 0);
	information->env = node;
	return (0);
}

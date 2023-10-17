#include "shell.h"
/**
 * get_environ - returns dtring array copy of our environmet
 * @information: struct
 *
 * Return: always 0
 */
char **get_environ(information_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_str(information->env);
		information->env_changed = 0;
	}
	return (information->environ);
}
/**
 * rm_env_var - remove environ variable
 * @information: struct
 * @var: the string env var
 *
 * Return: 1 on delete 0 otherwise
 */
int rm_env_var(information_t *information, char *var)
{
	list_t *node = information->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			information->env_changed = del_node_at(&(information->env), i);
			i = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (information->env_changed);
}
/**
 * _setenv - intialize new environ var
 * @information: struct
 * @var: variable to be intialized
 * @value: string env var value
 *
 * Return: always 0
 */
int _setenv(information_t *information, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcopy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = information->env;
	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			information->env_changed = 1;
			return (0);
		}
		node = node->next;

	}
	end_node(&(information->env), buf, 0);
	free(buf);
	information->env_changed = 1;
	return (0);
}

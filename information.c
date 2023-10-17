#include "shell.h"
/**
 * null_info - intialize information_t struct
 * @information: struct address
 */
void null_info(information_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}
/**
 * set_info - intialize information_t struct
 * @information: struct address
 * @arg_vec: argument vector
 */
void set_info(information_t *information, char **arg_vec)
{
	int i = 0;

	information->fname = arg_vec[0];
	if (information->arg)
	{
		information->argv = strtoword(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}

		for (i = 0; information->argv && information->argv[i]; i++)
			;
		information->argc = 1;

		replace_alias(information);
		replace_vars(information);
	}
}
/**
 * clean_info - frees information_t struct fields
 * @information: struct address
 * @all: true on success
 */
void clean_info(information_t *information, int all)
{
	clean(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (all)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			freelist(&(information->env));
		if (information->history)
			freelist(&(information->history));
		if (information->alias)
			freelist(&(information->alias));
		clean(information->environ);
			information->environ = NULL;
		pfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}

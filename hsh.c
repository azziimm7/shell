#include "shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return info struct
 * @av: the argument vector from main ()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(information_t *information, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		null_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchars(BUF_FLUSH);
		r = get_input(information);
		if (r != -1)
		{
			set_info(information, av);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_cmd(information);
		}
		else if (interactive (information))
			_putchar('\n');
		clean_info(information, 0);
	}
	history_write(information);
	clean_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_ret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_ret);
}



/**
 * find_builtin - finds a builtin command
 * @information: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
            0 if builtin executed successfully, 1 if builtin found but not successful,
           -2 if builtin signals exit ()
*/
int find_builtin(information_t *information)
{
	int i, built_in_ret = -1;
	builtin_t builtintbl[] = {
		{"exist", _shellexit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _set_new_env},
		{"unsetenv", _rmenv},
		{"cd", _dirchange},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcomp(information->argv[0], builtintbl[i].type) == 0)
		{
			information->line_count++;
			built_in_ret = builtintbl[i].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @information: the parameter & return info struct
 * Return: void
 */
void find_cmd(information_t *information)
{
	int i, k;
	char *path = NULL;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}

	for (i = 0, k = 0; information->arg[i]; i++)
		if (!is_delim(information->arg[i],"\t\n"))
		k++;

	if (!k)
	{
		return;
	}
	
		path = find_path(information, _getenv(information, "PATH="), information->argv[0]);
	if (path)
	{
		information->path = path;
		information->path = path;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
			|| information->argv[0][0] == '/') && is_cmd(information, information->argv [0]))
				fork_cmd(information);
		else if (* (information->arg) != '\n')
		{
			information->status = 127;
			print_err(information, "not found\n");
		}
	}
}








/**
 * fork_cmd - forks a an exec thread to run cmd
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(information_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv, get_environ(information)) == -1)
		{
			clean_info(information, 1);
			if (errno == EACCES)
				exit (126);
			exit (1);
		}
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_err(information, "Permission denied/n");
		}
	}
}

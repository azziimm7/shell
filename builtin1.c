#include "shell.h"

/**
 * _shellexit - exit the shell
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function porotype.
 * Return: exits with a given exist status
 *	(0) if ing.agrv[0] !="exist"
 */
int _shellexit(information_t *information)
{
	int exitchecker;

	if (information->argv[1])
	{
		exitchecker = _erroratoi(information->argv[1]);
		if (exitchecker == -1)
		{
			information->status = 2;
			print_err(information, "this is an illegal number: ");
			_eput(information->argv[1]);
			_eputchars('\n');
			return (1);
		}
		information->err_num = _erroratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _dirchange - change the current directory
 * @information: Structure containing potential arguments. Used to maintain
 *	constant function porotype.
 * Return: Always 0
 */
int _dirchange(information_t *information)
{
	char *s, *dir, buffer[1024];
	int chdir_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >> getcwd error msg here<<\n");
	if (!information->argv[1])
	{
		dir = _getenv(information, "HOME=");
		if (!dir)
			chdir_rt = chdir((dir = _getenv(information, "PWD=")) ? dir : "/");
		else
			chdir_rt = chdir(dir);
	}
	else if (_strcomp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		chdir_rt = chdir((dir = _getenv(information, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rt = chdir(information->argv[1]);
	if (chdir_rt == -1)
	{
		print_err(information, "can't cd to ");
		_eput(information->argv[1]), _eputchars('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "pwd="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _help - change the current directory
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function porotype.
 * Return: Always 0
 */
int _help(information_t *information)
{
	char **arg_array;

	arg_array = information->argv;
	_puts("help call works. Function not yet implemnted /n");
	if (0)
		_puts(*arg_array);
	return (0);
}

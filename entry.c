#include "shell.h"
/**
 * main - main or entry point
 * @arg_count: arg count
 * @arg_vec: arg vector
 *
 * Return: 0 on success 1 on error
 */
int main(int arg_count, char **arg_vec)
{
	information_t information[] = { INFO_INIT};
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	if (arg_count == 2)
	{
		fd = open(arg_vec[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eput(arg_vec[0]);
				_eput(": 0 : Can't open");
				_eput(arg_vec[1]);
				_eputchars('\n');
				_eputchars(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = fd;
	}
	pop_env_list(information);
	history_read(information);
	return (EXIT_SUCCESS);
}



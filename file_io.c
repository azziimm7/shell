#include "shell.h"
/**
 * _get_history - gets the history file
 * @information: struct
 *
 * Return: string containig history file
 */
char *_get_history(information_t *information)
{
	char *buf, *directory;

	directory = _getenv(information, "HOME");

	if (!directory)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcopy(buf, directory);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * history_write - create file
 * @information: struct
 *
 * Return: 1 on success, -1 otherwise
 */
int history_write(information_t *information)
{
	ssize_t fd;
	char *file_name = _get_history(information);
	list_t *node = NULL;

	if (!file_name)
		return (-1);
	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);

	for (node = information->history; node; node = node->next)
	{
		_putsfds(node->str, fd);
		_putfds('\n', fd);
	}
	_putfds(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * history_read - reads file history
 * @information: struct
 *
 * Return: history_count on success, 0 otherwise
 */
int history_read(information_t *information)
{
	int i, final = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _get_history(information);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list(information, buf + final, linecount++);
			final = i + 1;
		}
	if (final != i)
		history_list(information, buf + final, linecount++);
	free(buf);
	information->histcount = linecount;
	while (information->histcount-- >= HIST_MAX)
		del_node_at(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

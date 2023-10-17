#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @information: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(information_t *information, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
	r = getline(buf, &len _P, stdin);
#else
	r = _getline(information, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}

			information->linecount_flag = 1;
			rem_coms(*buf);
			history_list(information, *buf, information->histcount++);
			{
				*len = r;
				information->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * read_buf - reads a buffe
 * @information: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(information_t *information, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(information->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_input - gets a line minus the rewline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(information_t *information)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(information->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(information, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(information, buf, &j, i, len);
	while (j < len)
	{
		if (is_chain(information, buf, &j))
			break;
	j++;
	}

	i = j + 1;
	if (i >= len)
	{
		i = len = 0;
		information->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p;
	return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @information: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(information_t *information, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(information, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + 1, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	puts("\n");
	puts("$ ");
	putchar(BUF_FLUSH);
}

#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>


/* for  read/write buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024

#define BUF_FLUSH -1

/* for commad chainig */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for _convert_num()  */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using systum getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct lliststrs - singly lilnked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct info - contians pseudo args to pass into a function
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path
 * @argc: the arguments count
 * @line_count: the error count
 * @err_num: the error code
 * @linecount_flag: if on count this line of input
 * @fname: the program file name
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ is changed
 * @status: the return status
 * @cmd_buf: address of the pointer to cmd_buf
 * @cmd_buf_type: CMD_TYPE ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} information_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtins - byiltin string and related function
 * @type: builtin command flag
 * @func: the function
 */
typedef struct builtins
{
	char *type;
	int (*func)(information_t *);
} builtin_t;

/* strings funstions */
int _strlen(const char *str);
char *_strdup(const char *str);
char *_strcopy(char *dest, const char *src);
int _strcomp(const char *str1, const char *str2);
char *_strchr(char *str, char c);

/* 2-strings finctions */
char *start_with(const char *heystack, const char *needle);
char *_strcat(char *dest, char *src);
void _puts(char *src);
int _putchar(char c);

/* 3-strings funstions */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *str1, char *str2, int n);
char **strtoword(char *str, char *d);
char **strtoword2(char *str, char d);

/* memory helpers functions */
char *_memset(char *str, char c, unsigned int n);
void clean(char **str);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int pfree(void **ptr);

/* additional functions */
int interactive(information_t *information);
int is_delim(char c, char *delimiter);
int _is_alpha(int ch);
int _isdigit(int c);
int is_atoi(char *str);

/* more functions */
int _erroratoi(char *str);
void print_err(information_t *information, char *errstr);
int print_dec(int in, int fd);
char *_convert_num(long int number, int b, int flags);
void rem_coms(char *buff);

/*  linked list functions1 */
list_t *start_node(list_t **head, const char *str, int number);
list_t *end_node(list_t **head, const char *str, int number);
size_t print_list_string(const list_t *first);
int del_node_at(list_t **head, unsigned int index);
void freelist(list_t **head);

/* linked lists functions2 */
size_t length_list(list_t *h);
char **list_str(list_t *head);
size_t print_llist(const list_t *head);
list_t *node_start_w(list_t *node, char *pre, char ch);
ssize_t get_index(list_t *head, list_t *node);

/* error strings functoins */
void _eput(char *str);
int _eputchars(char ch);
int _putfds(char ch, int fds);
int _putsfds(char *str, int fds);

/* ENTRY POINT FUNCTION */
int main(int arg_count, char **arg_vec);

/* INFORMATION STRUCUTRE */
void null_info(information_t *information);
void set_info(information_t *information, char **arg_vec);
void clean_info(information_t *information, int all);

/* ENVIRONMENT FUNCTIONS */
char *_getenv(information_t *information, const char *name);
int _env(information_t *information);
int _set_new_env(information_t *information);
int _rmenv(information_t *information);
int pop_env_list(information_t *information);

/* ENVIRONMENT FUNCTIONS 2 */
char **get_environ(information_t *information);
int rm_env_var(information_t *information, char *var);
int _setenv(information_t *information, char *var, char *value);


/* file input/output functions */
char *_get_history(information_t *information);
int history_write(information_t *information);
int history_read(information_t *information);


/* file input/output functions2  */
int renumber_history(information_t *information);
int history_list(information_t *information, char *buf, int linecount);


/* hsh functions  */
int hsh(information_t *information, char **av);
int find_builtin(information_t *information);
void find_cmd(information_t *information);
void fork_cmd(information_t *information);


/* builtin functions1 */
int _shellexit(information_t *information);
int _dirchange(information_t *information);
int _help(information_t *information);

/* builtin functions2 */
int _history(information_t *information);
int unset_alias(information_t *information, char *str);
int _setalias(information_t *information, char *str);
int print_alias(list_t *node);
int my_alias(information_t *information);

/* chain functions */
int is_chain(information_t *information, char *buf, size_t *p);
void check_chain(information_t *information, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(information_t *information);
int replace_vars (information_t *information);
int replace_string(char **old, char *new);

/* getline function */

ssize_t input_buf(information_t *information, char **buf, size_t *len);
ssize_t read_buf(information_t *information, char *buf, size_t *i);
ssize_t get_input(information_t *information);
int _getline(information_t *information, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);


/* PATH FUNCTIONS */
int is_cmd(information_t *information, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(information_t *information, char *pathstr, char *cmd);


#endif

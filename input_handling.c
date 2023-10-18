#include "shell.h"

/**
 * capture_input - buffers chained commands
 * @info: pointer to the struct containing shell info
 *
 * Return: bytes read
 */
ssize_t capture_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, len;
	ssize_t r;

	r = custom_getline(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);

	if (len) /* if commands left in chain buffer */
	{
		char *p = buf + i;

		i += _strlen(p) + 1; /* move index past current command */

		if (i >= len) /* if reached end of buffer */
		{
			i = len = 0; /* reset index and length */
			info->cmd_buf_type = CMD_NORM;
		}

		info->arg = p; /* set the current command position */
		return (_strlen(p)); /* return length of current command */
	}

	info->arg = buf; /* not a chain, set from custom_getline */
	return (r); /* return length from custom_getline */
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: pointer to the struct containing shell info
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: length of the read line
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[R_BUF_SIZE];
	static size_t idx, buf_len;
	size_t k;
	ssize_t r, line_len = 0;
	char *new_ptr = NULL, *newline_pos;

	if (idx == buf_len)
		idx = buf_len = 0;

	r = read(info->read_fd, buf, R_BUF_SIZE);
	if (r <= 0)
		return (-1);

	newline_pos = char_search(buf + idx, '\n');
	k = newline_pos ? 1 + (unsigned int)(newline_pos - buf) : buf_len;

	new_ptr = realloc(*ptr, *length ? *length + k : k + 1);
	if (!new_ptr)
		return (-1); /* Allocation failure */

	if (*length)
		string_ncat(new_ptr, buf + idx, k - idx);
	else
		string_ncopy(new_ptr, buf + idx, k - idx + 1);

	line_len += k - idx;
	idx = k;
	*ptr = new_ptr;
	if (length)
		*length = line_len;

	return (line_len);
}

/**
 * signal_int_handler - handles the interrupt signal (Ctrl-C)
 * @sig_num: the signal number
 *
 * Return: void
 */
void signal_int_handler(__attribute__((unused))int sig_num)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}

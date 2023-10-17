#ifndef _HSH_SHELL_H_
#define _HSH_SHELL_H_

/* Include directives */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants */
#define R_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define BUF_FLSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GL 0
#define USE_STK 0
#define HSH_HIST_FILE ".hsh_history"
#define HIST_MAX_LEN 4096

extern char **environ;

/* Data structures */
typedef struct list_string
{
	int num;
	char *str;
	struct list_string *next;
} list_str_t;

typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_cnt;
	int err_num;
	int linecnt_flag;
	char *fname;
	list_str_t *env;
	list_str_t *history;
	list_str_t *alias;
	char **envrn;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int read_fd;
	int hist_cnt;
} info_t;

#define INFO_DEFAULT
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL,
	0, 0, NULL, 0, 0, 0}

typedef struct builtin_cmd
{
	char *type;
	int (*func)(info_t *);
} builtin_tbl_t;

/* hsh_loop.c */
int hsh_loop(info_t *, char **);
int locate_builtin(info_t *);
void locate_cmd(info_t *);
void spawn_cmd(info_t *);

/* hsh_loop.c */
int hsh_loop(info_t *, char **);
int locate_builtin(info_t *);
void locate_cmd(info_t *);
void spawn_cmd(info_t *);

/* parser.c */
int cmd_exists(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *detect_path(info_t *, char *, char *);

/* main_loop.c */
int main_hsh_loop(char **);

/* error_handling.c */
void error_puts(char *);
int error_putchar(char);
int putchar_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string_utils.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* string_utils1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void string_puts(char *);
int string_putchar(char);

/* exit_utils.c */
char *string_ncopy(char *, char *, int);
char *string_ncat(char *, char *, int);
char *char_search(char *, char);

/* tokenizer.c */
char **string_to_words(char *, char *);
char **string_to_array(char *, char);

/* realloc_utils.c */
char *set_memory(char *, char, unsigned int);
void free_double_pointer(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* memory_utils.c */
int buffer_free(void **);

/* atoi_utils.c */
int check_interactive(info_t *);
int delimiter_check(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* error_handling1.c */
int error_atoi(char *);
void display_error(info_t *, char *);
int print_digit(int, int);
char *number_conversion(long int, int, int);
void strip_comments(char *);

/* builtin_cmds.c */
int cmd_exit(info_t *);
int cmd_cd(info_t *);
int cmd_help(info_t *);

/* builtin_cmds1.c */
int cmd_history(info_t *);
int cmd_alias(info_t *);

/* input_handling.c */
ssize_t capture_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void signal_int_handler(int);

/* info_mgmt.c */
void reset_info(info_t *);
void initialize_info(info_t *, char **);
void release_info(info_t *, int);

/* environ_mgmt.c */
char *retrieve_env(info_t *, const char *);
int cmd_env(info_t *);
int cmd_setenv(info_t *);
int cmd_unsetenv(info_t *);
int set_env_list(info_t *);

/* getenv_utils.c */
char **fetch_environ(info_t *);
int remove_env(info_t *, char *);
int add_env(info_t *, char *, char *);

/* history_mgmt.c */
char *locate_history_file(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int compile_history_list(info_t *info, char *buf, int linecount);
int reorder_history(info_t *info);

/* list_mgmt.c */
list_str_t *create_node(list_str_t **, const char *, int);
list_str_t *append_node(list_str_t **, const char *, int);
size_t display_list_string(const list_str_t *);
int remove_node_by_index(list_str_t **, unsigned int);
void dispose_list(list_str_t **);

/* list_mgmt1.c */
size_t count_nodes(const list_str_t *);
char **convert_list_to_strings(list_str_t *);
size_t print_list_items(const list_str_t *);
list_str_t *locate_node_start(list_str_t *, char *, char);
ssize_t determine_node_index(list_str_t *, list_str_t *);

/* vars_mgmt.c */
int detect_chain(info_t *, char *, size_t *);
void inspect_chain(info_t *, char *, size_t *, size_t, size_t);
int swap_alias(info_t *);
int swap_vars(info_t *);
int swap_substring(char **, char *);

#endif

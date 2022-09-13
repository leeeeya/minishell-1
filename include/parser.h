#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>

#define UNEXP 258
#define NO_F 1
#define COM_NF 127
#define ERROR (-1)
#define PERM_DEN 126
# define FALSE 0
# define TRUE 1

//typedef struct s_input
//{
//	char        **args;
//	int builtin;
//	t_list *infile_name;
//	t_list *outfile_name;
//	int in_file;
//	int         out_file;
//	int type_of_file;
//	t_list *hd_delimeter;
//	struct s_input    *next;
//	struct s_input *prev;
//}	t_input;


//typedef struct s_parse
//{
//	char *cmd_line;
//	int *exit_code;
//	char *head_cmd_line;
//	t_input *ready_data;
//	char **env;
//	char **paths;
//}   t_parse;

//int get_args(t_parse *d);
////void syntax_error(t_parse *d, char *token);
//char *append(t_parse *d, char *str, char ch);
//int pars_doub_quote(char **line_to_write, t_parse *d);
//int pars_quote(char **line_to_write, t_parse *d);
//void pars_env(char **line_to_write, t_parse *d);
//
//t_input	*input_new();
//int	input_size(t_input *lst);
//void	input_clear(t_input **lst);
//void	input_add_back(t_input **lst, t_input **new);
//t_input *input_last(t_input *lst);
//void	input_delone(t_input *lst);
//
//void get_env(t_parse *d, char **env);
//int itter(t_parse *d, char **line_to_write, char type);
//int get_valid_fn(t_parse *d, t_list **fns);
//int handle_spaces(t_parse *d, char type);
//int handle_ifn(t_parse *d);
//int get_true_path(t_parse *d);
//void search_path(t_parse *d);
//void check_error(void *data, t_parse *d, char *error);
//void free_all( t_parse *d);
//void print_error(t_parse *d, char *arg, char *error);
//int parser(char *cmd_line, int *exit_code, char **env);
#endif //PARSER_H
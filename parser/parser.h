#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>

#define UNEXP 258
#define NO_F 1
#define COM_NF 127
#define ERROR (-1)
#define PERM_DEN 126

typedef struct s_input
{
	char			**args;
	int				builtin;
	t_list			*infile_name;
	t_list			*outfile_name;
	int				in_file;
	int				out_file;
	int				type_of_file;
	t_list			*hd_delimeter;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;


typedef struct s_data
{
	char			*cmd_line;
	int				*exit_code;
	char			*head_cmd_line;
	t_input			*ready_data;
	char			**env;
	char			**paths;
}	t_data;

//main.c
int		parser(char *cmd_line, int *exit_code, char **env);
int		check_accesses_outf(t_data *d);
int		check_accesses_inf(t_data *d);
int		get_outfile_name(t_data *d);
int		get_infile_name(t_data *d);
int		get_delimeter(t_data *d);
void	get_heredoc_fd(t_data *d);

//env.c
void	get_env(t_data *d, char **env);
char	*get_value_env(t_data *d, char *key);
void	pars_env(char **line_to_write, t_data *d);

//errors.c
void	free_all( t_data *d);
void	check_error(void *data, t_data *d, char *error);
void	print_error(t_data *d, char *arg, char *error);

//get_args.c
int		next_arg(t_data *d, t_list **arg_lst);
void	fetch_arg_array(t_data *d, t_list **arg_lst);
int		get_args(t_data *d);

//input_delete.c
void	input_delone(t_input *lst);
void	input_clear(t_input **lst);

//input_utils.c
t_input	*input_new();
t_input	*input_last(t_input *lst);
int		input_size(t_input *lst);
void	input_add_front(t_input **lst, t_input *new);
void	input_add_back(t_input **lst, t_input **new);

//quotes.c
int		pars_quote(char **line_to_write, t_data *d);
void	shielding(t_data *d, char **line_to_write);
int		pars_doub_quote(char **line_to_write, t_data *d);

//search_path.c
void	join_slash(t_data *d);
int		check_builtin(char *cmd, t_data *d);
void	search_path(t_data *d);
int		get_true_path(t_data *d);

//utils.c
char	*append(t_data *d, char *str, char ch);
int		itter(t_data *d, char **line_to_write, char type);
int		get_valid_fn(t_data *d, t_list **fns);
int		handle_spaces(t_data *d, char type);
int		handle_ifn(t_data *d);

// void syntax_error(t_data *d, char *token);

#endif //PARSER_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:39:09 by falarm            #+#    #+#             */
/*   Updated: 2022/09/12 18:28:10 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
// # include <wait.h>

# define TRUE 1
# define FALSE 0

# define PROMT_NORM "(ง •̀_•́)ง "
# define PROMT_BAD  "(๑•̀ᗝ•́)૭ "
# define RED   "\001\x1b[31m\002"
# define BLU   "\001\x1B[34m\002"
# define GRN   "\001\x1B[32m\002"
# define CLOSE "\001\033[0m\002" // Закрыть все свойства
# define BLOD  "\001\033[1m\002" // Подчеркнуть, жирным шрифтом, выделить
// # define BEGIN(x,y) "\001\033["#x";"#y"m\002" x: background, y: foreground

typedef struct s_hist
{
	int				index;
	char			*cmd_line;
	struct s_hist	*prev;
	struct s_hist	*next;
}	t_hist;

typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;

typedef struct s_input
{
	char			**args;
	char			*infile_name;
	char			*outfile_name;
	int				infile;
	int				outfile;
	int				type_of_file;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

typedef struct s_buildin
{
	char			*name;
	int				(*func)(t_input *, t_list **);
}	t_buildin;

typedef struct s_data
{
	int				exit_flag;
	int				exit_status;
	int				*pipes;
	t_list			*envp_list;
	t_buildin		buildins[7];
}	t_data;

//build-ins
int		ft_cd(t_input *inp, t_list **envp);
int		ft_echo(t_input *inp, t_list **envp);
int		ft_env(t_input *inp, t_list **envp);
int		ft_exit(t_input *inp, t_list **envp);
int		ft_export(t_input *inp, t_list **envp);
int		ft_pwd(t_input *inp, t_list **envp);
int		ft_unset(t_input *inp, t_list **envp);

//main.c
char	*print_promt(int status);

//ft_utils.c
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstswap(t_list *first, t_list *second, t_list *tmp);
int		double_arr_size(char **arr);
char	**split_by_first(char *s, char c);

//init.c
t_envp	*init_envp(char	*key, char *value);
t_data	*init_data(char	**env);
int		init_pipes(t_data *data, int count);

//ft_free.c
void	free_data(t_data *data);
void	free_double_arr(char **arr);
void	free_inp(t_input *inp);
void	del_envp(void *envp_list);
void	close_pipes(t_data *data, int pipe_count);

//env_utils.c
void	add_env_value(t_list *envp_list, t_envp *envp);
char	*get_envp_value(t_list *envp, char *buf);
void	change_env_value(t_envp *curr, t_envp *envp);
char	**get_envp(t_list *envp_list);

//handlers.c
void	sigint_handler(int n);
void	sigquit_handler(int n);
void	eof_handler(t_data *data);

//ft_list.c
int		lst_size(t_input *inp);

//executer.c
void	my_exec(t_data *data, t_input *inp);

//errors.c
void	error_malloc(t_data *data);
void	my_perror(t_data *data);
void	error_exit(void);
int		error_str(char *s, int code);

#endif

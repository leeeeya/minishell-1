/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:39:09 by falarm            #+#    #+#             */
/*   Updated: 2022/08/15 22:18:52 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../../libft/libft.h"
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

# define TRUE 1
# define FALSE 0

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
	int				type_of_file;	//how open file
	char			*hd_delimiter;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

typedef	struct s_buildin
{
	char			*name;
	int				(*func)(t_input *, t_list *);
}	t_buildin;

typedef struct s_data
{
	int				exit_flag;	//while false programm is working
	int				exit_status;
	t_list			*envp_list;
	t_buildin		buildins[7];
}	t_data;

//build-ins
int		ft_cd(t_input *inp, t_list *envp);
int		ft_echo(t_input *inp, t_list *envp);
int		ft_env(t_input *inp, t_list *envp);
int		ft_exit(t_input *inp, t_list *envp);
int		ft_export(t_input *inp, t_list *envp);
int		ft_pwd(t_input *inp, t_list *envp);
int		ft_unset(t_input *inp, t_list *envp);

//ft_utils.c
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstswap(t_list *first, t_list *second, t_list *tmp);

//init.c
t_data	*init_data(char	**env);

//ft_free.c
void	free_data(t_data *data);
void	free_double_arr(char **envp);

//env_utils.c
t_envp	*init_envp(char **key_value);
void	add_env_value(t_list *envp_list, t_envp *envp);
char	**get_envp(t_list *envp_list);

#endif

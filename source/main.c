/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:38:50 by falarm            #+#    #+#             */
/*   Updated: 2022/09/08 19:07:37 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_args(char *s)
{
	char	**args;

	args = ft_split(s, ' ');
	return (args);
}

t_input	*init_inp(char *s)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	input->args = get_args(s);
	input->infile_name = NULL;
	input->outfile_name = NULL;
	input->infile = 0;
	input->outfile = 1;
	input->type_of_file = 0;
	input->next = NULL;
	input->prev = NULL;
	return (input);
}

char	*print_promt(int status)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (status)
		tmp = ft_strjoin(RED PROMT_BAD CLOSE BLU, cwd);
	else
		tmp = ft_strjoin(GRN PROMT_NORM CLOSE BLU, cwd);
	free(cwd);
	cwd = ft_strjoin(tmp, CLOSE "$ ");
	free(tmp);
	return (cwd);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*data;
	t_input	*inp;
	char	*s;
	char	*promt;

	(void) argc;
	(void) argv;
	signal(SIGINT, sigint_handler);
	data = init_ms(envp);
	if (!data)
	{
		ft_putendl_fd(RED "Error: " CLOSE "malloc returned NULL pointer!", 2);
		return (0);
	}
	while (!data->exit_flag)
	{
		signal(SIGQUIT, SIG_IGN);
		promt = print_promt(data->exit_status);
		s = readline(promt);
		// call parser
		inp = init_inp(s);
		// ft_putendl_fd(inp->args[0], 1);
		// ft_putendl_fd(inp->args[1], 1);
		add_history(s);
		free(s);
		free(promt);
		if (!inp->args)
		{
			eof_handler(data);
			// for test while don't have parser
			free_inp(inp);
		}
		else if (inp->type_of_file != -1)
			my_exec(data, inp);
		// bad input	need create flag
		free_inp(inp);
	}
	free_data(data);
	return (0);
}

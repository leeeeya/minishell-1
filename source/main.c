/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:38:50 by falarm            #+#    #+#             */
/*   Updated: 2022/08/31 00:51:01 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_args()
{
	char	**args;

	args = (char **) malloc(sizeof(char *) * 2);
	if (!args)
		return (NULL);
	args[0] = ft_strdup("/usr/bin/cat");
	// args[1] = ft_strdup("HUI");
	// args[2] = ft_strdup("SOS");
	args[1] = NULL;
	return (args);
}

t_input	*init_inp()
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	input->args = get_args();
	input->infile_name = NULL;
	input->outfile_name = NULL;
	input->infile = 0;
	input->outfile = 1;
	input->type_of_file = 0;
	input->next = NULL;
	input->prev = NULL;
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_input	*inp;

	(void) argc;
	(void) argv;
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigquit_handler);
	data = init_data(envp);
	if (!data)
	{
		ft_putendl_fd(RED "Error: " CLOSE "malloc returned NULL pointer!", 2);
		return (0);
	}
	while (!data->exit_flag)
	{
		ft_putendl_fd(BEGIN(49, 31) PROMT CLOSE "$", 1);
		inp = init_inp();	// call parser
		// add_history();
		if (!inp)
			eof_handler(data);
		else if (inp->type_of_file != -1)	// bad input	need create flag
			my_exec(data, inp);
		free_inp(inp);
		data->exit_flag = 1;
	}
	free_data(data);
	return (0);
}

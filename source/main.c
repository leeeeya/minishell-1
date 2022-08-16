/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:38:50 by falarm            #+#    #+#             */
/*   Updated: 2022/08/15 22:30:51 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_input	*init_inp()
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	input->args = NULL;
	input->infile_name = NULL;
	input->outfile_name = NULL;
	input->infile = 0;
	input->outfile = 0;
	input->type_of_file = 0;
	input->hd_delimiter = NULL;
	input->next = NULL;
	input->prev = NULL;
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_input	*inp;

	if (argc > 1 && argv)
		ft_putendl_fd("Error: Too many arguments!", 2);
	data = init_data(envp);
	inp = init_inp();
	ft_env(inp, data->envp_list);
	free_data(data);
	free(inp);
	return (0);
}

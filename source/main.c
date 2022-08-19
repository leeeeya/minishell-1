/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:38:50 by falarm            #+#    #+#             */
/*   Updated: 2022/08/19 01:16:45 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_args()
{
	char	**args;

	args = (char **) malloc(sizeof(char *) * 4);
	if (!args)
		return (NULL);
	args[0] = ft_strdup("unset");
	args[1] = ft_strdup("HUI");
	args[2] = ft_strdup("SOS");
	args[3] = NULL;
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

	// chdir("..");
	if (argc > 1 && argv)
		ft_putendl_fd("Error: Too many arguments!", 2);
	data = init_data(envp);
	inp = init_inp();
	ft_env(inp, data->envp_list);
	// ft_pwd(inp, data->envp_list);
	// ft_cd(inp, data->envp_list);
	// ft_pwd(inp, data->envp_list);
	// ft_export(inp, data->envp_list);
	ft_unset(inp, data->envp_list);
	ft_env(inp, data->envp_list);
	// int i = 0;
	// while (envp[i])
	// 	ft_putendl_fd(envp[i++], 1);
	// ft_echo(inp, data->envp_list);
	// ft_exit(inp, data->envp_list);
	free_data(data);
	free_inp(inp);
	return (0);
}

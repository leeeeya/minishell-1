/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:03:14 by falarm            #+#    #+#             */
/*   Updated: 2022/08/16 14:57:05 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*init_envp_list(char **envp)
{
	t_envp	*elem;
	t_list	*list;
	char	**key_value;

	list = NULL;
	while (*envp)
	{
		key_value = ft_split(*envp, '=');
		elem = init_envp(key_value);
		// free(key_value[2]);
		free(key_value);
		if (list)
			add_env_value(list, elem);
		else
			list = ft_lstnew(elem);
		envp++;
	}
	return (list);
}

t_data	*init_data(char	**env)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->exit_flag = FALSE;
	data->exit_status = 0;
	data->envp_list = init_envp_list(env);
	data->buildins[0].name = "cd";
	data->buildins[0].func = &ft_cd;
	data->buildins[1].name = "echo";
	data->buildins[1].func = &ft_echo;
	data->buildins[2].name = "env";
	data->buildins[2].func = &ft_env;
	data->buildins[3].name = "exit";
	data->buildins[3].func = &ft_exit;
	data->buildins[4].name = "export";
	data->buildins[4].func = &ft_export;
	data->buildins[5].name = "pwd";
	data->buildins[5].func = &ft_pwd;
	data->buildins[6].name = "unset";
	data->buildins[6].func = &ft_unset;
	return (data);
}

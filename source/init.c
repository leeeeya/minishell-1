/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:03:14 by falarm            #+#    #+#             */
/*   Updated: 2022/09/04 19:23:10 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envp	*init_envp(char	*key, char *value)
{
	t_envp	*envp;

	envp = (t_envp *) malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	envp->key = ft_strdup(key);
	if (value)
		envp->value = ft_strdup(value);
	else
		envp->value = NULL;
	return (envp);
}

t_list	*init_envp_list(char **envp)
{
	t_envp	*elem;
	t_list	*list;
	char	**key_value;

	list = NULL;
	while (*envp)
	{
		key_value = split_by_first(*envp, '=');
		elem = init_envp(key_value[0], key_value[1]);
		free_double_arr(key_value);
		if (list)
			add_env_value(list, elem);
		else
			list = ft_lstnew(elem);
		envp++;
	}
	return (list);
}

t_ms	*init_ms(char	**env)
{
	t_ms	*data;

	data = (t_ms *) malloc(sizeof(t_ms));
	if (!data)
		return (NULL);
	data->exit_flag = FALSE;
	data->exit_status = 0;
	data->pipes = NULL;
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

int	init_pipes(t_ms *data, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(data->pipes + 2 * i) < 0)
		{
			my_perror(data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

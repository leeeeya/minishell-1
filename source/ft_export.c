/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:21 by falarm            #+#    #+#             */
/*   Updated: 2022/08/19 00:41:44 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_copy(t_list *envp)
{
	t_list	*tmp;
	t_envp	*elem;

	tmp = envp;
	while (tmp)
	{
		elem = tmp->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd("=", 1);
		if (elem->value)
			ft_putstr_fd(elem->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	ft_export(t_input *inp, t_list *envp)
{
	t_envp	*elem;
	int		i;
	char	**key_value;

	if (double_arr_size(inp->args) == 1)
		env_copy(envp);
	else
	{
		i = 0;
		while (inp->args[++i])
		{
			key_value = split_by_first(inp->args[i], '=');
			elem = init_envp(key_value[0], key_value[1]);
			add_env_value(envp, elem);
			free(key_value);
		}
	}
	return (errno);
}

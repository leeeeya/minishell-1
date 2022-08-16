/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:40:21 by falarm            #+#    #+#             */
/*   Updated: 2022/08/09 01:13:38 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_double_arr(char **arr)
{
	char	*tmp;

	if (!arr)
		return ;
	while (*arr)
	{
		tmp = *arr++;
		free(tmp);
	}
}

void	del(void *envp_list)
{
	t_envp	*envp;

	envp = (t_envp *)envp_list;
	free(envp->key);
	free(envp->value);
	free(envp);
}

void	free_data(t_data *data)
{
	ft_lstclear(&data->envp_list, (*del));
	free(data);
}

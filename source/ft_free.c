/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:40:21 by falarm            #+#    #+#             */
/*   Updated: 2022/08/17 21:48:04 by falarm           ###   ########.fr       */
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

void	del_envp(void *envp_list)
{
	t_envp	*envp;

	envp = (t_envp *)envp_list;
	free(envp->key);
	free(envp->value);
	free(envp);
}

void	free_inp(t_input *inp)
{
	t_input	*tmp;

	while (inp)
	{
		tmp = inp->next;
		free_double_arr(inp->args);
		free(inp->hd_delimiter);
		free(inp->infile_name);
		free(inp->outfile_name);
		free(inp);
		inp = tmp;
	}
}

void	free_data(t_data *data)
{
	ft_lstclear(&data->envp_list, (*del_envp));
	free(data);
}

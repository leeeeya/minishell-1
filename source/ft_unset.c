/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:36 by falarm            #+#    #+#             */
/*   Updated: 2022/08/19 01:13:07 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	delete(t_list *curr, t_list *prev)
{
	t_list *tmp;

	del_envp(curr->content);
	if (prev)
	{
		prev->next = curr->next;
		free(curr);
	}
	else if (curr->next)
	{
		tmp = curr->next;
		curr->content = curr->next->content;
		curr->next = curr->next->next;
		free(tmp);
	}
}

static void	check(t_list *envp, char *key)
{
	t_list	*tmp;
	t_list	*prev;
	t_envp	*curr;

	prev = NULL;
	tmp = envp;
	while (tmp)
	{
		curr = tmp->content;
		if (!ft_strncmp(key, curr->key, ft_strlen(key)))
		{
			delete(tmp, prev);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_input *inp, t_list *envp)
{
	int	i;

	i = 0;
	while (inp->args[++i])
		check(envp, inp->args[i]);
	return (0);
}

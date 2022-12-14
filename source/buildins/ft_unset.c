/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:36 by falarm            #+#    #+#             */
/*   Updated: 2022/09/12 20:01:57 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid(char *s)
{
	if (s && ft_isdigit(s[0]))
		return (FALSE);
	while (*s)
	{
		if (!ft_isalpha(*s) && !ft_isdigit(*s) && *s != '_')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static void	delete(t_list *curr, t_list *prev)
{
	t_list	*tmp;

	if (prev)
	{
		prev->next = curr->next;
		ft_lstdelone(curr, (*del_envp));
	}
	else if (curr->next)
	{
		del_envp(curr->content);
		tmp = curr->next;
		curr->content = curr->next->content;
		curr->next = curr->next->next;
		free(tmp);
	}
}

static void	check(t_list **envp, char *key)
{
	t_list	*tmp;
	t_list	*prev;
	t_envp	*curr;

	prev = NULL;
	tmp = *envp;
	while (tmp)
	{
		curr = tmp->content;
		if (!ft_strncmp(key, curr->key, ft_strlen(key)))
		{
			if (!tmp->next)
				ft_lstclear(envp, (*del_envp));
			else
				delete(tmp, prev);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_input *inp, t_list **envp)
{
	int	i;
	int	res;

	i = 0;
	res = EXIT_SUCCESS;
	while (inp->args[++i])
	{
		if (is_valid(inp->args[i]))
			check(envp, inp->args[i]);
		else
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(inp->args[i], 2);
			res = error_str("': not a valid identifier", 1);
		}
	}
	return (res);
}

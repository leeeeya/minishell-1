/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:39:11 by falarm            #+#    #+#             */
/*   Updated: 2022/08/17 21:01:25 by falarm           ###   ########.fr       */
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

void	change_env_value(t_envp *curr, t_envp *envp)
{
	if (curr->value && !envp->value)
		free(envp->value);
	else
	{
		free(curr->value);
		curr->value = envp->value;
	}
	free(envp->key);
	free(envp);
}

void	add_env_value(t_list *envp_list, t_envp *envp)
{
	t_envp	*curr;
	t_list	*tmp;
	int		cmp;

	while (envp_list)
	{
		curr = (t_envp *) envp_list->content;
		cmp = ft_strcmp(envp->key, curr->key);
		if (cmp <= 0 || !envp_list->next)
		{
			if (cmp == 0)
				change_env_value(curr, envp);
			else if (cmp < 0)
			{
				tmp = envp_list->next;
				envp_list->next = ft_lstnew(envp);
				ft_lstswap(envp_list, envp_list->next, tmp);
			}
			else
				envp_list->next = ft_lstnew(envp);
			break ;
		}
		envp_list = envp_list->next;
	}
}

char	*get_envp_value(t_list *envp, char *buf)
{
	t_envp	*elem;
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		elem = tmp->content;
		if (!ft_strncmp(buf, elem->key, ft_strlen(buf)))
			return (elem->value);
		tmp = tmp->next;
	}
	return (NULL);
}

// char	*envp_str(t_envp *envp)
// {
// 	char	*res;
// 	char	*tmp;

// 	if (envp->value)
// 	{
// 		tmp = ft_strjoin(envp->key, "=");
// 		res = ft_strjoin(tmp, envp->value);
// 		free(tmp);
// 	}
// 	else
// 		res = ft_strdup(envp->key);
// 	return (res);
// }

// char	**get_envp(t_list *envp_list)
// {
// 	char	**envp;
// 	t_list	*tmp;
// 	int		i;

// 	envp = (char **) malloc(sizeof(char *) * (ft_lstsize(envp_list) + 1));
// 	if (!envp)
// 		return (NULL);
// 	tmp = envp_list;
// 	i = 0;
// 	while (tmp)
// 	{
// 		envp[i++] = envp_str(tmp->content);
// 		tmp = tmp->next;
// 	}
// 	envp[i] = NULL;
// 	return (envp);
// }

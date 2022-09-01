/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:39:02 by falarm            #+#    #+#             */
/*   Updated: 2022/08/17 14:15:36 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_input *inp, t_list *envp)
{
	t_list	*tmp;
	t_envp	*elem;

	(void) inp;
	tmp = envp;
	while (tmp)
	{
		elem = tmp->content;
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd("=", 1);
		if (elem->value)
			ft_putstr_fd(elem->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	return (errno);
}

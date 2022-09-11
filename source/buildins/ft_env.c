/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:39:02 by falarm            #+#    #+#             */
/*   Updated: 2022/09/11 20:49:15 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_input *inp, t_list *envp)
{
	t_list	*tmp;
	t_envp	*elem;

	(void) inp;
	tmp = envp;
	while (tmp)
	{
		printf("envp memory: %p\n", tmp);
		elem = tmp->content;
		printf("envp->content memory: %p\n", elem);
		printf("content->key memory: %p\n", elem->key);
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd("=", 1);
		if (elem->value)
			ft_putstr_fd(elem->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:04:17 by falarm            #+#    #+#             */
/*   Updated: 2022/08/30 01:29:41 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lst_size(t_input *inp)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = inp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

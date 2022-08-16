/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:10:08 by falarm            #+#    #+#             */
/*   Updated: 2022/08/16 14:43:18 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstswap(t_list *first, t_list *second, t_list *tmp)
{
	void	*tmp_content;

	if (tmp)
		first->next->next = tmp;
	tmp_content = first->content;
	first->content = second->content;
	second->content = tmp_content;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (*s1 - *s2);
		*s1++;
		*s2++;
	}
	return (*s1 - *s2);
}

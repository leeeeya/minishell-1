/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:38:51 by cstefany          #+#    #+#             */
/*   Updated: 2022/09/13 20:04:16 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	input_delone(t_input *lst)
{
	if (lst == NULL)
		return ;
	if (lst->hd_delimeter)
	{
		free(lst->hd_delimeter);
		lst->hd_delimeter = NULL;
	}
	if (lst->outfile_name)
	{
		ft_lstclear(&lst->outfile_name, free);
		lst->outfile_name = NULL;
	}
	if (lst->infile_name)
	{
		ft_lstclear(&lst->infile_name, free);
		lst->infile_name = NULL;
	}
	if (lst->args)
	{
		int i = 0;
		while (lst->args[i] && *lst->args[i])
		{
			free(lst->args[i]);
			lst->args[i] = NULL;
			i++;
		}
		free(lst->args);
		lst->args = NULL;
	}
	free(lst);
	lst = NULL;
}


void	input_clear(t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		input_delone(*lst);
		*lst = tmp;
	}
}

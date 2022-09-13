/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:26:05 by cstefany          #+#    #+#             */
/*   Updated: 2022/09/12 20:25:13 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/minishell.h"

t_input	*input_new()
{
	t_input	*list;

	list = (t_input	*)malloc(sizeof (t_input));
	if (!list)
		return (NULL);
	list->infile_name = NULL;
	list->outfile_name = NULL;
	list->hd_delimeter = NULL;
	list->args = NULL;
	list->builtin = FALSE;
	list->out_file = 1;
	list->in_file = 0;
	list->type_of_file = 0;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}



t_input	*input_last(t_input *lst)
{
	int	i;

	i = input_size(lst);
	while (i > 1)
	{
		lst = lst -> next;
		i--;
	}
	return (lst);
}

int	input_size(t_input *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

void	input_add_front(t_input **lst, t_input *new)
{
	new -> next = *lst;
    (*lst) -> prev = new;
	*lst = new;
}

void	input_add_back(t_input **lst, t_input **new)
{
	t_input	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = *new;
	else
	{
		tmp = input_last(*lst);
		tmp->next = *new;
		(*new) -> prev = tmp;
	}
}
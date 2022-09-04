/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:00 by falarm            #+#    #+#             */
/*   Updated: 2022/09/03 00:26:45 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isnum(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!ft_isdigit(arr[i++]))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_exit(t_input *inp, t_list *envp)
{
	(void) envp;
	if (double_arr_size(inp->args) == 1)
		exit(0);
	else
	{
		if (ft_isnum(inp->args[1]))
			exit(ft_atoi(inp->args[1]) % 256);
		else
		{
			ft_putstr_fd("exit: Illegal number: ", STDOUT_FILENO);
			ft_putendl_fd(inp->args[1], STDOUT_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

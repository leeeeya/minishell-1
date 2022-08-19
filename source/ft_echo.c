/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:36:22 by falarm            #+#    #+#             */
/*   Updated: 2022/08/18 14:27:07 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_input *inp, t_list *envp)
{
	int	f;
	int	i;

	(void) envp;
	f = TRUE;
	i = 1;
	if (inp->args[i] && !ft_strncmp(inp->args[i], "-n", 5))
	{
		i++;
		f = FALSE;
	}
	while (inp->args[i])
	{
		ft_putstr_fd(inp->args[i++], 1);
		if (inp->args[i])
			ft_putchar_fd(' ', 1);
	}
	write(1, "\n", f);
	return (0);
}

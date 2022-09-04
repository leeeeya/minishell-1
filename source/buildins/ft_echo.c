/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:36:22 by falarm            #+#    #+#             */
/*   Updated: 2022/09/03 00:24:35 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (EXIT_SUCCESS);
}

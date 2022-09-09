/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:54:38 by falarm            #+#    #+#             */
/*   Updated: 2022/09/04 19:21:43 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Ctrl + C
void	sigint_handler(int n)
{
	int	p;
	int	s;

	(void) n;
	p = waitpid(-1, &s, WNOHANG);
	if (p)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 1);
}

/*	Ctrl + \	*/
void	sigquit_handler(int n)
{
	int	p;
	int	s;

	(void) n;
	p = waitpid(-1, &s, WNOHANG);
	if (!p)
		ft_putendl_fd("Quit", 1);
}

//	Ctrl + D
void	eof_handler(t_data *data)
{
	free_data(data);
	exit(0);
}

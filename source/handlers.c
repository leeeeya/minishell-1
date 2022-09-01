/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:54:38 by falarm            #+#    #+#             */
/*   Updated: 2022/08/29 22:48:29 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Ctrl + C
void	sigint_handler(int n)
{
	(void) n;
}

//	Ctrl + \	//
void	sigquit_handler(int n)
{
	(void) n;
}

//	Ctrl + D
void	eof_handler(t_data *data)
{
	ft_putendl_fd("Ctrl + d", 1);
	free_data(data);
	exit(0);
}


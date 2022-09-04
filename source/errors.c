/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:06:09 by falarm            #+#    #+#             */
/*   Updated: 2022/09/04 19:24:19 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_malloc(t_data *data)
{
	data->exit_flag = TRUE;
	ft_putendl_fd(RED "Error: " CLOSE "malloc returned NULL!", 2);
}

void	my_perror(t_data *data)
{
	data->exit_status = errno;
	perror(RED "Error" CLOSE);
}

void	error_exit(void)
{
	perror(RED "Error" CLOSE);
	exit(errno);
}

int	error_str(char *s, int code)
{
	ft_putendl_fd(s, 2);
	return (code);
}

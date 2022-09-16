/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:48 by etobias           #+#    #+#             */
/*   Updated: 2022/09/16 19:16:56 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_line(char *line)
{
	size_t	i;

	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_space(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	return (c <= ' ' || c > 126);
}

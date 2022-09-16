/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:14 by etobias           #+#    #+#             */
/*   Updated: 2022/09/16 19:09:36 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_end_quote(char *line, char quote, size_t *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == quote)
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!find_end_quote(line, line[i], &i))
			{
				error_sentence(UNCLOSED_QUOTES_ERROR, SYNTAX_ERROR_CODE);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

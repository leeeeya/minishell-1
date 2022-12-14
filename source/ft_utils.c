/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:10:08 by falarm            #+#    #+#             */
/*   Updated: 2022/09/11 18:53:07 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstswap(t_list *first, t_list *second, t_list *tmp)
{
	void	*tmp_content;

	if (tmp)
		first->next->next = tmp;
	tmp_content = first->content;
	first->content = second->content;
	second->content = tmp_content;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

int	double_arr_size(char **arr)
{
	int		i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

size_t	len_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**split_by_first(char *s, char c)
{
	char	**res;
	char	*tmp;

	tmp = ft_strchr(s, '=');
	if (!tmp)
		return (NULL);
	else if (++tmp)
	{
		res = (char **) malloc(sizeof(char *) * 3);
		if (!res)
			return (NULL);
		res[0] = ft_substr(s, 0, len_word(s, c));
		res[1] = ft_substr(tmp, 0, ft_strlen(tmp));
		res[2] = NULL;
	}
	else
	{
		res = (char **) malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res[0] = ft_substr(s, 0, ft_strlen(s) - 1);
		res[1] = NULL;
	}
	return (res);
}

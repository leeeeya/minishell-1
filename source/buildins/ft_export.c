/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:21 by falarm            #+#    #+#             */
/*   Updated: 2022/09/04 23:44:57 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid(char *s)
{
	if (s && ft_isdigit(s[0]))
		return (FALSE);
	while (*s && *s != '=')
	{
		if (!ft_isalpha(*s) && !ft_isdigit(*s) && *s != '_')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

void	env_copy(t_list *envp)
{
	t_list	*tmp;
	t_envp	*elem;

	tmp = envp;
	while (tmp)
	{
		elem = tmp->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd("=", 1);
		if (elem->value)
			ft_putstr_fd(elem->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void	export_variable(t_list *envp, char *s)
{
	char	**key_value;
	t_envp	*elem;

	key_value = split_by_first(s, '=');
	if (key_value)
	{
		elem = init_envp(key_value[0], key_value[1]);
		add_env_value(envp, elem);
		free(key_value);
	}
}

int	ft_export(t_input *inp, t_list *envp)
{
	int		i;
	int		res;

	res = EXIT_SUCCESS;
	if (!inp->args[1])
		env_copy(envp);
	else
	{
		i = 0;
		while (inp->args[++i])
		{
			if (is_valid(inp->args[i]))
				export_variable(envp, inp->args[i]);
			else
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(inp->args[i], 2);
				res = error_str("': not a valid identifier", 1);
			}
		}
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:36:42 by falarm            #+#    #+#             */
/*   Updated: 2022/08/18 20:06:49 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_input *inp, t_list *envp)
{
	t_envp	*elem;
	int		size;
	char	*pwd;

	elem = init_envp("OLDPWD", get_envp_value(envp, "PWD"));
	add_env_value(envp, elem);
	size = double_arr_size(inp->args);
	if (size > 2)
		return (1);
	else if (size > 1)
		chdir(inp->args[1]);
	else
		chdir(get_envp_value(envp, "HOME"));
	pwd = getcwd(NULL, 0);
	elem = init_envp("PWD", pwd);
	free(pwd);
	add_env_value(envp, elem);
	return (errno);
}

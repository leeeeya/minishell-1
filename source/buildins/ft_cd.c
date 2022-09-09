/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:36:42 by falarm            #+#    #+#             */
/*   Updated: 2022/09/04 23:34:27 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_minus(t_list *envp)
{
	char	*tmp;
	char	*pwd;

	tmp = get_envp_value(envp, "OLDPWD");
	if (chdir(tmp) == -1)
		return (error_str("cd: OLDPWD not set", 1));
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(tmp, 1);
	add_env_value(envp, init_envp("PWD", tmp));
	add_env_value(envp, init_envp("OLDPWD", pwd));
	free(pwd);
	return (EXIT_SUCCESS);
}

int	cd_path(t_input *inp, t_list *envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (chdir(inp->args[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(inp->args[1], 2);
		return (error_str(": No such file or directory", 1));
	}
	add_env_value(envp, init_envp("OLDPWD", cwd));
	free(cwd);
	cwd = getcwd(NULL, 0);
	add_env_value(envp, init_envp("PWD", cwd));
	free(cwd);
	return (EXIT_SUCCESS);
}

int	cd_home(t_list *envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (chdir(get_envp_value(envp, "HOME")) == -1)
		return (error_str("cd: HOME is undefined", 1));
	add_env_value(envp, init_envp("OLDPWD", cwd));
	free(cwd);
	cwd = get_envp_value(envp, "HOME");
	add_env_value(envp, init_envp("PWD", cwd));
	return (EXIT_SUCCESS);
}

int	ft_cd(t_input *inp, t_list *envp)
{
	if (inp->args[1])
	{
		if (inp->args[2])
			return (error_str("cd: too many arguments", 1));
		else if (!ft_strcmp("-", inp->args[1]))
			return (cd_minus(envp));
		else
			return (cd_path(inp, envp));
	}
	else
		return (cd_home(envp));
}

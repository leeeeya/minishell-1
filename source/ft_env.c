/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:39:02 by falarm            #+#    #+#             */
/*   Updated: 2022/08/10 01:19:02 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_input *inp, t_list *envp)
{
	char	**envp_c;
	int		i;

	(void)inp;
	i = 0;
	envp_c = get_envp(envp);
	if (!envp_c)
		return (errno);
	while (envp_c[i])
		ft_putendl_fd(envp_c[i++], 1);
	free_double_arr(envp_c);
	return (0);
}

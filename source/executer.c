/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:00:35 by falarm            #+#    #+#             */
/*   Updated: 2022/09/12 18:30:41 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	my_dup(t_input *inp, int in, int out)
{
	if (inp->in_file != 0)
		in = inp->in_file;
	if (inp->out_file != 1)
		out = inp->out_file;
	if (dup2(in, 0) < 0)
		error_exit();
	if (dup2(out, 1) < 0)
		error_exit();
}

int	ft_buildins(t_data *data, t_input *inp)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(inp->args[0], data->buildins[i].name,
				ft_strlen(inp->args[0])))
		{
			data->exit_status = data->buildins[i].func(inp, &data->envp_list);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	my_execute(t_data *data, t_input *inp, int pipe_count, int pipe_id)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror(inp->args[0]);
	if (!pid)
	{
		if (!pipe_count)
			my_dup(inp, 0, 1);
		else if (!inp->prev)
			my_dup(inp, inp->in_file, data->pipes[1]);
		else if (!inp->next)
			my_dup(inp, data->pipes[2 * pipe_id - 2], inp->out_file);
		else
			my_dup(inp, data->pipes[2 * pipe_id - 2],
				data->pipes[2 * pipe_id + 1]);
		close_pipes(data, pipe_count);
		if (ft_buildins(data, inp))
			exit(data->exit_status);
		data->exit_status = 0;
		if (execve(inp->args[0], inp->args, get_envp(data->envp_list)))
			exit(EXIT_FAILURE);
	}
}

void	my_exec(t_data *data, t_input *inp)
{
	t_input	*tmp;
	int		pipe_count;
	int		pipe_id;

	if (!inp->next && ft_buildins(data, inp))
		return ;
	pipe_count = lst_size(inp) - 1;
	data->pipes = (int *) malloc(sizeof(int) * pipe_count);
	if (!data->pipes)
		return (error_malloc(data));
	if (init_pipes(data, pipe_count))
		return (my_perror(data));
	tmp = inp;
	pipe_id = 0;
	while (tmp)
	{
		signal(SIGQUIT, sigquit_handler);
		my_execute(data, tmp, pipe_count, pipe_id++);
		tmp = tmp->next;
	}
	close_pipes(data, pipe_count);
	while (pipe_id--)
		waitpid(-1, &pipe_count, 0);
	data->exit_status = check_exit_status(pipe_count);
}

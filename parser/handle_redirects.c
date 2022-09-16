/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:05 by etobias           #+#    #+#             */
/*   Updated: 2022/09/16 20:10:27 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_input_desc(t_app *app, size_t i, t_command *cmd)
{
	int	fd;

	if (cmd->input_desc > 2)
		close(cmd->input_desc);
	fd = open(app->tokens[i], O_RDONLY);
	if (fd < 0)
	{
		// change free
		free_tokens(app);
		free_cmds(app);
		error_exit("unable to open file\n");
	}
	return (fd);
}

static int	get_heredoc(t_app *app, size_t i, t_command *cmd)
{
	int		fd;
	char	*buf;

	if (cmd->input_desc > 2)
		close(cmd->input_desc);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	while (1)
	{
		buf = readline("heredoc> ");
		if (!ft_strncmp(app->tokens[i], buf, ft_strlen(app->tokens[i]) + 1))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	if (buf)
		free(buf);
	close(fd);
	fd = open(HEREDOC, O_RDONLY);
	return (fd);
}

static int	get_output_desc(t_app *app, size_t i, t_command *cmd, int append)
{
	int	fd;
	int	flags;

	if (cmd->output_desc > 2)
		close(cmd->output_desc);
	if (append)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(app->tokens[i], flags, 0000644);
	return (fd);
}

void	handle_redirects(t_app *app, size_t i, t_command *cmd)
{
	if (ft_strcmp(app->tokens[i], "<") == 0)
		cmd->input_desc = get_input_desc(app, ++i, cmd);
	else if (ft_strcmp(app->tokens[i], "<<") == 0)
		cmd->input_desc = get_heredoc(app, ++i, cmd);
	else if (ft_strcmp(app->tokens[i], ">") == 0)
		cmd->output_desc = get_output_desc(app, ++i, cmd, 0);
	else if (ft_strcmp(app->tokens[i], ">>") == 0)
		cmd->output_desc = get_output_desc(app, ++i, cmd, 1);
}

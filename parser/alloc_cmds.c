/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:23:57 by etobias           #+#    #+#             */
/*   Updated: 2022/09/16 20:11:37 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_command	*init_command()
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->input_desc = 0;
	cmd->output_desc = 1;
	cmd->args = NULL;
	return (cmd);
}

static t_list	*alloc_memory(t_app *app)
{
	int			i;
	t_list		*list;
	t_list		*tmp;
	t_command	*cmd;

	i = -1;
	tmp = NULL;
	while (++i < app->cmd_number)
	{
		cmd = init_command();
		if (tmp)
			tmp->next = ft_lstnew(cmd);
		else
		{
			list = ft_lstnew(cmd);
			tmp = list;
		}
		tmp = tmp->next;
	}
	return (list);
}

void	get_cmds(t_app *app)
{
	size_t		cmd_i;
	size_t		i;
	t_list		*tmp;
	t_command	*cmd;

	cmd_i = 0;
	i = -1;
	tmp = app->cmds;
	while (app->tokens[++i])
	{
		if (app->tokens[i][0] == '|')
			tmp = tmp->next;
		else if (app->tokens[i][0] == '<' || app->tokens[i][0] == '>')
		{
			cmd = tmp->content;
			handle_redirects(app, i++, cmd);
		}
		else
		{
			cmd = tmp->content;
			cmd->args = array_add(cmd->args, app->tokens[i]);
		}
	}
}

void	alloc_cmds(t_app *app)
{
	size_t	i;
	size_t	size;

	if (app->tokens == NULL)
	{
		app->cmds = NULL;
		return ;
	}
	i = 1;
	size = 1;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
			size++;
		i++;
	}
	app->cmd_number = size;
	app->cmds = alloc_memory(app);
	if (!app->cmds)
		error_exit("malloc failed to allocate memory (cmd_array)");
}

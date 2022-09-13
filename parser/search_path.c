#include "../include/parser.h"
#include "../include/minishell.h"

void join_slash(t_parse *d)
{
	int		i;
	char *tmp;

	i = 0;
	while (d->paths && d->paths[i] != NULL)
		i++;
	i = 0;
	while (d->paths[i] != NULL)
	{
		tmp =  ft_strjoin(d->paths[i], "/");
		free(d->paths[i]);
		check_error(tmp, d, "ft_strjoin");

		d->paths[i] = ft_strdup(tmp);
		free(tmp);
		check_error(d->paths[i], d, "ft_strdup");
		i++;
	}
}

int check_builtin(char *cmd, t_parse *d)
{
	int len;

	len = (int)ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len) ||
			!ft_strncmp(cmd, "cd", len) ||
			!ft_strncmp(cmd, "pwd", len) ||
			!ft_strncmp(cmd, "export", len) ||
			!ft_strncmp(cmd, "unset", len) ||
			!ft_strncmp(cmd, "env", len) ||
			!ft_strncmp(cmd, "exit", len))
		d->ready_data->builtin = TRUE;
	return d->ready_data->builtin;
}

void search_path(t_parse *d)
{
	int			i;
	char *tmp;

	i = 0;
	if (!d->env)
		return;
	while (d->env[i] && !ft_strnstr(d->env[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (!d->env[i])
		return;
	tmp = ft_strtrim(d->env[i], "PATH=");
	check_error(tmp, d, "ft_strtrim");

	d->paths = ft_split(tmp, ':');
	check_error(d->paths, d, "ft_split");
	free(tmp);
	tmp = NULL;

	join_slash(d);
}


int get_true_path(t_parse *d)
{
	int i;
	char *tmp_arg;

	i = 0;
	if (!d->ready_data->args)
		return 0;
	if (check_builtin(d->ready_data->args[0], d))
		return 0;
	int len = (int)ft_strlen(d->ready_data->args[0]);
	if (!ft_strncmp(d->ready_data->args[0], "..", len) ||
			!ft_strncmp(d->ready_data->args[0], ".", len))
	{
		print_error(d, d->ready_data->args[0], ": command not found");
		*d->exit_code = COM_NF;
		return ERROR;
	}
	if (access(d->ready_data->args[0], F_OK) == 0 && access(d->ready_data->args[0], X_OK) != 0)
	{
		print_error(d, d->ready_data->args[0], ": permission denied\n");
		*d->exit_code = PERM_DEN;
		return ERROR;
	}
	else if (d->paths)
	{
		tmp_arg = ft_strdup(d->ready_data->args[0]);
		free(d->ready_data->args[0]);
		check_error(tmp_arg, d, "ft_strdup");
		while (d->paths[i])
		{
			d->ready_data->args[0] = ft_strjoin(d->paths[i], tmp_arg);
			check_error(d->ready_data->args[0], d, "ft_strjoin");
			if (access(d->ready_data->args[0], X_OK) == 0)
			{
				free(tmp_arg);
				tmp_arg = NULL;
				break;
			}
			else
			{
				free(d->ready_data->args[0]);
				d->ready_data->args[0] = NULL;
			}
			i++;
		}
	}
	if (!d->ready_data->args[0] || access(d->ready_data->args[0], F_OK) != 0)
	{
		print_error(d, tmp_arg, ": command not found\n");
		free(tmp_arg);
		*d->exit_code = COM_NF;
		return ERROR;
	}
	if (tmp_arg)
		free(tmp_arg);
	return (0);
}

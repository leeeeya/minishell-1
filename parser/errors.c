#include "parser.h"

void free_all(t_data *d)
{
	int i;
	if (d->ready_data)
		input_clear(&d->ready_data);

	if (d->head_cmd_line && *d->head_cmd_line)
	{
		//printf("d->head_cmd_line: %p\n", d->head_cmd_line);
		free(d->head_cmd_line);
		d->head_cmd_line = NULL;
	}
	// if (d->cmd_line && *d->cmd_line)
	// {
	// 	printf("d->cmd_line: %p\n", d->cmd_line);
	// 	free(d->cmd_line);
	// 	d->cmd_line = NULL;
	// }
	if (d->env)
	{
		i = 0;
		while (d->env[i])
		{
			free(d->env[i]);
			d->env[i] = NULL;
			i++;
		}
		free(d->env);
		d->env = NULL;
	}
	if (d->paths)
	{
		i = 0;
		while (d->paths[i])
		{
			free(d->paths[i]);
			d->paths[i] = NULL;
			i++;
		}
		free(d->paths);
		d->paths = NULL;
	}
}

void	check_error(void *data, t_data *d, char *error)
{
	char	*err_str;

	if (!data)
	{
		free_all(d);
		err_str = ft_strjoin("minishell: ", error);
		if (!err_str)
		{
			perror("minishell: ft_strjoin");
			exit(errno);
		}
		perror(err_str);
		free(err_str);
		err_str = NULL;
		exit(errno);
	}
}

void	print_error(t_data *d, char *arg, char *error)
{
	(void) d;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
//	exit(1);
}
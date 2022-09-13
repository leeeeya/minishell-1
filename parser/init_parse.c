#include "parser.h"

void	init_parse(t_data *d, int *exit_code, char *cmd_line, char **env)
{
	char	*tmp;

	d->ready_data = input_new(exit_code);
	check_error(d->ready_data, d, "input_new");
	d->cmd_line = ft_strdup(cmd_line);
	tmp = ft_strtrim(d->cmd_line, "\n");
	check_error(tmp, d, "ft_strtrim");
	free(d->cmd_line);
	d->cmd_line = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	check_error(d->cmd_line, d, "ft_strdup");
	d->head_cmd_line = d->cmd_line;
	d->exit_code = exit_code;
	get_env(d, env);
	d->paths = NULL;
}

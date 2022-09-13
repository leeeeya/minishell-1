#include "../include/parser.h"
#include "../include/minishell.h"

int pars_quote(void **line_to_write, t_parse *d)
{
	d->cmd_line++;
	while(*d->cmd_line != '\'' && *d->cmd_line != '\0')
	{
		char *tmp = append(d, (char *) *line_to_write, *d->cmd_line);
		free(*line_to_write);
		*line_to_write = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		d->cmd_line++;
	}
	if (*d->cmd_line != '\0')
		d->cmd_line++;
	else
	{
		print_error(d, "syntax error near unexpected token ", "` ' `");
		*d->exit_code = 222;
		return ERROR;
	}
	return 0;
}

void shielding(t_parse *d, void **line_to_write)
{
	char tmp;

	d->cmd_line++;
	tmp = *d->cmd_line;
	d->cmd_line--;
	if (tmp != '$' && tmp != '\\' && tmp != '\"')
	{
		char *tmp_str = append(d, (char *) *line_to_write, *d->cmd_line);
		free(*line_to_write);
		*line_to_write = tmp_str;
		free(tmp_str);
		tmp_str = NULL;
		d->cmd_line++;
	}
	else
		d->cmd_line++;
}

int pars_doub_quote(void **line_to_write, t_parse *d)
{
	d->cmd_line++;
	while(*d->cmd_line != '\"' && *d->cmd_line != '\0')
	{
		if (*d->cmd_line == '\\')
			shielding(d, line_to_write);
		else if (*d->cmd_line == '$') {
            pars_env(line_to_write, d);
            continue;
        }
		char *tmp = append(d, (char *) *line_to_write, *d->cmd_line);
//		free(*line_to_write);
        *line_to_write = tmp;
		free(tmp);
		tmp = NULL;
		d->cmd_line++;
	}
	if (*d->cmd_line != '\0')
		d->cmd_line++;
	else if (*d->cmd_line == '\0')
	{
		print_error(d, "syntax error near unexpected token ", "` \" `");
		*d->exit_code = 111;
		return ERROR;
	}
	return (0);
}
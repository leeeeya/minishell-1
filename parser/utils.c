#include "../include/parser.h"
#include "../include/minishell.h"

char *append(t_parse *d, char *str, char ch)
{
	char *res;
	int i;

	i = 0;
	res = ft_calloc(ft_strlen(str) + 2, sizeof (char));
	check_error(res, d, "ft_calloc");
	while(str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = ch;
	res[++i] = '\0';
//	if(str)
//	{
//		printf("str ptr: %p\n", str);
//		free(str);
//		str = NULL;
//	}
	return res;
}


int itter(t_parse *d, void **line_to_write, char type)
{
	if (*d->cmd_line == '\"')
    {
		if (pars_doub_quote(line_to_write, d) < 1)
			return ERROR;
		return 1;
	}
	else if (*d->cmd_line == '\'')
	{
		if (pars_quote(line_to_write, d) < 1)
			return ERROR;
		return 1;
	}
	else if (type != 'd' && *d->cmd_line == '$')
	{
		pars_env(line_to_write, d);
		return 1;
	}
	else if (*d->cmd_line == '\\')
		d->cmd_line++;
	return 0;
}

int get_valid_fn(t_parse *d, t_list **fns)
{
	t_list *new = NULL;
	char *file_name = NULL;

	while (*d->cmd_line)
	{
		int val = itter(d, &file_name, 'f');
		if (val > 0)
			continue;
		else if (val < 0)
			return ERROR;
		if (*d->cmd_line == ' ' || *d->cmd_line == '>' || *d->cmd_line == '|' || *d->cmd_line == '<')
			break;
		char *tmp = append(d, file_name, *d->cmd_line);
		free(file_name);
		file_name = tmp;
		tmp = NULL;
		d->cmd_line++;
	}
	if ( file_name)
	{
		new = ft_lstnew(file_name);
		file_name = NULL;
		ft_lstadd_back(fns, new);
		new = NULL;
		return 1;
	}
	return 0;
}

int handle_spaces(t_parse *d, char type)
{
	if (*d->cmd_line == ' ')
	{
		while (*d->cmd_line == ' ')
			d->cmd_line++;
		if (*d->cmd_line == '<')
		{
			print_error(d, "syntax error near unexpected token ", "`<'");
			*d->exit_code = UNEXP;
			return ERROR;
		}
		if (*d->cmd_line == '>')
		{
			print_error(d, "syntax error near unexpected token ", "`>'");
			*d->exit_code = UNEXP;
			return ERROR;
		}
		if (*d->cmd_line == '|')
		{
			print_error(d, "syntax error near unexpected token ", "`|'");
			*d->exit_code = UNEXP;
			return ERROR;
		}
		if (type == 'i' && (*d->cmd_line == '\n' || *d->cmd_line == '\0'))
		{
			print_error(d, "syntax error near unexpected token ", "`newline'");
			*d->exit_code = UNEXP;
			return ERROR;
		}
	}
	return 0;
}

int handle_ifn(t_parse *d)
{
	if (*d->cmd_line == '>')
		d->cmd_line++;
	if (*d->cmd_line == '\n' || *d->cmd_line == '\0')
	{
		print_error(d, "syntax error near unexpected token ", "`newline'");
		*d->exit_code = UNEXP;
		return ERROR;
	}
	if (*d->cmd_line == '>')
	{
		print_error(d, "syntax error near unexpected token ", "`>'");
		*d->exit_code = UNEXP;
		return ERROR;
	}
	if (*d->cmd_line == '|')
	{
		print_error(d, "syntax error near unexpected token ", "`|'");
		*d->exit_code = UNEXP;
		return ERROR;
	}
	return 0;
}
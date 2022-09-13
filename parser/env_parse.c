#include "../include/parser.h"
#include "../include/minishell.h"

void get_env(t_parse *d, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	if (!i)
		return;
	d->env = (char **)ft_calloc(i + 1, sizeof (char *));
	check_error(d->env, d,"ft_calloc");
	i = 0;
	while(env[i])
	{
		d->env[i] = ft_strdup(env[i]);
		check_error(d->env[i], d,"ft_strdup");
		i++;
	}
}

char *get_value_env(t_parse *d, char *key)
{
	char *value;
	int i;

	value = NULL;
	i = 0;
	while(d->env && d->env[i])
	{
		if (ft_strnstr(d->env[i], key, ft_strlen(key)))
		{
			value = ft_strchr(d->env[i], '=');
			value++;
			break;
		}
		i++;
	}
	if (value == NULL)
		return NULL;
	return value;
}


void pars_env(void **line_to_write, t_parse *d)
{
	int i;
	char *key;
	char *env;
	char *tmp;

	i = 0;
	d->cmd_line++;
	if (*d->cmd_line == ' ' || !*d->cmd_line)
	{
		*line_to_write = ft_strdup("$");
		return;
	}
	if (*d->cmd_line == '\'')
		return;
	if (*d->cmd_line == '?')
	{
		d->cmd_line++;
		tmp = ft_strjoin((char *) *line_to_write, ft_itoa(*d->exit_code));
		*line_to_write = ft_strdup(tmp);
		return;
	}
	key = ft_strdup(d->cmd_line);
	check_error(key, d, "ft_strdup");
	env = NULL;
	while (key[i] != ' ' && key[i] != '|' && key[i] != '$' && key[i] != '\\'
						&& key[i] != '\'' && key[i] != '\"' && key[i] != '<' &&
						key[i] != '>' && key[i] != '/' && key[i] != '\0' && key[i] != '\n')
	{
		i++;
		d->cmd_line++;
	}
	key[i] = '\0';
	env = get_value_env(d, key);
	if (!env)
		return;
	tmp = ft_strjoin((char *) *line_to_write, env);
//	free(*line_to_write);
	check_error(tmp, d, "ft_strjoin");
	*line_to_write = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	free(key);
	key = NULL;
	check_error(*line_to_write, d, "ft_strdup");
}
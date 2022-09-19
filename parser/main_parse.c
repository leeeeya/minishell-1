//#include "../include/parser.h"
#include "../include/minishell.h"

void get_heredoc_fd(t_parse *d)
{
	int fd = 0;
	char *s;
	while (d->ready_data->hd_delimeter)
	{
		if (!d->ready_data->hd_delimeter->next)
			fd = open("heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
		s = readline(">");
		while (ft_strncmp(d->ready_data->hd_delimeter->content, s, ft_strlen(s) - 1))
		{
			if (fd)
			{
				write(fd, s, ft_strlen(s));
				write(fd, "\n", 1);
			}
			free(s);
			s = NULL;
			s = readline(">");
		}
		if (s)
			free(s);
		d->ready_data->hd_delimeter = d->ready_data->hd_delimeter->next;
	}
	if (fd<2)
		close(fd);
}


int get_delimeter(t_parse *d)
{
	d->cmd_line++;
	if (*d->cmd_line == '\n' || *d->cmd_line == '\0')
	{
		print_error(d, "syntax error near unexpected token ", "`newline'");
		*d->exit_code = UNEXP;
		return ERROR;
	}
	while (*d->cmd_line == ' ')
		d->cmd_line++;
	if (get_valid_fn(d, &d->ready_data->hd_delimeter) < 0)
		return ERROR;
	return 0;
//	if (get_valid_fn(d, &d->ready_data->hd_delimeter))
//		return 1;
//	if (!*d->cmd_line)
//		return 1;
//	return 0;
}


int get_infile_name(t_parse *d)
{
	if (*d->cmd_line == '<')
	{
		d->cmd_line++;
		if (*d->cmd_line == '<')
		{
			if (get_delimeter(d) < 0)
				return ERROR;
			t_list * new = ft_lstnew("heredoc");
			ft_lstadd_back(&d->ready_data->infile_name, new);
			return 1;
		}
		if (*d->cmd_line == ' ')
		{
			while(*d->cmd_line == ' ')
				d->cmd_line++;
			if (*d->cmd_line == '>')
			{
				print_error(d, "syntax error near unexpected token ", "`>'");
				*d->exit_code = UNEXP;
				return ERROR;
			}
			if (*d->cmd_line == '<')
			{
				print_error(d, "syntax error near unexpected token ", "`<'");
				*d->exit_code = UNEXP;
				return ERROR;
			}
		}
		if (handle_ifn(d) < 0)
			return ERROR;
//		handle_spaces(d, 'i');

		int val = get_valid_fn(d, &d->ready_data->infile_name);
		if (val > 0)
			return 1;
		else if (val <0)
			return ERROR;
	}
	if (!*d->cmd_line)
		return 1;
	return 0;
}

int get_outfile_name(t_parse *d)
{
	if (*d->cmd_line == '>')
	{
		d->cmd_line++;
		if (handle_spaces(d, 'o') < 0)
			return ERROR;
		if (*d->cmd_line == '\n' || *d->cmd_line == '|' || *d->cmd_line == '\0')
		{
			print_error(d, "syntax error near unexpected token ", "`newline'");
			*d->exit_code = UNEXP;
			return ERROR;
		}
//		if (*d->cmd_line == '\\')
//		{
//			print_error(d, "syntax error near unexpected token ", "`\\'");
//			exit(1);
//		}
//		if (*d->cmd_line == '>')
//		{
//			d->ready_data->type_of_file = O_APPEND;
//			d->cmd_line++;
//		}
		else
			d->ready_data->type_of_file = O_RDWR;
		int val = get_valid_fn(d, &d->ready_data->outfile_name);

		if (val >0)
			return 1;
		else if (val < 0)
			return ERROR;
	}
	if (!*d->cmd_line)
		return 1;
	return 0;
}

int check_accesses_inf(t_parse *d)
{
	t_list *head;

	head = d->ready_data->infile_name;
	while (d->ready_data->infile_name)
	{
		// todo handle error
		if (d->ready_data->infile_name->content && access(d->ready_data->infile_name->content, R_OK) != 0)
		{
			char *tmp = ft_strjoin(d->ready_data->infile_name->content, ": ");
			print_error(d,  tmp, strerror(errno));
			*d->exit_code = NO_F;
			return ERROR;
		}
		else if (!d->ready_data->infile_name->next && d->ready_data->infile_name->content)
			d->ready_data->in_file = open(d->ready_data->infile_name->content, O_RDONLY);
		d->ready_data->infile_name = d->ready_data->infile_name->next;
	}
	d->ready_data->infile_name = head;
//	ft_listclear(&head);
	return 0;
}

int check_accesses_outf(t_parse *d)
{
	t_list *head;

	head = d->ready_data->outfile_name;
	while (d->ready_data->outfile_name)
	{
		if (d->ready_data->outfile_name->content && access(d->ready_data->outfile_name->content, W_OK) != 0
			&& access(d->ready_data->outfile_name->content, F_OK) == 0)
		{
			char *tmp = ft_strjoin(d->ready_data->outfile_name->content, ": ");
			print_error(d,  tmp, strerror(errno));
			*d->exit_code = NO_F;
			return ERROR;
		}
		else if (*(char *)d->ready_data->outfile_name->content)
		{
			if (access(d->ready_data->outfile_name->content, F_OK) != 0) {
				// todo handle error
				if (d->ready_data->type_of_file == O_APPEND)
					d->ready_data->out_file = open(d->ready_data->outfile_name->content, O_CREAT | O_RDWR | O_APPEND, 0644);
				else
					d->ready_data->out_file = open(d->ready_data->outfile_name->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			}
			else if (!d->ready_data->outfile_name->next)
			{
				if (d->ready_data->type_of_file == O_APPEND)
					d->ready_data->out_file = open(d->ready_data->outfile_name->content, O_RDWR | O_APPEND);
				else
					d->ready_data->out_file = open(d->ready_data->outfile_name->content, O_RDWR | O_TRUNC);
			}
		}
		d->ready_data->outfile_name = d->ready_data->outfile_name->next;
	}
//	for( int i = 0; i < 3; i++)
//	{
//		ft_putnbr_fd(i, d->ready_data->out_file);
//	}
	d->ready_data->outfile_name = head;
//	ft_listclear(&head);
	return 0;
}

t_input *parser(char *cmd_line, int *exit_code, char **env)
{
	t_parse d;
	t_input *head;
	char    *tmp;

	//// init data
    d.ready_data = input_new();
	check_error(d.ready_data, &d, "input_new");
	d.cmd_line = ft_strdup(cmd_line);
	tmp = ft_strtrim(d.cmd_line, "\n");
	check_error(tmp, &d, "ft_strtrim");
	free(d.cmd_line);
	d.cmd_line = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	check_error(d.cmd_line, &d, "ft_strdup");
	head = d.ready_data;
	d.head_cmd_line = d.cmd_line;
	d.exit_code = exit_code;
	get_env(&d, env);
	d.paths = NULL;


	//// main loop
	while (*d.cmd_line)
	{
		while (*d.cmd_line == ' ')
			d.cmd_line++;

		int val = get_infile_name(&d);
		if (val > 0)
			continue;
		else if (val < 0)
			return (t_input *)ERROR;

		val = get_outfile_name(&d);
		if (val > 0)
			continue;
		else if (val < 0)
			return (t_input *)ERROR;

		if (*d.cmd_line == '|')
		{
			d.cmd_line++;
			if (*d.cmd_line == '|')
			{
				print_error(&d, "unexpected token ", "`|'");
				*d.exit_code = 111;
				return (t_input *)ERROR;
			}
			while (*d.cmd_line == ' ')
				d.cmd_line++;
			if (*d.cmd_line == '\n' || *d.cmd_line == '\0')
			{
				print_error(&d, "syntax error near unexpected token ", "`|'");
				*d.exit_code = 111;
				return (t_input *)ERROR;
			}
			t_input *new = input_new();
			input_add_back(&d.ready_data, &new);
			d.ready_data = d.ready_data->next;
			continue;
		}
		get_args(&d);
	}
	if (d.ready_data->args && *d.ready_data->args)
		search_path(&d);
	d.ready_data = head;
	while (d.ready_data)
	{
		get_heredoc_fd(&d);
		if (check_accesses_inf(&d) < 0)
			return (t_input *)ERROR;
		if (check_accesses_outf(&d) < 0)
			return (t_input *)ERROR;
		if (get_true_path(&d) < 0)
			return (t_input *)ERROR;
		d.ready_data = d.ready_data->next;
	}

	d.ready_data = head;



	// int i = 0;
	// while (d.ready_data)
	// {
	// 	printf("first pipe:\n\n");
	// 	printf("infile: ");
	// 	if (d.ready_data->infile_name)
	// 		printf("%s\n", ft_lstlast(d.ready_data->infile_name)->content);
	// 	else
	// 		printf("\n");
	// 	printf("outfile: ");
	// 	if (d.ready_data->outfile_name)
	// 		printf("%s\n", ft_lstlast(d.ready_data->outfile_name)->content);
	// 	else
	// 		printf("\n");

	// 	printf("hd: ");
	// 	if (d.ready_data->hd_delimeter)
	// 		printf("%s\n", ft_lstlast(d.ready_data->hd_delimeter)->content);
	// 	else
	// 		printf("\n");


	// 	printf("fd_i: %d\nfd_o: %d\ntof: %d\nargs: ",
	// 		   d.ready_data->in_file, d.ready_data->out_file,
	// 		   d.ready_data->type_of_file);
	// 	while (d.ready_data->args && d.ready_data->args[i]) {
	// 		printf("%s ", d.ready_data->args[i]);
	// 		i++;
	// 	}
	// 	printf("\n\n\n");
	// 	d.ready_data = d.ready_data->next;
	// 	i = 0;
	// }
	// d.ready_data = head;
	// free_all(&d);
	return (head);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void) argc;
// 	(void) argv;
// 	char *cmd_line = get_next_line(0);
// 	int exit_code = 0;
// 	parser(cmd_line, &exit_code, env);
// }


// 1 todo absolute path cmd  	DONE
// 2 todo file access && fd 	DONE
// 3 todo handle errors   (perror, strerror)
// 7 todo handle exit_codes
// 4 todo || && ; и др необрабатываемые сиволы  ?????
// 6 todo if several '>' create all files, get last fd 	DONE
// 8 todo HEREDOC !!!!!  DONE

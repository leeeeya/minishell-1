#include "parser.h"

int next_arg(t_data *d, t_list **arg_lst)
{
	t_list *new;

	new = NULL;
	if (*d->cmd_line == ' ')
	{
		while(*d->cmd_line == ' ')
			d->cmd_line++;
		if (*d->cmd_line)
		{
			if (*d->cmd_line == '<' || *d->cmd_line == '|' || *d->cmd_line == '>')
				return 0 ;
			new = ft_lstnew("");
			ft_lstadd_back(arg_lst, new);
			(*arg_lst) = (*arg_lst)->next;
		}
		return 1;
	}
	return 2;
}

void fetch_arg_array(t_data *d, t_list **arg_lst)
{
	d->ready_data->args = (char **)ft_calloc(ft_lstsize(*arg_lst) + 1, sizeof (char *));
	check_error(d->ready_data->args, d, "ft_calloc");
	int i = 0;
	while (*arg_lst != NULL)
	{
		d->ready_data->args[i] = ft_strdup((*arg_lst)->content);
		check_error(d->ready_data->args[i], d, "ft_strdup");
		i++;
		*arg_lst = (*arg_lst)->next;
	}
	d->ready_data->args[i] = NULL;
}

int get_args(t_data *d)
{
	t_list	*arg_lst = NULL;
	t_list *head = NULL;
	int res;

	while (*d->cmd_line == ' ')
		d->cmd_line++;
	if (!*d->cmd_line)
		return 0;
	arg_lst = ft_lstnew("");
	head = arg_lst;
	while (*d->cmd_line)
	{
		int val = itter(d, &arg_lst->content, 'a');
		if (val >0)
			continue;
		else if (val < 0)
			return ERROR;

		if (*d->cmd_line == '<' || *d->cmd_line == '|' || *d->cmd_line ==  '>')
			break ;
		res = next_arg(d, &arg_lst);
		if (!res)
			break;
		else if (res == 1)
			continue;
		char *tmp = append(d, arg_lst->content, *d->cmd_line);
		if (*arg_lst->content)
			free(arg_lst->content);
		arg_lst->content = tmp;
//		free(tmp);
		tmp = NULL;
		d->cmd_line++;
	}
	arg_lst = head;
	if (*arg_lst->content)
		fetch_arg_array(d, &arg_lst);
//	ft_lstclear(&head, free);
	return 0;
}

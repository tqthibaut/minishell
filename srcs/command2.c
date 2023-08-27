/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:20:29 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 01:10:14 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null_tab(t_info *info)
{
	t_arg_info	*tmp;
	int			i;
	int			u;

	tmp = info->list_arg;
	while (tmp)
	{
		i = 0;
		u = 0;
		while (i < tmp->size)
		{
			if (tmp->tab_null[i] == FALSE)
				tmp->cmd[u++] = tmp->cmd[i];
			i++;
		}
		if (u != 0)
			tmp->cmd[u] = NULL;
		if (u == 0 && i > 0)
			tmp->execute = FALSE;
		tmp = tmp->next;
	}
}

int	is_pipe(t_arg *arg)
{
	if (arg->quote == FALSE && ft_strncmp(arg->str, "|", 2) == 0)
		return (TRUE);
	return (FALSE);
}

int	get_cmd_size(t_arg *arg)
{
	t_arg	*tmp;
	int		count;

	tmp = arg;
	count = 0;
	while (tmp && is_pipe(tmp) == FALSE)
	{
		if (is_red(tmp->str, tmp->quote) == TRUE)
			tmp = tmp->next->next;
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

int	init_list(t_arg_info *list, int index, t_info *info)
{
	list->execute = TRUE;
	list->next = NULL;
	list->index = index;
	list->newcmd = NULL;
	list->is_in = NOTHING;
	list->is_out = NOTHING;
	list->infilefd = -1;
	list->outfilefd = -1;
	list->childpid = -2;
	list->infile_name = NULL;
	list->size = 0;
	list->size = get_cmd_size(info->current_arg);
	list->cmd = malloc(sizeof(char *) * (list->size + 1));
	if (!list->cmd)
	{
		free(list);
		return (print_error(MALLOC, NULL));
	}
	return (0);
}

int	start_red(t_info *info, t_arg_info *list)
{
	if (do_red(info, list) == ERROR)
	{
		if (list->infile_name)
			free(list->infile_name);
		if (list->newcmd)
			free(list->newcmd);
		free(list->cmd);
		free(list);
		return (ERROR);
	}
	return (0);
}

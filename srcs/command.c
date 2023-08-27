/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:54:37 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 00:53:19 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_cmd(t_info *info, t_arg_info *list, int i)
{
	while (info->current_arg)
	{
		if (list->execute == FALSE)
			return (0);
		if (is_pipe(info->current_arg) == TRUE)
			break ;
		if (is_red(info->current_arg->str, info->current_arg->quote) == TRUE)
		{
			if (start_red(info, list) == ERROR)
				return (ERROR);
			info->current_arg = info->current_arg->next->next;
		}
		else
		{
			if (info->current_arg->null == FALSE)
				list->tab_null[i] = FALSE;
			else
				list->tab_null[i] = TRUE;
			list->cmd[i++] = info->current_arg->str;
			info->current_arg = info->current_arg->next;
		}
	}
	list->cmd[i] = NULL;
	return (0);
}

static int	init_cmd(t_arg_info *list, int index, t_info *info)
{
	if (init_list(list, index, info) == ERROR)
		return (ERROR);
	list->tab_null = malloc(sizeof(int) * (list->size));
	if (!list->tab_null)
	{
		free(list->cmd);
		free(list);
		print_error(MALLOC, NULL);
		return (ERROR);
	}
	return (0);
}

static t_arg_info	*get_cmd(t_info *info, int index)
{
	t_arg_info	*list;
	int			i;

	i = 0;
	list = malloc(sizeof(t_arg_info));
	if (!list)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	if (init_cmd(list, index, info) == ERROR)
		return (NULL);
	if (info->list_arg == NULL)
		info->list_arg = list;
	else
		info->current_list_arg->next = list;
	if (fill_cmd(info, list, i) == ERROR)
		return (NULL);
	return (list);
}

int	parse_cmd(t_info *info)
{
	int	i;

	i = 1;
	info->current_arg = info->arg;
	info->list_arg = get_cmd(info, i++);
	info->current_list_arg = info->list_arg;
	if (info->list_arg == NULL)
		return (ERROR);
	info->current_list_arg = info->list_arg;
	while (info->current_arg)
	{
		if (is_pipe(info->current_arg) == TRUE)
			info->current_arg = info->current_arg->next;
		info->current_list_arg->next = get_cmd(info, i++);
		if (info->current_list_arg->next == NULL)
			return (ERROR);
		info->current_list_arg = info->current_list_arg->next;
	}
	if (check_access(info) == ERROR)
		return (ERROR);
	if (get_tab_env(info) == ERROR)
		return (ERROR);
	return (0);
}

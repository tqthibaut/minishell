/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:28:28 by jgao              #+#    #+#             */
/*   Updated: 2022/04/06 18:13:31 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all(t_arg_info *list)
{
	t_arg_info	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->infile_name)
			unlink(tmp->infile_name);
		tmp = tmp->next;
	}
}

void	reset_free(t_info *info)
{
	if (info->buffer)
	{
		free(info->buffer);
		info->buffer = NULL;
	}
	free_arg(&info->arg);
	unlink_all(info->list_arg);
	free_list_arg(&info->list_arg);
	if (info->list_env.tab_env)
		free(info->list_env.tab_env);
	if (info->pipe.pipefd)
		free(info->pipe.pipefd);
}

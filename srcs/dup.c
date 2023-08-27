/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:53:00 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:33:23 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_dup(t_info *info)
{
	dup2(info->fdsave[0], STDIN);
	dup2(info->fdsave[1], STDOUT);
}

void	close_dup(t_info *info)
{
	if (info->current_list_arg->childpid == 0)
	{
		close(info->fdsave[0]);
		close(info->fdsave[1]);
	}
}

void	close_list_fd(t_arg_info *list)
{
	t_arg_info	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->infilefd != -1)
			close(tmp->infilefd);
		if (tmp->outfilefd != -1)
			close(tmp->outfilefd);
		tmp = tmp->next;
	}
}

void	which_dup(t_info *info)
{
	int	index;

	close_dup(info);
	index = info->current_list_arg->index - 1;
	if (info->current_list_arg->is_in == TRUE
		|| info->current_list_arg->is_in == HEREDOC)
		dup2(info->current_list_arg->infilefd, STDIN);
	else
	{
		if (info->current_list_arg->index != 1)
			if (info->current_list_arg->childpid == 0)
				dup2(info->pipe.pipefd[index * 2 - 2], STDIN);
	}
	if (info->current_list_arg->is_out == TRUE)
		dup2(info->current_list_arg->outfilefd, STDOUT);
	else
	{
		if (info->current_list_arg->next != NULL)
			if (info->current_list_arg->childpid == 0)
				dup2(info->pipe.pipefd[index * 2 + 1], STDOUT);
	}
	close_list_fd(info->list_arg);
}

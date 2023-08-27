/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:02:04 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 22:55:21 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_pipe(int i, t_info *info, int status)
{
	while (i <= info->pipe.nbpipe)
	{
		waitpid(info->current_list_arg->childpid, &status, 0);
		if (!info->current_list_arg->next)
		{
			if (WIFEXITED(status) == TRUE)
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) == TRUE)
			{
				g_exit_status = 128 + WTERMSIG(status);
				if (g_exit_status == 131)
					printf("Quit (core dumped)\n");
			}
		}
		i++;
		info->current_list_arg = info->current_list_arg->next;
	}
}

void	wait_child(t_info *info)
{
	int	status;

	status = 0;
	info->current_list_arg = info->list_arg;
	if (info->pipe.nbpipe > 0)
		wait_pipe(0, info, status);
	if (info->pipe.nbpipe == 0
		&& check_built_in(info->current_list_arg->cmd[0]) == FALSE)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) == TRUE)
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) == TRUE)
		{
			g_exit_status = 128 + WTERMSIG(status);
			if (g_exit_status == 131)
				printf("Quit (core dumped)\n");
		}
	}
}

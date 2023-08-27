/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:12:26 by jgao              #+#    #+#             */
/*   Updated: 2022/04/05 13:05:33 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	close_pipe(t_info *info)
{
	int	i;

	i = 0;
	if (!info->pipe.nbpipe)
		return ;
	if (info->pipe.nbpipe > 0)
		while (i < info->pipe.nbpipe * 2)
			close(info->pipe.pipefd[i++]);
}

static void	find_nb_pipe(t_info *info)
{
	t_arg	*tmp;

	tmp = info->arg;
	info->pipe.nbpipe = 0;
	while (tmp)
	{
		if (is_pipe(tmp) == TRUE)
			info->pipe.nbpipe++;
		tmp = tmp->next;
	}
}

int	create_pipe(t_info *info)
{
	int	i;

	i = 0;
	find_nb_pipe(info);
	if (info->pipe.nbpipe == 0)
		return (1);
	info->pipe.pipefd = malloc(sizeof (int) * info->pipe.nbpipe * 2);
	if (!info->pipe.pipefd)
		return (print_error(MALLOC, NULL));
	while (i < info->pipe.nbpipe)
	{
		if (pipe(info->pipe.pipefd + (2 * i++)) == -1)
		{
			perror("Pipe:");
			g_exit_status = 32;
			return (ERROR);
		}
	}
	return (0);
}

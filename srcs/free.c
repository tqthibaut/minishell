/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:56:34 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:21:18 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(t_arg **arg)
{
	t_arg	*tmp;

	while (*arg)
	{
		tmp = *arg;
		*arg = (*arg)->next;
		free(tmp->str);
		free(tmp);
		tmp = NULL;
	}
}

void	tab_free(char ***tab)
{
	int	i;

	i = 0;
	if (*tab)
	{
		while ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i++] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_info(t_info *info)
{
	if (info->buffer)
	{
		free(info->buffer);
		info->buffer = NULL;
	}
	free_arg(&info->arg);
	free_list_env(&info->list_env);
	free_list_arg(&info->list_arg);
	if (info->list_env.tab_env)
		free(info->list_env.tab_env);
	close(info->fdsave[0]);
	close(info->fdsave[1]);
	close_pipe(info);
	if (info->pipe.pipefd)
		free(info->pipe.pipefd);
}

void	free_all_no_unlink(t_info *info)
{
	if (info->buffer)
	{
		free(info->buffer);
		info->buffer = NULL;
	}
	free_arg(&info->arg);
	free_list_arg(&info->list_arg);
	if (info->list_env.tab_env)
		free(info->list_env.tab_env);
	close(info->fdsave[0]);
	close(info->fdsave[1]);
	close_pipe(info);
	if (info->pipe.pipefd)
		free(info->pipe.pipefd);
}

void	free_all_with_unlink(t_info *info)
{
	info->current_list_arg = info->list_arg;
	if (info->buffer)
	{
		free(info->buffer);
		info->buffer = NULL;
	}
	free_arg(&info->arg);
	while (info->current_list_arg)
	{
		if (info->current_list_arg->infile_name)
		{
			unlink(info->current_list_arg->infile_name);
			free(info->current_list_arg->infile_name);
		}
		info->current_list_arg = info->current_list_arg->next;
	}
	free_list_arg(&info->list_arg);
	if (info->list_env.tab_env)
		free(info->list_env.tab_env);
	close(info->fdsave[0]);
	close(info->fdsave[1]);
	close_pipe(info);
	if (info->pipe.pipefd)
		free(info->pipe.pipefd);
}

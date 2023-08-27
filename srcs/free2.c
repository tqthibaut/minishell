/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:33:08 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:55:44 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_arg_info *tmp)
{
	if (tmp->is_in == TRUE || tmp->is_in == HEREDOC)
		close(tmp->infilefd);
	if (tmp->is_out == TRUE)
		close(tmp->outfilefd);
}

static void	free_list_arg_next(t_arg_info *tmp)
{
	if (tmp->tab_null)
	{
		free(tmp->tab_null);
		tmp->tab_null = NULL;
	}
	close_fd(tmp);
	if (tmp->infile_name)
		free(tmp->infile_name);
	free(tmp);
}

void	free_list_arg(t_arg_info **list)
{
	t_arg_info	*tmp;

	tmp = *list;
	while (tmp)
	{
		*list = (*list)->next;
		if (tmp->newcmd)
		{
			free(tmp->newcmd);
			tmp->newcmd = NULL;
		}
		if (tmp->cmd)
		{
			free(tmp->cmd);
			tmp->cmd = NULL;
		}
		free_list_arg_next(tmp);
		tmp = NULL;
		tmp = *list;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = NULL;
	}
}

void	free_list_env(t_list_env *env)
{
	free_env(env->envp);
	free_env(env->exp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:00:33 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:19:30 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_info *info)
{
	info->buffer = NULL;
	info->cmd_error = NULL;
	info->arg = NULL;
	info->list_arg = NULL;
	info->list_env.tab_env = NULL;
	info->pipe.pipefd = NULL;
	info->sig_int = 0;
	info->pipe.nbpipe = 0;
	info->parent_status = TRUE;
	sig_ignore(SIGQUIT);
	sig_int_set(SIGINT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:08:09 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 02:21:15 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_cd(t_info *info)
{
	char	*path;

	path = parse_cd(info->current_list_arg);
	if (!path)
	{
		free_info(info);
		exit(1);
	}
	if (check_path(path, info->current_list_arg->cmd[1]) == FALSE)
	{
		free(path);
		free_info(info);
		exit(1);
	}
	chdir(path);
	change_env(info->list_env.envp, path, ENV, NULL);
	change_env(info->list_env.exp, path, EXPORT, NULL);
	free(path);
}

void	child_cd(t_info *info)
{
	int		i;

	i = 0;
	while (info->current_list_arg->cmd[i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			free_info(info);
			exit(1);
		}
		i++;
	}
	if (i == 1)
	{
		free_info(info);
		exit(1);
	}
	next_cd(info);
	free_info(info);
	exit(0);
}

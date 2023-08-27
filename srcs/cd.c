/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:28:54 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 13:15:58 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_cd(t_arg_info *arg)
{
	char	current_path[2048];
	char	*ret_path;
	char	**split_path;

	if (arg->cmd[1][0] == '/')
		return (absolute_path(arg));
	if (getcwd(current_path, 2048) == NULL)
	{
		ft_putstr_fd("Error during cd parsing\n", 2);
		return (NULL);
	}
	split_path = ft_split(arg->cmd[1], '/');
	if (!split_path)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	ret_path = relative_path(split_path, current_path);
	tab_free(&split_path);
	if (!ret_path)
		return (NULL);
	return (ret_path);
}

int	check_path(char *path, char *cmd)
{
	int		fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(cmd);
		return (FALSE);
	}
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(cmd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int	check_path_and_chdir(t_info *info)
{
	char	*path;

	path = parse_cd(info->current_list_arg);
	if (!path)
	{
		g_exit_status = 1;
		return (FALSE);
	}
	if (check_path(path, info->current_list_arg->cmd[1]) == FALSE)
	{
		free(path);
		g_exit_status = 1;
		return (FALSE);
	}
	chdir(path);
	change_env(info->list_env.envp, path, ENV, NULL);
	change_env(info->list_env.exp, path, EXPORT, NULL);
	if (path)
		free(path);
	g_exit_status = 0;
	return (0);
}

int	built_in_cd(t_info *info)
{
	int		i;

	i = 0;
	if (info->current_list_arg->childpid == 0)
		child_cd(info);
	while (info->current_list_arg->cmd[i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	if (i == 1)
	{
		g_exit_status = 0;
		return (0);
	}
	if (check_path_and_chdir(info) == FALSE)
		return (ERROR);
	return (0);
}

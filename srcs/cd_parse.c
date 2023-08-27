/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:06:50 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 02:20:21 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*next_remove(char *path, int save_index)
{
	char	*new_path;

	new_path = malloc(sizeof(char) * (save_index + 1));
	if (!new_path)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	ft_strlcpy(new_path, path, save_index + 1);
	free(path);
	return (new_path);
}

static char	*remove_slash(char *path, int i, int save_index)
{
	char	*new_path;

	while (path[i])
	{
		if (path[i] == '/')
			save_index = i;
		i++;
	}
	if (save_index == 0)
	{
		new_path = malloc(sizeof(char) * 2);
		if (!new_path)
		{
			print_error(MALLOC, NULL);
			return (NULL);
		}
		new_path[0] = '/';
		new_path[1] = '\0';
		free(path);
		return (new_path);
	}
	else
		return (next_remove(path, save_index));
	return (new_path);
}

static char	*add_path(char *path, char *add)
{
	char	*new_path;
	int		i;
	int		u;

	i = 0;
	u = 0;
	new_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(add) + 2));
	if (!new_path)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	while (path[u])
		new_path[i++] = path[u++];
	new_path[i++] = '/';
	u = 0;
	while (add[u])
		new_path[i++] = add[u++];
	new_path[i] = '\0';
	free(path);
	return (new_path);
}

char	*relative_path(char **split_path, const char *current_path)
{
	char	*ret_path;
	int		i;

	i = 0;
	ret_path = malloc(sizeof(char) * (ft_strlen(current_path) + 1));
	if (!ret_path)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	ft_strlcpy(ret_path, current_path, ft_strlen(current_path) + 1);
	while (split_path[i])
	{
		if (ft_strncmp(split_path[i], "..", 3) == 0)
			ret_path = remove_slash(ret_path, 0, 0);
		else if (ft_strncmp(split_path[i], ".", 2) == 0)
			break ;
		else
			ret_path = add_path(ret_path, split_path[i]);
		if (!ret_path)
			return (NULL);
		i++;
	}
	return (ret_path);
}

char	*absolute_path(t_arg_info *arg)
{
	char	*ret_path;

	ret_path = malloc(sizeof(char) * (ft_strlen(arg->cmd[1]) + 1));
	if (!ret_path)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	ft_strlcpy(ret_path, arg->cmd[1], ft_strlen(arg->cmd[1]) + 1);
	return (ret_path);
}

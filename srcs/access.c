/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:48:25 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 01:27:55 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strjoin_add_slash(const char *str1, const char *str2)
{
	int		i;
	int		u;
	char	*ret;

	i = 0;
	u = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!ret)
		return (NULL);
	while (str1[i])
		ret[u++] = str1[i++];
	ret[u++] = '/';
	i = 0;
	while (str2[i])
		ret[u++] = str2[i++];
	ret[u] = '\0';
	return (ret);
}

static int	find_cmd_in_path(t_arg_info *list, char **split_path, int ind)
{
	int		i;

	i = 0;
	if (access(list->cmd[ind], X_OK) == 0)
		return (0);
	if (!split_path)
		return (ERROR);
	else
	{
		while (split_path[i])
		{
			list->newcmd = my_strjoin_add_slash(split_path[i], list->cmd[ind]);
			if (!list->newcmd)
				return (print_error(MALLOC, NULL));
			if (access(list->newcmd, X_OK) == 0)
			{
				list->cmd[ind] = list->newcmd;
				return (0);
			}
			i++;
			free(list->newcmd);
			list->newcmd = NULL;
		}
	}
	return (0);
}

t_env	*get_path_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->str)
			if (ft_strncmp(tmp->str, "PATH=", 5) == 0)
				break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int	start_access(t_arg_info *tmp, char **split_path)
{
	int	i;

	i = 0;
	if (tmp->execute == FALSE)
		return (0);
	while (tmp->cmd[i] && i < tmp->size && tmp->tab_null[i] == TRUE)
		i++;
	if (!tmp->cmd[i])
		return (0);
	if (check_built_in(tmp->cmd[i]) == FALSE)
		if (find_cmd_in_path(tmp, split_path, i) == ERROR)
			return (ERROR);
	return (0);
}

int	check_access(t_info *info)
{
	t_env		*path;
	t_arg_info	*tmp;
	char		**split_path;
	int			i;

	split_path = NULL;
	path = get_path_env(info->list_env.envp);
	if (path)
		split_path = ft_split(&path->str[5], ':');
	tmp = info->list_arg;
	while (tmp)
	{
		i = 0;
		if (start_access(tmp, split_path) == ERROR)
			break ;
		tmp = tmp->next;
	}
	tab_free(&split_path);
	return (0);
}

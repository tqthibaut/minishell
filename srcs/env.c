/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:42:44 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 13:13:05 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tab_env(t_info *info)
{
	int		count;
	int		i;
	t_env	*tmp;

	count = 0;
	i = 0;
	tmp = info->list_env.envp;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	info->list_env.tab_env = malloc(sizeof(char *) * (count + 1));
	if (!info->list_env.tab_env)
		return (print_error(MALLOC, NULL));
	tmp = info->list_env.envp;
	while (tmp)
	{
		info->list_env.tab_env[i++] = tmp->str;
		tmp = tmp->next;
	}
	info->list_env.tab_env[i] = NULL;
	return (0);
}

t_env	*init_env(char **envp, int type)
{
	t_env	*ret;
	t_env	*new;
	int		i;

	i = 1;
	if (!envp[0])
		return (init_null(type));
	ret = create_list_env(envp[0], type);
	if (!ret)
		return (NULL);
	while (envp[i])
	{
		new = create_list_env(envp[i++], type);
		if (!new)
			return (NULL);
		ft_lstadd_back(&ret, new);
	}
	change_sh_level(ret, type);
	return (ret);
}

t_env	*find_env(t_env *env, char *str, int type)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	if (type == EXPORT)
		i = 11;
	else
		i = 0;
	while (tmp)
	{
		if (tmp->str)
		{
			if (ft_strncmp(&tmp->str[i], str, ft_strlen(str)) == 0)
			{
				if (tmp->str[i + ft_strlen(str)] == '\0'
					|| tmp->str[i + ft_strlen(str)] == '=')
					return (tmp);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	built_in_env(t_info *info)
{
	if (info->current_list_arg->childpid == 0)
	{
		if (info->current_list_arg->cmd[1])
		{
			write(2, "env: too many arguments\n", 24);
			free_info(info);
			exit(127);
		}
		print_list(info->list_env.envp);
		free_info(info);
		exit(0);
	}
	if (info->current_list_arg->cmd[1])
	{
		write(2, "env: too many arguments\n", 24);
		g_exit_status = 125;
		return (FALSE);
	}
	print_list(info->list_env.envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:45:34 by jgao              #+#    #+#             */
/*   Updated: 2022/04/07 14:12:06 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_dup(t_env *tmp, char *str, int TYPE)
{
	int	len;
	int	exp;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	exp = 0;
	if (TYPE == EXPORT)
		exp = 11;
	while (tmp)
	{
		if (ft_strncmp(str, &tmp->str[exp], len) == 0)
			if (tmp->str[exp + len] == '\0' || tmp->str[exp + len] == '=')
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	add_export(t_info *info, char *str)
{
	t_env	*tmp;

	tmp = find_dup(info->list_env.exp, str, EXPORT);
	if (!tmp)
	{
		tmp = info->list_env.exp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_list_env(str, EXPORT);
		if (!tmp->next)
		{
			write(2, "Error malloc in export\n", 23);
			return (ERROR);
		}
	}
	else
	{
		free(tmp->str);
		tmp->str = ft_strjoin("declare -x ", str);
		if (!tmp->str)
			return (ERROR);
		if (add_quote(tmp) == ERROR)
			return (ERROR);
	}
	return (0);
}

int	add_env(t_info *info, char *str)
{
	t_env	*tmp;

	tmp = find_dup(info->list_env.envp, str, ENV);
	if (!tmp)
	{
		tmp = info->list_env.envp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_list_env(str, ENV);
		if (!tmp->next)
		{
			write(2, "Error malloc in export\n", 23);
			return (ERROR);
		}
	}
	else
	{
		free(tmp->str);
		tmp->str = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!tmp->str)
			return (ERROR);
		ft_strlcpy(tmp->str, str, ft_strlen(str) + 1);
	}
	return (0);
}

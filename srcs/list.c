/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:02:52 by jgao              #+#    #+#             */
/*   Updated: 2022/03/10 14:48:08 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_quote(t_env *ret)
{
	int		i;
	int		u;
	char	*tmp;

	i = 0;
	u = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(ret->str) + 3));
	if (!tmp)
		return (ERROR);
	while (ret->str[i] != '=' && ret->str[i])
		tmp[u++] = ret->str[i++];
	if (ret->str[i] == '=')
	{
		tmp[u++] = ret->str[i++];
		tmp[u++] = '\"';
		while (ret->str[i])
			tmp[u++] = ret->str[i++];
		tmp[u++] = '\"';
	}
	tmp[u] = '\0';
	free(ret->str);
	ret->str = tmp;
	return (0);
}

t_env	*create_list_env(char *str, int type)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->next = NULL;
	if (type == ENV)
	{
		ret->str = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!ret->str)
			return (NULL);
		ft_strlcpy(ret->str, str, ft_strlen(str) + 1);
	}
	else if (type == EXPORT)
	{
		ret->str = ft_strjoin("declare -x ", str);
		if (!ret->str)
			return (NULL);
		if (add_quote(ret) == ERROR)
			return (NULL);
	}
	return (ret);
}

void	print_list(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

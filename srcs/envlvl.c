/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:46:24 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 22:56:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_sh_level(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == 'S')
				if (ft_strncmp(&tmp->str[i], "SHLVL=", 6) == 0)
					return (tmp);
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int	write_export(t_env *tmp, char *nbr, int i, int u)
{
	tmp->str = malloc(sizeof(char) * (20 + ft_strlen(nbr)));
	ft_strlcpy(tmp->str, "declare -x SHLVL=\"", 19);
	while (tmp->str[i])
		i++;
	while (nbr[u])
		tmp->str[i++] = nbr[u++];
	tmp->str[i] = '\"';
	tmp->str[i + 1] = '\0';
	return (0);
}

static int	rewrite_str(t_env *tmp, int type, int nb)
{
	char	*nbr;

	nbr = ft_itoa(nb);
	if (tmp->str)
	{
		free(tmp->str);
		tmp->str = NULL;
	}
	if (type == ENV)
		tmp->str = ft_strjoin("SHLVL=", nbr);
	else if (type == EXPORT)
		if (write_export(tmp, nbr, 0, 0) == ERROR)
			return (ERROR);
	free(nbr);
	return (0);
}

int	change_sh_level(t_env *env, int type)
{
	int		i;
	int		nb;
	t_env	*tmp;

	i = 0;
	tmp = find_sh_level(env);
	if (!tmp)
		return (ERROR);
	while ((tmp->str[i] < '0' || tmp->str[i] > '9') && tmp->str[i])
		i++;
	if (!tmp->str[i])
		return (ERROR);
	nb = ft_atoi(&tmp->str[i]);
	if (rewrite_str(tmp, type, nb + 1) == ERROR)
		return (ERROR);
	if (!tmp->str)
		return (ERROR);
	return (0);
}

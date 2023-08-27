/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_null2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:04:15 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:13:21 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	null_export_next(char *string, int type, t_env *exp)
{
	if (type == SHLVL)
	{
		exp->str = malloc(sizeof(char) * (ft_strlen(string) + 4));
		if (!exp->str)
			return (-1);
		ft_strlcpy(exp->str, string, ft_strlen(string) + 1);
		add_string(exp->str, "\"");
		add_string(exp->str, "1");
	}
	else if (type == OLDPWD)
	{
		exp->str = malloc(sizeof(char) * (ft_strlen(string) + 1));
		if (!exp->str)
			return (-1);
		ft_strlcpy(exp->str, string, ft_strlen(string) + 1);
	}
	return (0);
}

t_env	*null_export(char *string, int type)
{
	t_env	*exp;
	char	str[2042];

	exp = malloc(sizeof(t_env));
	if (!exp)
		return (NULL);
	exp->next = NULL;
	if (type == PWD)
	{
		getcwd(str, 2042);
		exp->str = malloc(sizeof(char)
				* (ft_strlen(str) + ft_strlen(string) + 3));
		if (!exp->str)
			return (NULL);
		ft_strlcpy(exp->str, string, ft_strlen(string) + 1);
		add_string(exp->str, "\"");
		add_string(exp->str, str);
	}
	else
		if (null_export_next(string, type, exp) == -1)
			return (NULL);
	if (type != OLDPWD)
		add_string(exp->str, "\"");
	return (exp);
}

static int	sh_lvl(t_env *env, char *string)
{
	env->str = malloc(sizeof(char) * (ft_strlen(string) + 2));
	if (!env->str)
	{
		free(env);
		return (ERROR);
	}
	ft_strlcpy(env->str, string, ft_strlen(string) + 1);
	add_string(env->str, "1");
	return (0);
}

t_env	*null_env(char *string, int type)
{
	t_env	*env;
	char	str[2042];

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->next = NULL;
	if (type == PWD)
	{
		getcwd(str, 2042);
		env->str = malloc(sizeof(char) * (ft_strlen(str)
					+ ft_strlen(string) + 1));
		if (!env->str)
		{
			free(env);
			return (NULL);
		}
		ft_strlcpy(env->str, string, ft_strlen(string) + 1);
		add_string(env->str, str);
	}
	else if (type == SHLVL)
		if (sh_lvl(env, string) == ERROR)
			return (NULL);
	return (env);
}

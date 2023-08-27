/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:15 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:16:37 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_export_null(void)
{
	t_env	*ret;

	ret = null_export("declare -x PWD=", PWD);
	if (!ret)
	{
		free_env(ret);
		return (NULL);
	}
	ret->next = null_export("declare -x SHLVL=", SHLVL);
	if (!ret->next)
	{
		free_env(ret);
		return (NULL);
	}
	ret->next->next = null_export("declare -x OLDPWD", OLDPWD);
	if (!ret->next->next)
	{
		free_env(ret);
		return (NULL);
	}
	return (ret);
}

static t_env	*init_env_null(void)
{
	t_env	*ret;

	ret = null_env("PWD=", PWD);
	if (!ret)
	{
		free_env(ret);
		return (NULL);
	}
	ret->next = null_env("SHLVL=", SHLVL);
	if (!ret->next)
	{
		free_env(ret);
		return (NULL);
	}
	return (ret);
}

t_env	*init_null(int type)
{
	t_env	*ret;

	if (type == EXPORT)
	{
		ret = init_export_null();
		if (!ret)
			return (NULL);
	}
	else
	{
		ret = init_env_null();
		if (!ret)
			return (NULL);
	}
	return (ret);
}

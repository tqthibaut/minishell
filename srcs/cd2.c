/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:16:03 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 13:18:11 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd(t_env *tmp_oldpwd, int type, t_env *tmp_pwd, char *path)
{
	if (tmp_oldpwd)
	{
		if (type == ENV)
			tmp_oldpwd->str = ft_strjoin("OLDPWD=", &tmp_pwd->str[4]);
		else
			tmp_oldpwd->str = ft_strjoin("declare -x OLDPWD=",
					&tmp_pwd->str[15]);
	}
	free(tmp_pwd->str);
	if (type == ENV)
		tmp_pwd->str = ft_strjoin("PWD=", path);
	else
		tmp_pwd->str = ft_strjoin("declare -x PWD=", path);
}

int	change_env(t_env *envp, char *path, int type, t_env *tmp_pwd)
{
	t_env	*tmp_oldpwd;

	tmp_oldpwd = find_env(envp, "OLDPWD", type);
	if (tmp_oldpwd)
	{
		free(tmp_oldpwd->str);
		tmp_oldpwd->str = NULL;
	}
	tmp_pwd = find_env(envp, "PWD", type);
	if (tmp_pwd)
		change_pwd(tmp_oldpwd, type, tmp_pwd, path);
	if (type == EXPORT && tmp_pwd)
		add_quote(tmp_pwd);
	return (0);
}

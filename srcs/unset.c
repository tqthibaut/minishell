/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:52:55 by jgao              #+#    #+#             */
/*   Updated: 2022/04/06 17:43:19 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	quick_cmp_for_env(char *str1, char *str2, int type)
{
	int	i;
	int	u;

	if (type == EXPORT)
		i = 11;
	else
		i = 0;
	u = 0;
	while (str2[u] && str1[i])
	{
		if (str1[i++] != str2[u++])
			return (FALSE);
	}
	if ((str1[i] != '\0' && str1[i] != '=') || str2[u])
		return (FALSE);
	return (TRUE);
}

static void	free_env_list(t_env *env)
{
	if (env)
	{
		if (env->str)
			free(env->str);
		free(env);
	}
}

static void	find_for_env(char *str, t_env *envp, t_info *info)
{
	t_env	*prev;

	prev = envp;
	while (envp)
	{
		if (quick_cmp_for_env(envp->str, str, ENV) == TRUE)
		{
			if (envp == info->list_env.envp)
			{
				info->list_env.envp = info->list_env.envp->next;
				free_env_list(envp);
			}
			else
			{
				while (prev->next != envp && prev->next)
					prev = prev->next;
				prev->next = envp->next;
				free_env_list(envp);
			}
			break ;
		}
		envp = envp->next;
	}
}

void	find_and_unset(char *str, t_env *exp, t_info *info)
{
	t_env	*prev;

	prev = exp;
	while (exp)
	{
		if (quick_cmp_for_env(exp->str, str, EXPORT) == TRUE)
		{
			if (exp == info->list_env.exp)
			{
				info->list_env.exp = info->list_env.exp->next;
				free_env_list(exp);
			}
			else
			{
				while (prev->next != exp && prev->next)
					prev = prev->next;
				prev->next = exp->next;
				free_env_list(exp);
			}
			find_for_env(str, info->list_env.envp, info);
			break ;
		}
		exp = exp->next;
	}
}

int	built_in_unset(t_info *info)
{
	int	i;

	i = 1;
	if (info->current_list_arg->childpid == 0)
		child_unset(info);
	if (!info->current_list_arg->cmd[1])
		return (0);
	if (check_unset_flag(info) == TRUE)
		return (ERROR);
	while (info->current_list_arg->cmd[i])
	{
		find_and_unset(info->current_list_arg->cmd[i],
			info->list_env.exp, info);
		i++;
	}
	g_exit_status = 0;
	return (0);
}

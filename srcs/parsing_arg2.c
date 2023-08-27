/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:16:39 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 00:22:21 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quick_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_arg	*free_null_arg_list(t_info *info, t_arg *arg)
{
	t_arg	*tmp;

	tmp = info->arg;
	if (tmp == arg)
	{
		info->arg = tmp->next;
		free(arg->str);
		free(arg);
		return (info->arg);
	}
	while (tmp && tmp->next != arg)
		tmp = tmp->next;
	tmp->next = arg->next;
	free(arg->str);
	free(arg);
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:31:52 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 00:22:04 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_list(t_info *info, int *i)
{
	t_arg	*new;
	t_arg	*tmp;
	int		u;

	u = 0;
	new = new_arg(info->buffer, i);
	if (!new)
		return (print_error(MALLOC, NULL));
	if (info->arg)
	{
		tmp = info->arg;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		info->arg = new;
	return (0);
}

static void	replace_value_by_quote(t_arg *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == -1)
			tmp->str[i] = '\'';
		if (tmp->str[i] == -2)
			tmp->str[i] = '\"';
		i++;
	}
}

static int	do_remove_quote(t_arg *tmp)
{
	if (quick_check_quote(tmp->str) == TRUE)
	{
		tmp->quote = TRUE;
		tmp->str = remove_quotes(tmp->str);
		if (!tmp->str)
			return (print_error(MALLOC, NULL));
	}
	return (0);
}

int	exp_and_quote(t_info *info)
{
	t_arg	*tmp;

	tmp = info->arg;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "<<", 3) == 0)
			tmp = tmp->next;
		else
		{
			tmp->str = replace_expansion(info, tmp->str);
			if (!tmp->str)
				return (print_error(MALLOC, NULL));
			if (tmp->str[0] == '\0')
			{
				tmp->null = TRUE;
				tmp = tmp->next;
				continue ;
			}
			if (do_remove_quote(tmp) == ERROR)
				return (ERROR);
			replace_value_by_quote(tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_arg(t_info *info)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	while (info->buffer[i])
	{
		while (info->buffer[i] == ' ')
			i++;
		if (info->buffer[i])
		{
			if (fill_list(info, &i) == ERROR)
			{
				free_arg(&info->arg);
				info->arg = NULL;
				return (ERROR);
			}
		}
	}
	tmp = info->arg;
	if (exp_and_quote(info) == ERROR)
		return (ERROR);
	return (0);
}

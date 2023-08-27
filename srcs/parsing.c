/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:42:43 by jgao              #+#    #+#             */
/*   Updated: 2022/04/07 15:31:52 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

t_arg	*new_arg(char *buffer, int *i)
{
	t_arg	*new;
	int		length;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->null = FALSE;
	length = get_arg_length(buffer, *i);
	new->str = malloc(sizeof(char) * (length + 1));
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	ft_strlcpy(new->str, &buffer[*i], length + 1);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->quote = FALSE;
	new->next = NULL;
	*i += length;
	return (new);
}

int	split_arg(t_info *info)
{
	info->arg = NULL;
	if (!info->buffer)
		return (0);
	if (get_arg(info) == ERROR)
	{
		return (ERROR);
	}
	return (0);
}

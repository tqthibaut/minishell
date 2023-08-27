/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:24:39 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:32:45 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	static_magic(t_info *mem)
{
	static t_info	*ptr = NULL;

	if (mem != NULL)
		ptr = mem;
	else
		free_info(ptr);
}

void	close_and_unlink(t_info *info)
{
	t_arg_info	*tmp;

	tmp = info->list_arg;
	while (tmp)
	{
		if (tmp->is_in == TRUE || tmp->is_in == HEREDOC)
			close(tmp->infilefd);
		if (tmp->is_out == TRUE)
			close(tmp->outfilefd);
		if (tmp->infile_name)
			unlink(tmp->infile_name);
		tmp = tmp->next;
	}
}

int	heredoc_create_file(t_arg_info *list, int index)
{
	char	*number_str;

	number_str = ft_itoa(index);
	if (index < 10)
		list->infile_name = ft_strjoin(".heredoc_0", number_str);
	else
		list->infile_name = ft_strjoin(".heredoc_", number_str);
	if (!list->infile_name)
		return (ERROR);
	free(number_str);
	return (0);
}

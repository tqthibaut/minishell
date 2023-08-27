/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:24:10 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 21:54:29 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_length(char *buffer, int i)
{
	int	count;
	int	singleq;
	int	doubleq;

	count = 0;
	singleq = FALSE;
	doubleq = FALSE;
	while (buffer[i])
	{
		check_current_quote(buffer[i], &singleq, &doubleq);
		if (singleq == FALSE && doubleq == FALSE && buffer[i] == ' ')
			break ;
		i++;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:49:41 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 13:54:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	printf_width_next(t_tab *tab, int len, int arg, int write_len)
{
	if (arg == ARGSTR)
	{
		while (tab->widthnb-- - len > 0)
		{
			write(1, &tab->attr.widthchar, 1);
			write_len++;
		}
	}
	return (write_len);
}

int	print_width(t_tab *tab, int len, int arg)
{
	int	write_len;

	write_len = 0;
	if (arg == ARGINT)
	{
		if (tab->precinb > len)
		{
			while (tab->widthnb-- - tab->precinb > 0)
			{
				write_len++;
				write(1, &tab->attr.widthchar, 1);
			}
		}
		else
		{
			while (tab->widthnb-- - len > 0)
			{
				write(1, &tab->attr.widthchar, 1);
				write_len++;
			}
		}
	}
	return (printf_width_next(tab, len, arg, write_len));
}

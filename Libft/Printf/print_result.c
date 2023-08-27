/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:45:27 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 13:57:12 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	print_argint_null(t_tab *tab, int len)
{
	int	write_len;
	int	precinbtmp;

	write_len = 0;
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF)
		write_len += print_width(tab, 0, ARGINT);
	precinbtmp = tab->precinb;
	while (precinbtmp-- >= len)
	{
		write(1, "0", 1);
		write_len++;
	}
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON)
		write_len += print_width(tab, 0, ARGINT);
	return (write_len);
}

static int	print_argint_next(t_tab *tab, char *str, int len, int sign)
{
	int		precitmp;
	int		write_len;

	precitmp = tab->precinb;
	while (precitmp-- > len)
		write(1, "0", 1);
	write_len = tab->precinb - (precitmp + 1) + len;
	write(1, str + sign, len - sign);
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON)
		write_len += print_width(tab, len, ARGINT);
	return (write_len);
}

int	print_argint(t_tab *tab, char *str, int len)
{
	int	sign;
	int	write_len;

	sign = 0;
	write_len = 0;
	if (str[0] == '0' && tab->precision == TRUE)
		return (print_argint_null(tab, len));
	if (str[0] == '-')
	{
		sign = 1;
		tab->precinb++;
	}
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF
		&& tab->attr.flag[1][1] == ATTRZERO_OFF)
		write_len += print_width(tab, len, ARGINT);
	if (sign == 1)
		write(1, "-", 1);
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF
		&& tab->attr.flag[1][1] == ATTRZERO_ON)
		write_len += print_width(tab, len, ARGINT);
	return (write_len + print_argint_next(tab, str, len, sign));
}

int	print_argstr(t_tab *tab, char *str, int len)
{
	int	write_len;

	write_len = 0;
	if (tab->precision == TRUE && tab->precinb < len)
	{
		if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF)
			write_len += print_width(tab, tab->precinb, ARGSTR);
		write(1, str, tab->precinb);
		write_len += tab->precinb;
		if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON)
			write_len += print_width(tab, tab->precinb, ARGSTR);
		return (write_len);
	}
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF)
		write_len += print_width(tab, len, ARGSTR);
	write(1, str, len);
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON)
		write_len += print_width(tab, len, ARGSTR);
	return (write_len + len);
}

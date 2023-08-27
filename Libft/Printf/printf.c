/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:08:46 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:04:16 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

static int	check_flag(const char *str, t_tab *tab)
{
	tab->width = FALSE;
	tab->precision = FALSE;
	tab->widthnb = 0;
	tab->precinb = 0;
	if (str[tab->i] == '*' || (str[tab->i] >= '1' && str[tab->i] <= '9'))
		ft_width(str, tab);
	if (str[tab->i] == '.')
		ft_precision(str, tab);
	return (0);
}

static int	func_conversion(const char c, t_tab *tab)
{
	int	write_len;

	tab->flagind = 0;
	while (tab->flag[tab->flagind] != '\0')
	{
		if (tab->flag[tab->flagind] == c)
		{
			write_len = tab->func[tab->flagind][0](tab);
			if (write_len == -1)
				return (-1);
			return (write_len);
		}
		tab->flagind++;
	}
	return (0);
}

void	check_attr(const char *str, t_tab *tab)
{
	int	i;

	i = 0;
	tab->attr.widthchar = ' ';
	while (tab->attr.flag[i][0])
		tab->attr.flag[i++][1] = '0';
	i = 0;
	while (tab->attr.flag[i][0])
	{
		if (str[tab->i] == tab->attr.flag[i][0])
		{
			tab->attr.flag[i][1] = '1';
			tab->i++;
			i = -1;
		}
		i++;
	}
	check_flag(str, tab);
}

int	ft_printf(const char *str, ...)
{
	t_tab	tab;
	int		ret;

	tab.i = 0;
	tab.ret = 0;
	fill_all_tab(&tab);
	va_start(tab.arg, str);
	while (str[tab.i])
	{
		if (str[tab.i] == '%')
		{
			tab.i++;
			check_attr(str, &tab);
			ret = func_conversion(str[tab.i], &tab);
			if (ret == -1)
				return (-1);
			tab.ret += ret - 1;
		}
		else
			write(1, &str[tab.i], 1);
		tab.i++;
		tab.ret++;
	}
	va_end(tab.arg);
	return (tab.ret);
}

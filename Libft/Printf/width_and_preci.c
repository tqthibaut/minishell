/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_preci.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:17:56 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 13:54:16 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_precision(const char *str, t_tab *tab)
{
	tab->precision = TRUE;
	tab->precinb = 0;
	tab->i++;
	if (str[tab->i] == '*')
	{
		tab->precinb = va_arg(tab->arg, int);
		if (tab->precinb < 0)
			tab->precision = FALSE;
		tab->i++;
	}
	else
	{
		while (str[tab->i] == '0')
			tab->i++;
		while (str[tab->i] >= '0' && str[tab->i] <= '9')
			tab->precinb = (tab->precinb * 10) + (str[tab->i++] - '0');
	}
	if (tab->precision == TRUE)
	{
		tab->attr.flag[1][1] = ATTRZERO_OFF;
		tab->attr.widthchar = ' ';
	}
}

void	ft_width(const char *str, t_tab *tab)
{
	if (str[tab->i] == '*')
	{
		tab->widthnb = va_arg(tab->arg, int);
		if (tab->widthnb < 0)
		{
			tab->widthnb *= -1;
			tab->attr.flag[0][1] = ATTRMINUS_ON;
		}
		tab->i++;
		tab->width = TRUE;
	}
	else if (str[tab->i] >= '1' && str[tab->i] <= '9')
	{
		while (str[tab->i] >= '0' && str[tab->i] <= '9')
			tab->widthnb = (tab->widthnb * 10) + (str[tab->i++] - '0');
		tab->width = TRUE;
	}
	if (tab->attr.flag[0][1] == ATTRMINUS_OFF
		&& tab->attr.flag[1][1] == ATTRZERO_ON)
		tab->attr.widthchar = '0';
}

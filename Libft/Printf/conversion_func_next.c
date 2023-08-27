/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_func_next.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:15:07 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:15:50 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_putnbr_memory_next(t_tab *tab, char *str, int len, int write_len)
{
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF
		&& tab->attr.flag[1][1] == ATTRZERO_OFF)
		write_len += print_width(tab, len + 2, ARGSTR);
	write(1, "0x", 2);
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF
		&& tab->attr.flag[1][1] == ATTRZERO_ON)
		write_len += print_width(tab, len + 2, ARGSTR);
	write(1, str, len);
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON
		&& tab->attr.flag[1][1] == ATTRZERO_OFF)
		write_len += print_width(tab, len + 2, ARGSTR);
	return (write_len);
}

int	ft_putnbr_memory(t_tab *tab)
{
	char	*str;
	int		len;
	int		write_len;

	str = ft_itoa_base(tab->ptr, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write_len = 2 + len + ft_putnbr_memory_next(tab, str, len, 0);
	free(str);
	return (write_len);
}

int	my_putstr(t_tab *tab)
{
	int	len;

	if (tab->charstr == NULL)
		tab->charstr = "(null)";
	len = ft_strlen(tab->charstr);
	return (print_argstr(tab, tab->charstr, len));
}

int	my_putnbr(t_tab *tab)
{
	char	*str;
	int		len;
	int		ret;

	str = ft_itoa_base(tab->intnb, 10);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	ret = print_argint(tab, str, len);
	free(str);
	return (ret);
}

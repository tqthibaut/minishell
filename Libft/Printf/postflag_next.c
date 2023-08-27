/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postflag_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:16:45 by jgao              #+#    #+#             */
/*   Updated: 2020/12/08 11:13:04 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	argchar(t_tab *tab)
{
	int	write_len;

	write_len = 0;
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_OFF)
		write_len += print_width(tab, 1, ARGSTR);
	ft_putchar((char)va_arg(tab->arg, int));
	if (tab->width == TRUE && tab->attr.flag[0][1] == ATTRMINUS_ON)
		write_len += print_width(tab, 1, ARGSTR);
	return (write_len + 1);
}

int	argmod(t_tab *tab)
{
	return (print_argstr(tab, "%", 1));
}

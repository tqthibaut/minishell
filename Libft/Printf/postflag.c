/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postflag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:07:56 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:09:23 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

int	argint(t_tab *tab)
{
	int	ret;

	tab->intnb = va_arg(tab->arg, int);
	ret = tab->func[tab->flagind][1](tab);
	if (ret == -1)
		return (-1);
	return (ret);
}

int	arguint(t_tab *tab)
{
	int	ret;

	tab->uintnb = va_arg(tab->arg, unsigned int);
	ret = tab->func[tab->flagind][1](tab);
	if (ret == -1)
		return (-1);
	return (ret);
}

int	arguintptr(t_tab *tab)
{
	int	ret;

	tab->ptr = va_arg(tab->arg, uintptr_t);
	ret = tab->func[tab->flagind][1](tab);
	if (ret == -1)
		return (-1);
	return (ret);
}

int	argcharp(t_tab *tab)
{
	int	ret;

	tab->charstr = va_arg(tab->arg, char *);
	ret = tab->func[tab->flagind][1](tab);
	if (ret == -1)
		return (-1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:19:29 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:38:19 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <unistd.h>

void	ft_putnbr(int nb)
{
	if (nb == INT_MIN)
	{
		write(1, "-", 1);
		ft_putnbr(nb / -10);
	}
	if (nb < 0 && nb != INT_MIN)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb / 10 != 0 && nb != INT_MIN)
		ft_putnbr(nb / 10);
	if (nb == INT_MIN)
		ft_putchar((nb % 10 * -1) + '0');
	else
		ft_putchar(nb % 10 + '0');
}

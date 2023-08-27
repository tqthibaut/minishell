/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:02:26 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:38:04 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == INT_MIN)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(nb / -10, fd);
	}
	if (nb < 0 && nb != INT_MIN)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb / 10 != 0 && nb != INT_MIN)
		ft_putnbr_fd(nb / 10, fd);
	if (nb == INT_MIN)
		ft_putchar((nb % 10 * -1) + '0', fd);
	else
		ft_putchar(nb % 10 + '0', fd);
}

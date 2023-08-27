/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillflag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:12:57 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:13:07 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	fill_func(int (*func[32][32])())
{
	func[0][0] = &argint;
	func[0][1] = &my_putnbr;
	func[1][0] = &argint;
	func[1][1] = &my_putnbr;
	func[2][0] = &arguint;
	func[2][1] = &ft_putnbr_octal;
	func[3][0] = &arguint;
	func[3][1] = &ft_putnbr_unsigned;
	func[4][0] = &arguint;
	func[4][1] = &ft_putnbr_hexa;
	func[5][0] = &arguint;
	func[5][1] = &ft_putnbr_hexa_up;
	func[6][0] = &argchar;
	func[7][1] = &my_putstr;
	func[7][0] = &argcharp;
	func[8][0] = &arguintptr;
	func[8][1] = &ft_putnbr_memory;
	func[9][0] = &argmod;
}

static void	fill_flag(char ret[10])
{
	ret[0] = 'd';
	ret[1] = 'i';
	ret[2] = 'o';
	ret[3] = 'u';
	ret[4] = 'x';
	ret[5] = 'X';
	ret[6] = 'c';
	ret[7] = 's';
	ret[8] = 'p';
	ret[9] = '%';
	ret[10] = '\0';
}

static void	fill_attr(char attr[3][2])
{
	attr[0][0] = '-';
	attr[1][0] = '0';
	attr[2][0] = '\0';
}

void	fill_all_tab(t_tab *tab)
{
	fill_flag(tab->flag);
	fill_func(tab->func);
	fill_attr(tab->attr.flag);
}

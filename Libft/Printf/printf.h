/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:07:02 by jgao              #+#    #+#             */
/*   Updated: 2021/11/24 17:27:28 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

# define TRUE 1
# define FALSE 0
# define ARGINT 0
# define ARGSTR 1
# define ATTRZERO_ON '1'
# define ATTRZERO_OFF '0'
# define ATTRMINUS_ON '1'
# define ATTRMINUS_OFF '0'

typedef struct s_attr
{
	char	flag[3][2];
	char	widthchar;
}				t_attr;

typedef struct s_tab
{
	int				i;
	int				ret;
	int				flagind;
	int				precinb;
	int				precision;
	int				widthnb;
	int				width;
	va_list			arg;
	char			flag[10];
	int				(*func[32][32])();
	char			*print_value;
	int				intnb;
	unsigned int	uintnb;
	char			*charstr;
	char			chr;
	uintptr_t		ptr;
	struct s_attr	attr;
}				t_tab;

void			fill_all_tab(t_tab *tab);
void			ft_width(const char *str, t_tab *tab);
void			ft_precision(const char *str, t_tab *tab);
char			*ft_itoa_base(long n, int b);
int				ft_putchar(char c);
int				ft_strlen(char *s);
int				ft_putstr(char *s);
int				ft_putnbr(int nb);
int				printchar(char *s);
int				my_putstr(t_tab *tab);
int				my_putnbr(t_tab *tab);
int				ft_putnbr_octal(t_tab *tab);
int				ft_putnbr_unsigned(t_tab *tab);
int				ft_putnbr_hexa(t_tab *tab);
int				ft_putnbr_hexa_up(t_tab *tab);
int				ft_putnbr_memory(t_tab *tab);
int				argint(t_tab *tab);
int				argcharp(t_tab *tab);
int				argchar(t_tab *tab);
int				arguintptr(t_tab *tab);
int				argmod(t_tab *tab);
int				arguint(t_tab *tab);
int				print_width(t_tab *tab, int len, int arg);
int				print_argint(t_tab *tab, char *str, int len);
int				print_argstr(t_tab *tab, char *str, int len);
int				print_width(t_tab *tab, int len, int arg);

#endif

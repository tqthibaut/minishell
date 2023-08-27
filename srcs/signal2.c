/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:02:44 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:25:33 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_reset(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigaction(sig, &sa, NULL);
}

void	exit_signal(t_info *info)
{
	printf("exit\n");
	free_info(info);
	exit(0);
}

void	sig_int_fork(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
}

void	sig_set_fork(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = &sig_int_fork;
	sa.sa_flags = SA_RESTART;
	sigaction(sig, &sa, NULL);
}

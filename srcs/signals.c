/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:28:43 by tthibaut          #+#    #+#             */
/*   Updated: 2022/04/09 12:55:40 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_function(int i)
{
	(void)i;
	g_exit_status = 130;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_ignore(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigaction(sig, &sa, NULL);
}

void	sig_int_set(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = &sigint_function;
	sa.sa_flags = SA_RESTART;
	sigaction(sig, &sa, NULL);
}

void	sig_int_hdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	static_magic(NULL);
	exit(130);
}

void	sig_set_heredoc(int sig)
{
	struct sigaction	sa;

	if (sig == SIGQUIT)
	{
		ft_memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_RESTART;
		sigaction(sig, &sa, NULL);
	}
	if (sig == SIGINT)
	{
		ft_memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = &sig_int_hdoc;
		sa.sa_flags = SA_RESTART;
		sigaction(sig, &sa, NULL);
	}
}

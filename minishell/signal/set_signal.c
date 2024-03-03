/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:38 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/19 15:34:58 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_signals.h"

void	set_signal_process(void)
{
	extern int		rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_before_heredoc(void)
{
	extern int		rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, check_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_main(void)
{
	extern int			rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, do_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child(void)
{
	extern int			rl_catch_signals;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void)
{
	extern int			rl_catch_signals;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:03 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/19 11:50:47 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_signals.h"
#include "../_includes/moo_environ.h"

void	do_sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	update_exit_code(1);
}

void	check_signal(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (signo == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

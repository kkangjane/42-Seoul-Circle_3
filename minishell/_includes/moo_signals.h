/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moo_signals.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:31:02 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/19 11:54:50 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOO_SIGNALS_H
# define MOO_SIGNALS_H

# include "moo_basic.h"
# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <unistd.h>

/* signal_utils.c */
void	do_sigint_handler(int signo);
void	check_signal(int signo);

/* set_signal.c */
void	set_signal_process(void);
void	set_signal_main(void);
void	set_signal_child(void);
void	set_signal_heredoc(void);
void	set_signal_before_heredoc(void);

#endif
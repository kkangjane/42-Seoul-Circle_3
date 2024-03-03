/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:18:37 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_includes/moo_basic.h"

int	perror_msg(const char *msg)
{
	extern int	errno;

	ft_putstr_fd("moo: ", STDERR_FILENO);
	perror(msg);
	return (1);
}

int	print_error(char *f, char *wrong_s, char *msg, int exit_code)
{
	ft_putstr_fd("moo: ", STDERR_FILENO);
	if (f)
	{
		ft_putstr_fd(f, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (wrong_s)
	{
		ft_putstr_fd(wrong_s, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	return (exit_code);
}

void	error_exit(const char *string)
{
	extern int	errno;

	perror_msg(string);
	exit(errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:14:40 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/18 17:42:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	check_option(char *cmd, int *option);

int	ft_echo(t_cmd *proc)
{
	int	out_fd;
	int	option;
	int	i;

	out_fd = find_fd(proc, 1);
	i = 1;
	option = 0;
	while (check_option(proc->cmd[i], &option) == 0)
		i++;
	while (proc->cmd[i])
	{
		ft_putstr_fd(proc->cmd[i], out_fd);
		if (proc->cmd[i + 1] != 0)
			ft_putchar_fd(' ', out_fd);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', out_fd);
	return (close_out_fd(proc, 0));
}

static int	check_option(char *cmd, int *option)
{
	int	i;

	if (!cmd)
		return (1);
	i = 0;
	if (cmd[i++] != '-')
		return (1);
	if (cmd[i++] != 'n')
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			break ;
		i++;
	}
	if (cmd[i] == 'n' || cmd[i] == 0)
	{
		*option = 1;
		return (0);
	}
	return (1);
}

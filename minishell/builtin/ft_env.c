/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:38:50 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/17 16:13:58 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	is_there_value(char *line);

int	ft_env(t_cmd *proc)
{
	int	i;
	int	out_fd;

	out_fd = find_fd(proc, 1);
	if (proc->cmd[1] != 0)
	{
		write(2, "env: ", 5);
		write(2, proc->cmd[1], ft_strlen(proc->cmd[1]));
		write(2, ": No such file or directory\n", 28);
		return (close_out_fd(proc, 127));
	}
	i = -1;
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], "_=", 2) == 0)
			continue ;
		if (ft_strncmp(g_env[i], "?=", 2) == 0)
			continue ;
		if (is_there_value(g_env[i]) > 0)
			ft_putendl_fd(g_env[i], out_fd);
	}
	return (close_out_fd(proc, 0));
}

static int	is_there_value(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == 0)
		return (0);
	return (1);
}

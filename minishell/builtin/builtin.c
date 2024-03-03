/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:02:39 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/17 16:12:35 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	builtin(t_cmd *proc)
{
	char	*cmd;

	cmd = proc->cmd[0];
	if (cmd && ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(proc));
	else if (cmd && ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(proc));
	else if (cmd && ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(proc));
	else if (cmd && ft_strcmp(cmd, "export") == 0)
		return (ft_export(proc));
	else if (cmd && ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(proc));
	else if (cmd && ft_strcmp(cmd, "env") == 0)
		return (ft_env(proc));
	else if (cmd && ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(proc));
	else
		return (1);
}

int	is_builtin(t_cmd *proc)
{
	char	*cmd;

	if (proc->cmd == 0 || proc->cmd[0] == 0)
		return (0);
	cmd = proc->cmd[0];
	if (cmd && ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (cmd && ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

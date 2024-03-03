/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:13:03 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:25:49 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	do_execve(t_cmd *cmd, char *cmd_file)
{
	extern int	rl_catch_signals;
	char		**fake_env;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		set_signal_child();
		if (files_open_test(cmd->files, cmd))
			return (fileopen_err(1));
		if (cmd_file == 0)
			return (cmdfile_error(cmd));
		if (access(cmd_file, X_OK) == -1)
			error_exit(cmd_file);
		if (pipe_to_fd(cmd) == -1 || file_to_fd(cmd) == -1)
		{
			ft_putendl_fd("dup2 error", 2);
			exit(1);
		}
		fake_env = make_fake_environ();
		execve(cmd_file, cmd->cmd, fake_env);
	}
	close_out_fd(cmd, 0);
	return (0);
}

int	do_builtin(t_cmd *cmd)
{
	int	code;

	if (files_open_test(cmd->files, cmd))
		return (fileopen_err(0));
	code = builtin(cmd);
	update_exit_code(code);
	return (0);
}

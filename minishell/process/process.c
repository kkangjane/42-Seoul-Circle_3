/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:25:01 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/19 15:11:44 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

void	process(t_cmd *cmd)
{
	t_cmd		*start;
	char		*cmd_file;

	start = cmd;
	set_signal_before_heredoc();
	if (check_heredoc(start))
		return ;
	set_signal_process();
	make_pipe(start);
	while (cmd)
	{
		cmd_file = find_command(&cmd->cmd[0]);
		if (is_builtin(cmd))
			do_builtin(cmd);
		else
			do_execve(cmd, cmd_file);
		if (cmd_file)
			free(cmd_file);
		cmd = cmd->next;
	}
	finish_cmdline(start);
}

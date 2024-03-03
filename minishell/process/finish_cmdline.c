/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:40:04 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/22 15:02:43 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static void	all_close(t_cmd *cmd);
static void	all_wait(t_cmd *cmd);
static void	close_builtin(t_cmd *cmd);
static void	close_execve(t_cmd *cmd);

void	finish_cmdline(t_cmd *cmd)
{
	all_close(cmd);
	all_wait(cmd);
}

static void	all_close(t_cmd *cmd)
{
	if (cmd->next == 0)
		return ;
	while (cmd)
	{
		if (is_builtin(cmd))
			close_builtin(cmd);
		else if (cmd->pid)
			close_execve(cmd);
		cmd = cmd->next;
	}
}

static void	all_wait(t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid)
		{
			waitpid(cmd->pid, &status, WUNTRACED);
			if (cmd->cmd && is_builtin(cmd) == 0 && cmd->next == 0)
			{
				if (WIFEXITED(status))
					update_exit_code(WEXITSTATUS(status));
				else if (WIFSIGNALED(status))
				{
					if (WTERMSIG(status) == 2)
						ft_putendl_fd("", 2);
					else if (WTERMSIG(status) == 3)
						ft_putendl_fd("Quit: 3", 2);
					if (WTERMSIG(status) == 2 || WTERMSIG(status) == 3)
						update_exit_code(128 + WTERMSIG(status));
				}
			}
		}
		cmd = cmd->next;
	}
}

static void	close_builtin(t_cmd *cmd)
{
	if (cmd->infile_fd > -2 && cmd->infile_fd != STDIN_FILENO)
		close(cmd->infile_fd);
	else if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	if (cmd->outfile_fd > -2 && cmd->outfile_fd != STDOUT_FILENO)
		close(cmd->outfile_fd);
}

static void	close_execve(t_cmd *cmd)
{
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	if (cmd->infile_fd > -2 && cmd->infile_fd != STDIN_FILENO)
		close(cmd->infile_fd);
	if (cmd->outfile_fd > -2 && cmd->outfile_fd != STDOUT_FILENO)
		close(cmd->outfile_fd);
}

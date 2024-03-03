/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:52:51 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/18 16:09:05 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	make_pipe(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (!cmd->next)
		return (0);
	if (pipe(pipe_fd) < 0)
		exit(1);
	cmd->out_fd = pipe_fd[1];
	cmd = cmd->next;
	while (cmd)
	{
		cmd->in_fd = pipe_fd[0];
		if (!cmd->next)
			break ;
		if (pipe(pipe_fd) < 0)
			exit(1);
		cmd->out_fd = pipe_fd[1];
		cmd = cmd->next;
	}
	return (0);
}

int	pipe_to_fd(t_cmd *cmd)
{
	int	error_flag;

	error_flag = 0;
	if (cmd->in_fd != STDIN_FILENO)
		error_flag = dup2(cmd->in_fd, STDIN_FILENO);
	if (error_flag == -1)
		return (-1);
	if (cmd->out_fd != STDOUT_FILENO)
		error_flag = dup2(cmd->out_fd, STDOUT_FILENO);
	if (error_flag == -1)
		return (-1);
	return (0);
}

int	file_to_fd(t_cmd *cmd)
{
	int	error_flag;

	error_flag = 0;
	if (cmd->infile_fd > 0)
	{
		close(cmd->in_fd);
		error_flag = dup2(cmd->infile_fd, STDIN_FILENO);
		if (error_flag == -1)
			return (-1);
	}
	if (cmd->outfile_fd > 0)
	{
		close(cmd->out_fd);
		error_flag = dup2(cmd->outfile_fd, STDOUT_FILENO);
		if (error_flag == -1)
			return (-1);
	}
	return (0);
}

int	close_prev(t_cmd *start, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = 0;
	if (cmd->idx > 0)
		tmp = cmd_idx(start, cmd->idx - 1);
	else
		return (0);
	if (tmp->outfile_fd > -1)
		if (tmp->outfile_fd != STDOUT_FILENO)
			close(tmp->out_fd);
	if (tmp->out_fd > -1 && tmp->outfile_fd == -2)
		if (tmp->out_fd != STDOUT_FILENO)
			close(tmp->out_fd);
	return (0);
}

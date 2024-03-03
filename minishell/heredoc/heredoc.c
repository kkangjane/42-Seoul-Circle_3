/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:31:56 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/19 15:43:08 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static void	open_heredoc_file(t_cmd *cmd);
static void	heredoc_count(t_cmd *cmd);

int	check_heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	open_heredoc_file(cmd);
	pid = fork();
	if (pid == 0)
	{
		set_signal_heredoc();
		while (cmd)
		{
			heredoc_per_cmdline(cmd, &cmd->files);
			cmd = cmd->next;
		}
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (update_exit_code(WEXITSTATUS(status)));
		else if (WIFSIGNALED(status))
			if (WTERMSIG(status) == 2)
				return (update_exit_code(1));
	}
	return (0);
}

static void	open_heredoc_file(t_cmd *cmd)
{
	t_file_lst	*tmp;
	int			fd;
	int			idx;

	idx = 0;
	heredoc_count(cmd);
	while (cmd)
	{
		tmp = cmd->files;
		while (tmp)
		{
			if ((tmp->io_flag & HEREDOC) == HEREDOC)
			{
				arr_add(&(cmd->heredoc), tmp->filename);
				tmp->filename = make_file_name(cmd, &idx);
				fd = open(tmp->filename, O_CREAT, 0644);
				close(fd);
			}
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

static void	heredoc_count(t_cmd *cmd)
{
	t_file_lst	*tmp;
	int			cnt;

	cnt = 0;
	while (cmd)
	{
		tmp = cmd->files;
		while (tmp)
		{
			if ((tmp->io_flag & HEREDOC) == HEREDOC)
				cnt++;
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	if (cnt > 16)
	{
		cmd_free(&cmd);
		arr_free(&g_env);
		exit(print_error(0, 0, "maximum here-document count exceeded\n", 2));
	}
}

void	heredoc(char *str, char *file_name)
{
	char	*input;
	int		fd;

	fd = open(file_name, O_WRONLY);
	while (1)
	{
		input = readline("> \033[s");
		if (input == 0)
		{
			write(1, "\033[u", 4);
			close(fd);
			free(str);
			return ;
		}
		if (ft_strcmp(input, str) == 0)
		{
			close(fd);
			free(str);
			free(input);
			return ;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
}

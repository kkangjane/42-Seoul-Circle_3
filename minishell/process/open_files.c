/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:35:51 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/18 17:17:45 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	open_file(char	*file, int open_flag);
static int	open_infile(t_file_lst *files);
static int	open_outfile(t_file_lst *files);

int	files_open_test(t_file_lst *files, t_cmd *cmd)
{
	int	fd;

	while (files)
	{
		fd = open_file(files->filename, files->io_flag);
		if (fd < 0)
		{
			perror_msg(files->filename);
			return (1);
		}
		else
			close(fd);
		files = files->next;
	}
	cmd->infile_fd = open_infile(cmd->files);
	cmd->outfile_fd = open_outfile(cmd->files);
	return (0);
}

static int	open_infile(t_file_lst *files)
{
	t_file_lst	*last;
	int			fd;

	last = 0;
	while (files)
	{
		if (files->io_flag == (INPUT | REDIRECT))
			last = files;
		else if (files->io_flag == (INPUT | HEREDOC | REDIRECT))
			last = files;
		files = files->next;
	}
	if (!last)
		return (-2);
	fd = open_file(last->filename, last->io_flag);
	return (fd);
}

static int	open_outfile(t_file_lst *files)
{
	t_file_lst	*last;
	int			fd;

	last = 0;
	while (files)
	{
		if (files->io_flag == (OUTPUT | REDIRECT | APPEND))
			last = files;
		else if (files->io_flag == (OUTPUT | REDIRECT))
			last = files;
		files = files->next;
	}
	if (!last)
		return (-2);
	fd = open_file(last->filename, last->io_flag);
	return (fd);
}

static int	open_file(char	*file, int open_flag)
{
	int	fd;

	fd = -2;
	if (open_flag == (INPUT | REDIRECT))
		fd = open(file, O_RDONLY);
	else if (open_flag == (INPUT | REDIRECT | HEREDOC))
		fd = open(file, O_RDONLY);
	else if (open_flag == (OUTPUT | REDIRECT | APPEND))
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (open_flag == (OUTPUT | REDIRECT))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		ft_putendl_fd("file's io_flag is wrong", STDOUT_FILENO);
	return (fd);
}

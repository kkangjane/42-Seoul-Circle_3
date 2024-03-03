/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:43 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	check_outfile(t_file_lst *files, char *file, char *pwd);
static int	check_file_name(char *file_name, t_cmd *cmd);
static char	*heredoc_home(void);

static int	check_outfile(t_file_lst *files, char *file, char *pwd)
{
	char		*file_path;

	while (files)
	{
		if (((files->io_flag) & OUTPUT) == OUTPUT)
		{
			if (files->filename[0] == '/' && !ft_strcmp(file, files->filename))
				return (1);
			else if (files->filename[0] != '/' && pwd)
			{
				file_path = ft_strjoin(pwd, file);
				if (!file_path)
					error_exit("heredoc");
				if (ft_strcmp(file_path, files->filename) == 0)
				{
					free(pwd);
					free(file_path);
					return (1);
				}
				free(file_path);
			}
		}
		files = files->next;
	}
	return (0);
}

static int	check_file_name(char *file_name, t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(0, 1024);
	if (access(file_name, F_OK) != 0
		&& !check_outfile(cmd->files, file_name, pwd))
	{
		if (pwd)
			free(pwd);
		return (1);
	}
	if (pwd)
		free(pwd);
	return (0);
}

char	*make_file_name(t_cmd *cmd, int *file_idx)
{
	char	*home;
	char	*temp;
	char	*file_name;

	home = heredoc_home();
	while (1)
	{
		temp = ft_itoa((*file_idx)++);
		file_name = ft_strjoin(home, temp);
		if (!file_name || !temp)
			error_exit("heredoc");
		free(temp);
		if (check_file_name(file_name, cmd))
		{
			if (home)
				free(home);
			return (file_name);
		}
		free(file_name);
	}
	return (0);
}

static char	*heredoc_home(void)
{
	char	*home;
	char	*temp;

	home = exploit_value("HOME");
	if (home)
	{
		temp = ft_strjoin(home, "/goinfre/");
		if (!temp)
			error_exit("heredoc");
		free(home);
		home = temp;
	}
	return (home);
}

void	heredoc_per_cmdline(t_cmd *cmd, t_file_lst **files)
{
	t_file_lst	*file;
	int			h_idx;

	file = *files;
	h_idx = 0;
	while (file)
	{
		if ((file->io_flag & (HEREDOC)) == (HEREDOC))
			heredoc(cmd->heredoc[h_idx++], file->filename);
		file = file->next;
	}
}

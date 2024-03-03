/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:17:01 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/18 17:14:01 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	find_fd(t_cmd *cmd, int inout)
{
	if (inout == 0)
	{
		if (cmd->infile_fd > 0)
			return (cmd->infile_fd);
		else
			return (cmd->in_fd);
	}
	else
	{
		if (cmd->outfile_fd > 0)
			return (cmd->outfile_fd);
		else
			return (cmd->out_fd);
	}
}

int	all_check(char	*keys[], char *cmd)
{
	int		i;
	int		err;

	i = -1;
	err = 0;
	while (keys[++i])
	{
		if (!ft_isalpha(keys[i][0]) && keys[i][0] != '_')
		{
			ft_putstr_fd("moo: ", STDOUT_FILENO);
			ft_putstr_fd(cmd, STDOUT_FILENO);
			ft_putstr_fd(": `", STDOUT_FILENO);
			ft_putstr_fd(keys[i], STDOUT_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDOUT_FILENO);
			err = 1;
		}
	}
	return (err);
}

int	close_out_fd(t_cmd *proc, int ret)
{
	int	out_fd;

	out_fd = find_fd(proc, 1);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (ret);
}

int	close_in_fd(t_cmd *proc, int ret)
{
	int	in_fd;

	in_fd = find_fd(proc, 0);
	if (in_fd != STDOUT_FILENO)
		close(in_fd);
	return (ret);
}

int	check_dir(char *dir)
{
	DIR	*dirp;

	dirp = opendir(dir);
	if (!dirp)
		return (print_error("cd", dir, "No such file or directory\n", 0));
	closedir(dirp);
	return (1);
}

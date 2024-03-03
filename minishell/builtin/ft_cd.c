/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:11:06 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static void	change_pwd(char *oldpwd);
static int	cd_home(t_cmd *proc, char *oldpwd);
static int	cd_homeplus(t_cmd *proc, char *oldpwd);
static int	cd(t_cmd *proc, char *oldpwd);

int	ft_cd(t_cmd *proc)
{
	char	*oldpwd;

	close_out_fd(proc, 0);
	oldpwd = getcwd(0, 1024);
	if (!proc->cmd[1] || ft_strcmp(proc->cmd[1], "~") == 0)
		return (cd_home(proc, oldpwd));
	else if (ft_strncmp(proc->cmd[1], "~/", 2) == 0)
		return (cd_homeplus(proc, oldpwd));
	return (cd(proc, oldpwd));
}

static int	cd_home(t_cmd *proc, char *oldpwd)
{
	char	*home;

	home = exploit_value("HOME");
	if (!home)
	{
		print_error("cd", 0, "Home not set\n", 31);
		return (free_str(oldpwd, home, 0, 31));
	}
	if (check_dir(home) == 0)
		return (free_str(oldpwd, home, 0, 1));
	if (!(proc->idx == 0 && proc->next == 0))
		return (free_str(oldpwd, home, 0, 0));
	if (chdir(home) < 0)
	{
		perror_msg(home);
		return (free_str(oldpwd, home, 0, 1));
	}
	change_pwd(oldpwd);
	return (free_str(oldpwd, home, 0, 0));
}

static int	cd_homeplus(t_cmd *proc, char *oldpwd)
{
	char	*home;
	char	*path;

	home = exploit_value("HOME");
	if (!home)
	{
		print_error("cd", 0, "Home not set\n", 31);
		return (free_str(oldpwd, 0, 0, 31));
	}
	path = ft_strjoin(home, &proc->cmd[1][1]);
	if (!path)
		return (free_str(oldpwd, home, 0, 1));
	if (check_dir(path) == 0)
		return (free_str(path, oldpwd, home, 1));
	if (!(proc->idx == 0 && proc->next == 0))
		return (free_str(path, oldpwd, home, 0));
	if (chdir(path) < 0)
	{
		print_error("cd", proc->cmd[1], "No such file or directory\n", 1);
		return (free_str(oldpwd, path, home, 1));
	}
	change_pwd(oldpwd);
	return (free_str(oldpwd, path, home, 0));
}

static int	cd(t_cmd *proc, char *oldpwd)
{
	if (check_dir(proc->cmd[1]) == 0)
		return (free_str(oldpwd, 0, 0, 1));
	if (!(proc->idx == 0 && proc->next == 0))
		return (free_str(oldpwd, 0, 0, 0));
	if (chdir(proc->cmd[1]) < 0)
	{
		print_error("cd", proc->cmd[1], "No such file or directory\n", 1);
		return (free_str(oldpwd, 0, 0, 1));
	}
	change_pwd(oldpwd);
	return (free_str(oldpwd, 0, 0, 0));
}

static void	change_pwd(char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(0, 1024);
	if (!pwd)
		error_exit("cd");
	if (oldpwd && find_env_idx("OLDPWD") > -1)
		change_env("OLDPWD", oldpwd);
	else if (oldpwd)
		add_env("OLDPWD", oldpwd);
	if (pwd && find_env_idx("PWD") > -1)
		change_env("PWD", pwd);
	else if (pwd)
		add_env("PWD", pwd);
	free(pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:40:08 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:18:57 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_includes/moo_basic.h"
#include "_includes/moo_environ.h"
#include "_includes/moo_signals.h"

static char	**get_paths(char **envp);
static char	*free_path(char *cmd, char ***paths, char *ret);

void	init_moo(char **argv, int argc, char **envp)
{
	if (argc > 1)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": too many arguments", 2);
		exit(1);
	}
	printf("\033[00;01;32m         (__)\n");
	printf("         (oo)\n");
	printf("   /------\\/\n");
	printf("  / |    ||\n");
	printf(" *  /\\---/\\\n");
	printf("    ~~   ~~\n");
	printf("....\"Have you mooed today?\"...\033[0m\n");
	copy_env(envp);
	update_exit_code(0);
	set_signal_main();
}

t_cmd	*cmd_idx(t_cmd *cmd, int idx)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = cmd;
	if (idx < 0)
		return (0);
	while (temp)
	{
		if (temp->idx == idx)
			return (temp);
		temp = temp->next;
	}
	return (0);
}

char	*find_command(char **cmd_args)
{
	char	*cmd;
	char	**paths;
	char	*path_cmd;
	int		i;

	if (cmd_args == 0 || cmd_args[0] == 0)
		return (0);
	if (ft_strrchr(cmd_args[0], '/') != 0 && access(cmd_args[0], F_OK) != -1)
		return (ft_strdup(cmd_args[0]));
	if (ft_strrchr(cmd_args[0], '/') != 0 && access(cmd_args[0], F_OK) == -1)
		return (0);
	cmd = ft_strjoin("/", cmd_args[0]);
	i = -1;
	paths = get_paths(g_env);
	while (paths && paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], cmd);
		if (access(path_cmd, F_OK) != -1)
			return (free_path(cmd, &paths, path_cmd));
		free(path_cmd);
	}
	return (free_path(cmd, &paths, 0));
}

static char	**get_paths(char **envp)
{
	int		i;
	char	*paths;
	char	**result;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			paths = ft_strdup(envp[i] + 5);
			result = ft_split(paths, ':');
			free(paths);
			return (result);
		}
		i++;
	}
	return (0);
}

static char	*free_path(char *cmd, char ***paths, char *ret)
{
	int	i;

	if (cmd)
		free(cmd);
	i = 0;
	if (paths == 0)
		return (ret);
	if (*paths)
	{
		while ((*paths)[i])
			free((*paths)[i++]);
	}
	if (*paths)
		free(*paths);
	return (ret);
}

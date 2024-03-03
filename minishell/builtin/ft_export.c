/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:19:01 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	print_env(t_cmd *proc);
static void	export_one(char *line);
static int	check_update(char *key, char *value);

int	ft_export(t_cmd *proc)
{
	int		i;
	int		err;

	if (proc->cmd[1] == 0)
		return (print_env(proc));
	close_out_fd(proc, 0);
	err = all_check(&proc->cmd[1], "export");
	if (!(proc->next == 0 && proc->idx == 0))
		return (err);
	i = 0;
	while (proc->cmd[++i])
		if (ft_isalpha(proc->cmd[i][0]) || proc->cmd[i][0] == '_')
			export_one(proc->cmd[i]);
	return (err);
}

static int	print_env(t_cmd *proc)
{
	int		i;
	char	*key;

	i = -1;
	while (g_env[++i])
	{
		key = exploit_key(i);
		if (!ft_strncmp(key, "_", 1) || !ft_strncmp(key, "?", 1))
		{
			free(key);
			continue ;
		}
		print_line(key, find_fd(proc, 1));
		free(key);
	}
	return (close_out_fd(proc, 0));
}

static void	export_one(char *line)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = (char *) malloc(sizeof(char) * (i + 1));
	if (!key)
		error_exit("export");
	ft_strlcpy(key, line, i + 1);
	if (line[i] == 0)
		value = 0;
	else
		value = ft_strdup(&line[i + 1]);
	if (check_update(key, value))
	{
		if (find_env_idx(key) < 0)
			add_env(key, value);
		else
			change_env(key, value);
	}
	free(key);
	if (value)
		free(value);
}

static int	check_update(char *key, char *value)
{
	char	*old_value;
	int		ret;

	if (find_env_idx(key) < 0)
		return (1);
	old_value = exploit_value(key);
	if (old_value)
	{
		if (value)
			ret = 1;
		else
			ret = 0;
		free(old_value);
	}
	else
		ret = 1;
	return (ret);
}

void	print_line(char *key, int out_fd)
{
	char	*val;

	val = exploit_value(key);
	ft_putstr_fd("declare -x ", out_fd);
	ft_putstr_fd(key, out_fd);
	if (val)
	{
		ft_putstr_fd("=\"", out_fd);
		ft_putstr_fd(val, out_fd);
		ft_putendl_fd("\"", out_fd);
		free(val);
	}
	else
		ft_putchar_fd('\n', out_fd);
}

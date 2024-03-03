/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:39:42 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_environ.h"

void	copy_env(char **original)
{
	int	line;

	line = 0;
	while (original[line])
		line++;
	g_env = (char **) malloc(sizeof(char *) * (line + 1));
	if (!g_env)
		error_exit("copy_env");
	line = 0;
	while (original[line])
	{
		g_env[line] = ft_strdup(original[line]);
		if (!g_env[line])
			error_exit("copy_env");
		line++;
	}
	g_env[line] = 0;
}

int	change_env(char *key, char *value)
{
	char	*new_line;
	int		idx;

	idx = find_env_idx(key);
	if (value == 0)
	{
		free(g_env[idx]);
		g_env[idx] = key;
		return (0);
	}
	new_line = join_key_value(key, value);
	if (!new_line)
		return (-1);
	free(g_env[idx]);
	g_env[idx] = new_line;
	return (0);
}

int	add_env(char *key, char *value)
{
	char	*new_line;
	char	**new_env;
	int		i;
	int		j;

	new_line = join_key_value(key, value);
	if (!new_line)
		error_exit("add_env");
	i = 0;
	while (g_env[i])
		i++;
	new_env = (char **) malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		error_exit("add_env");
	i = -1;
	j = 0;
	while (g_env[++i])
		new_env[j++] = g_env[i];
	new_env[j++] = new_line;
	new_env[j] = 0;
	free(g_env);
	g_env = new_env;
	return (0);
}

void	remove_env(int idx)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (g_env[i])
		i++;
	new_env = (char **) malloc(sizeof(char *) * i);
	if (!new_env)
		error_exit("remove_env");
	i = -1;
	j = 0;
	while (g_env[++i])
	{
		if (i == idx)
			free(g_env[i]);
		else
			new_env[j++] = g_env[i];
	}
	new_env[j] = 0;
	free(g_env);
	g_env = new_env;
}

int	update_exit_code(int code)
{
	char	*c;
	int		idx;

	idx = find_env_idx("?");
	c = ft_itoa(code % 256);
	if (!c)
		return (-1);
	if (idx < 0)
		add_env("?", c);
	else
		change_env("?", c);
	free(c);
	return (code);
}

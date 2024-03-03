/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:05 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_environ.h"

char	*exploit_value(char *key)
{
	char	*value;
	char	*line;
	int		idx;

	idx = find_env_idx(key);
	if (idx < 0)
		return (0);
	line = g_env[idx];
	idx = 0;
	while (line[idx] && line[idx] != '=')
		idx++;
	if (!line[idx])
		return (0);
	idx++;
	value = ft_strdup(&line[idx]);
	return (value);
}

int	find_env_idx(char *key)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		error_exit("env");
	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(g_env[i], temp, ft_strlen(temp))
			|| !ft_strcmp(g_env[i], key))
		{
			free(temp);
			return (i);
		}
	}
	free(temp);
	return (-1);
}

char	*exploit_key(int idx)
{
	char	*key;
	int		i;

	if (idx < 0)
		return (0);
	i = 0;
	while (g_env[idx][i] && g_env[idx][i] != '=')
		i++;
	if (g_env[idx][i] == 0)
		key = (char *) malloc(sizeof(char) * i);
	else
		key = (char *) malloc(sizeof(char) * (i + 1));
	if (!key)
		error_exit("exploit_key");
	i = 0;
	while (g_env[idx][i] && g_env[idx][i] != '=')
	{
		key[i] = g_env[idx][i];
		i++;
	}
	key[i] = 0;
	return (key);
}

char	*join_key_value(char *key, char *value)
{
	char	*temp;
	char	*new_line;

	if (!value)
		return (ft_strdup(key));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (0);
	new_line = ft_strjoin(temp, value);
	free(temp);
	if (!new_line)
		return (0);
	return (new_line);
}

char	**make_fake_environ(void)
{
	int		i;
	int		j;
	char	**new;
	int		code;

	i = 0;
	while (g_env[i])
		i++;
	code = find_env_idx("?");
	new = (char **) malloc(sizeof(char *) * (i));
	i = 0;
	j = 0;
	while (g_env[i])
	{
		if (i != code)
			new[j++] = g_env[i];
		i++;
	}
	new[j] = 0;
	return (new);
}

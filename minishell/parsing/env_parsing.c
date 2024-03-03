/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:17:46 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 16:14:44 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"
#include "../_includes/moo_environ.h"

static char	*value_in_env(char **key);
static int	valid_env_key_char(char c, int start_flag);

static char	*value_in_env(char **key)
{
	char	*value;
	t_buf	*key_buf;

	value = 0;
	if (valid_env_key_char(**key, 1) == 0)
	{
		value = ft_strdup("$");
		(*key)--;
		if (!value)
			return (0);
		return (value);
	}
	if (**key == '?')
		return (exploit_value("?"));
	key_buf = 0;
	while (valid_env_key_char(**key, 0) == 1)
	{
		char_to_buf(&key_buf, **key);
		(*key)++;
	}
	value = exploit_value(key_buf->buf);
	buf_free(&key_buf);
	(*key)--;
	return (value);
}

void	parse_dollar(t_buf **buf, char **str)
{
	char	*value;
	int		dollar_idx;

	dollar_idx = 0;
	(*str)++;
	value = value_in_env(str);
	if (!value)
	{
		char_to_buf(buf, 0);
		return ;
	}
	dollar_idx = 0;
	if (value[dollar_idx] == 0)
		char_to_buf(buf, 0);
	while (value[dollar_idx])
		char_to_buf(buf, value[dollar_idx++]);
	free(value);
	return ;
}

void	parse_dollar2(t_buf **buf, char **str, t_token **token)
{
	char	*value;
	int		dollar_idx;
	int		attr;

	attr = 0;
	(*str)++;
	value = value_in_env(str);
	if (!value)
		return ;
	dollar_idx = -1;
	if (value[0] == 0)
		char_to_buf(buf, 0);
	while (value[++dollar_idx])
	{
		if (ft_isspace(value[dollar_idx]) == 1)
			token_add(buf, &attr, token);
		else
			char_to_buf(buf, value[dollar_idx]);
	}
	free(value);
	return ;
}

static int	valid_env_key_char(char c, int start_flag)
{
	if (start_flag == 1 && (ft_isalpha(c) == 1 || c == '?'))
		return (1);
	if (start_flag == 0 && ft_isalnum(c) == 1)
		return (1);
	if (c == '-' || c == '_')
		return (1);
	return (0);
}

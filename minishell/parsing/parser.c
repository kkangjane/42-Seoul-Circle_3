/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:13:05 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static int		single_quote(t_buf **buf, char **str);
static int		double_quote(t_buf **buf, char **str);
static t_cmd	*free_end(t_token **token, t_buf **buf, t_cmd **cmd);
static int		read_cmd(char **s, int *attr, t_buf **buf, t_token **token);

static int	single_quote(t_buf **buf, char **str)
{
	int	flag;

	flag = 0;
	(*str)++;
	while (**str && **str != '\'')
	{
		char_to_buf(buf, **str);
		(*str)++;
		flag++;
	}
	if (flag == 0)
		char_to_buf(buf, 0);
	if (**str == 0)
	{
		print_error("input is not closed quote", 0, "`\'\'\n", 0);
		if (token_error_update_exit() < 0)
			parsing_error_exit("malloc");
		return (-1);
	}
	return (0);
}

static int	double_quote(t_buf **buf, char **str)
{
	int	flag;

	flag = 0;
	(*str)++;
	while (**str && **str != '\"')
	{
		if (**str == '$')
			parse_dollar(buf, str);
		else
			char_to_buf(buf, **str);
		(*str)++;
		flag++;
	}
	if (flag == 0)
		char_to_buf(buf, 0);
	if (**str == 0)
	{
		print_error("input is not closed quote", 0, "`\"\'\n", 0);
		if (token_error_update_exit() < 0)
			parsing_error_exit("malloc");
		return (-1);
	}
	return (0);
}

static t_cmd	*free_end(t_token **token, t_buf **buf, t_cmd **cmd)
{
	token_free(token);
	buf_free(buf);
	cmd_free(cmd);
	return (0);
}

static int	read_cmd(char **s, int *attr, t_buf **buf, t_token **token)
{
	if (ft_isspace(**s) == 1)
		token_add(buf, attr, token);
	else if (getattr(s, 0) != 0)
	{
		token_add(buf, attr, token);
		*attr = 0;
		(*s)--;
	}
	else if (**s == '\'')
		return (single_quote(buf, s));
	else if (**s == '\"')
		return (double_quote(buf, s));
	else if (**s == '$')
		parse_dollar2(buf, s, token);
	else
		char_to_buf(buf, **s);
	return (0);
}

t_cmd	*parsing(char *str)
{
	t_token	*token;
	t_buf	*buf;
	t_cmd	*cmd;
	int		attr;

	buf = 0;
	token = 0;
	cmd = 0;
	attr = 0;
	while (*str)
	{
		if (attr == 0)
		{
			attr = check_attr_and_add_token(&str, &token, &buf);
			if (token_error_check(attr, &str) < 0)
				return (free_end(&token, &buf, &cmd));
			if (pipe_cmd_add(&cmd, &token, &buf, &attr) < 0)
				return (0);
		}
		if (read_cmd(&str, &attr, &buf, &token) < 0)
			return (free_end(&token, &buf, &cmd));
		str++;
	}
	cmd_add(&cmd, &token, &buf, &attr);
	return (cmd);
}

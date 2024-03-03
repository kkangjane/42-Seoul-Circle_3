/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:19:41 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/19 11:28:08 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

int	getattr(char **str, int flag)
{
	int	attr;

	attr = 0;
	if (ft_strncmp(*str, "<<", 2) == 0)
	{
		flag = flag << 1;
		attr = (HEREDOC | REDIRECT | INPUT);
	}
	else if (ft_strncmp(*str, ">>", 2) == 0)
	{
		flag = flag << 1;
		attr = (REDIRECT | OUTPUT | APPEND);
	}
	else if (ft_strncmp(*str, "|", 1) == 0)
		attr = PIPE;
	else if (ft_strncmp(*str, "<", 1) == 0)
		attr = (REDIRECT | INPUT);
	else if (ft_strncmp(*str, ">", 1) == 0)
		attr = (REDIRECT | OUTPUT);
	if (flag == 0)
		return (attr);
	*str += (flag) * (attr > 0);
	return (attr);
}

int	check_attr_and_add_token(char **str, t_token **token, t_buf **buf)
{
	int	tmp_attr;
	int	attr;

	attr = getattr(str, 1);
	if (attr)
	{
		tmp_attr = 0;
		token_add(buf, &tmp_attr, token);
	}
	return (attr);
}

int	pipe_cmd_add(t_cmd **cmd, t_token **token, t_buf **buf, int *attr)
{
	if (*attr != PIPE)
		return (0);
	if (!(*buf) && !(*token) && !(*cmd))
	{
		print_token_error(PIPE);
		return (-1);
	}
	cmd_add(cmd, token, buf, attr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_struct_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:19 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static t_buf	*buf_sizeup(t_buf **buf);
static t_buf	*buf_new(void);

static t_buf	*buf_new(void)
{
	t_buf	*new;

	new = (t_buf *)malloc(sizeof(t_buf));
	if (!new)
		return (0);
	new->buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(new->buf))
	{
		free(new);
		return (0);
	}
	new->buf[0] = 0;
	new->buf_size = BUFFER_SIZE;
	new->saved = new->buf;
	new->saved_size = 0;
	return (new);
}

static t_buf	*buf_sizeup(t_buf **buf)
{
	char	*new;

	if (!*buf || !(*buf)->buf)
		return (buf_free(buf));
	new = (char *)malloc(sizeof(char) * (((*buf)->buf_size) * 2 + 1));
	if (!new)
		return (buf_free(buf));
	new = ft_memmove(new, (*buf)->buf, (*buf)->saved_size);
	free((*buf)->buf);
	(*buf)->buf_size *= 2;
	(*buf)->buf = new;
	(*buf)->saved = &(new[(*buf)->saved_size]);
	return (*buf);
}

void	*buf_free(t_buf **buf)
{
	if (buf && *buf)
	{
		if ((*buf)->buf)
			free((*buf)->buf);
		free((*buf));
	}
	*buf = 0;
	return (0);
}

void	char_to_buf(t_buf **buf, char save)
{
	if (!*buf)
	{
		*buf = buf_new();
		if (!*buf)
			parsing_error_exit("minishell");
	}
	if ((*buf)->buf_size == (*buf)->saved_size - 1)
	{
		*buf = buf_sizeup(buf);
		if (!*buf)
			parsing_error_exit("minishell");
	}
	*((*buf)->saved++) = save;
	*((*buf)->saved) = 0;
	(*buf)->saved_size += 1;
	if (!save)
	{
		(*buf)->saved -= 1;
		(*buf)->saved_size -= 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:16:11 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static t_token	*token_new(char **buf, int *attr);

static t_token	*token_new(char **buf, int *attr)
{
	t_token	*rv;

	rv = (t_token *)malloc(sizeof(t_token));
	if (!rv)
	{
		free(*buf);
		*buf = 0;
		return (0);
	}
	rv->buf = *buf;
	*buf = 0;
	rv->attr = *attr;
	*attr = 0;
	rv->next = 0;
	return (rv);
}

void	token_add(t_buf **buf, int *attr, t_token **token)
{
	char	*token_basket;
	t_token	*iter;

	if (!*buf || !((*buf)->buf))
		return ;
	token_basket = ft_strdup((*buf)->buf);
	buf_free(buf);
	if (!token_basket)
		parsing_error_exit("minishell");
	iter = *token;
	if (!iter)
		*token = token_new(&token_basket, attr);
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = token_new(&token_basket, attr);
	}
	if (!(*token) || (iter && !(iter->next)))
		parsing_error_exit("minishell");
	return ;
}

void	*token_free(t_token **token)
{
	t_token	*iter;

	if (!token || !*token)
		return (0);
	iter = *token;
	while (*token)
	{
		*token = (*token)->next;
		free(iter->buf);
		free(iter);
		iter = *token;
	}
	*token = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:18:33 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static t_cmd	*cmd_new(void);
static t_cmd	*cmd_last(t_cmd **cmd);

static t_cmd	*cmd_new(void)
{
	t_cmd	*rv;

	rv = (t_cmd *)malloc(sizeof(t_cmd));
	if (!rv)
		return (0);
	rv->cmd = 0;
	rv->idx = 0;
	rv->error = 0;
	rv->files = 0;
	rv->in_fd = 0;
	rv->pid = -1;
	rv->out_fd = 1;
	rv->infile_fd = -2;
	rv->outfile_fd = -2;
	rv->next = 0;
	rv->heredoc = 0;
	return (rv);
}

void	*cmd_free(t_cmd **cmd)
{
	t_cmd	*iter;
	t_cmd	*tmp;

	if (!cmd || !(*cmd))
		return (0);
	iter = *cmd;
	while (iter)
	{
		file_free(&(iter->files));
		arr_free(&(iter->cmd));
		arr_free(&(iter->heredoc));
		tmp = iter->next;
		free(iter);
		iter = tmp;
	}
	*cmd = 0;
	return (0);
}

static t_cmd	*cmd_last(t_cmd **cmd)
{
	t_cmd	*iter;

	if (!*(cmd))
	{
		*cmd = cmd_new();
		if (!*cmd)
			return (0);
		iter = *cmd;
	}
	else
	{
		iter = *cmd;
		while (iter->next)
			iter = iter->next;
		iter->next = cmd_new();
		if (!(iter->next))
		{
			cmd_free(cmd);
			return (0);
		}
		iter->next->idx = iter->idx + 1;
		iter = iter->next;
	}
	return (iter);
}

void	cmd_add(t_cmd **cmd, t_token **token, t_buf **buf, int *attr)
{
	t_cmd	*cur;
	t_token	*tmp;

	token_add(buf, attr, token);
	cur = cmd_last(cmd);
	if (!cur)
		parsing_error_exit("minishell");
	while (*token)
	{
		if (((*token)->attr & REDIRECT) == REDIRECT)
			file_add(&(cur->files), (*token)->buf, (*token)->attr);
		else
			arr_add(&(cur->cmd), (*token)->buf);
		tmp = (*token);
		(*token) = (*token)->next;
		free(tmp);
	}
	*token = 0;
}

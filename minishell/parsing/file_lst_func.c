/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lst_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:36:12 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static t_file_lst	*file_new(void);

static t_file_lst	*file_new(void)
{
	t_file_lst	*node;

	node = (t_file_lst *)malloc(sizeof(t_file_lst));
	if (!node)
		return (0);
	node->filename = 0;
	node->io_flag = 0;
	node->next = 0;
	return (node);
}

void	*file_free(t_file_lst **file)
{
	t_file_lst	*iter;

	if (!*file)
		return (0);
	iter = *file;
	while (iter)
	{
		*file = (*file)->next;
		if ((iter->io_flag & (HEREDOC)) == (HEREDOC))
			unlink(iter->filename);
		free(iter->filename);
		free(iter);
		iter = *file;
	}
	return (0);
}

void	file_add(t_file_lst **head, char *filename, int io_flag)
{
	t_file_lst	*new;
	t_file_lst	*iter;

	new = file_new();
	if (!new)
	{
		file_free(head);
		parsing_error_exit("minishell");
	}
	new->filename = filename;
	new->io_flag = io_flag;
	if (!*head)
		*head = new;
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
	return ;
}

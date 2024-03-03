/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:07:20 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/17 16:15:56 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	ft_unset(t_cmd *proc)
{
	int		i;
	int		idx;
	int		err;

	close_out_fd(proc, 0);
	if (proc->cmd[1] == 0)
		return (0);
	err = all_check(&proc->cmd[1], "unset");
	if (!(proc->idx == 0 && proc->next == 0))
		return (err);
	i = 0;
	while (proc->cmd[++i])
	{
		if (!(ft_isalpha(proc->cmd[i][0]) || proc->cmd[i][0] == '_'))
			continue ;
		idx = find_env_idx(proc->cmd[i]);
		if (idx < 0)
			continue ;
		remove_env(idx);
	}
	return (err);
}

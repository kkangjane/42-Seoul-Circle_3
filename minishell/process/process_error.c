/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:55:50 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/19 11:46:54 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	cmdfile_error(t_cmd *cmd)
{
	print_error(0, cmd->cmd[0], "command not found\n", 127);
	exit(127);
	return (127);
}

int	fileopen_err(int ex)
{
	if (ex)
		exit(1);
	update_exit_code(1);
	return (1);
}

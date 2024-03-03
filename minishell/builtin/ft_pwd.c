/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:46:41 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/17 16:15:48 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

int	ft_pwd(t_cmd *proc)
{
	int		out_fd;
	char	*pwd;

	out_fd = find_fd(proc, 1);
	pwd = getcwd(0, 1024);
	if (!pwd)
	{
		perror_msg("pwd");
		return (close_out_fd(proc, 1));
	}
	ft_putendl_fd(pwd, out_fd);
	free(pwd);
	return (close_out_fd(proc, 0));
}

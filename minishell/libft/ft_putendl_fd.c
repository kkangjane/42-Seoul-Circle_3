/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:49:17 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/22 16:16:57 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	size_t	check;

	if (!s)
		return ;
	if (fd < 0)
		return ;
	len = ft_strlen(s);
	check = 0;
	while (check != len)
		check += write(fd, s + check, len - check);
	write(fd, "\n", 1);
}

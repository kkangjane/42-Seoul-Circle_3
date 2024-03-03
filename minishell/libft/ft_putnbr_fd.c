/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:52:40 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:43:38 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n <= -10)
			ft_putnbr_fd((-1) * (n / 10), fd);
		ft_putnbr_fd((-1) * (n % 10), fd);
		return ;
	}
	if (n < 10)
	{
		nbr = '0' + n;
		write(fd, &nbr, 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}

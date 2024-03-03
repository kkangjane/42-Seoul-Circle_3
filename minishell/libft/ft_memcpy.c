/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:46:48 by seonggek          #+#    #+#             */
/*   Updated: 2023/10/10 14:53:51 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstarr;
	unsigned char	*srcarr;

	i = 0;
	dstarr = (unsigned char *)dst;
	srcarr = (unsigned char *)src;
	while (n > 0 && (srcarr != 0 || dstarr != 0))
	{
		n -= sizeof(char);
		dstarr[i] = srcarr[i];
		i++;
	}
	return (dst);
}

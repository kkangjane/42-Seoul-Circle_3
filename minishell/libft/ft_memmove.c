/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:01:18 by seonggek          #+#    #+#             */
/*   Updated: 2023/10/10 14:53:52 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dstarr;
	char		*srcarr;
	size_t		i;

	dstarr = (char *)dst;
	srcarr = (char *)src;
	if ((long long)dst < (long long)src)
	{
		i = 0;
		while (i < len)
		{
			dstarr[i] = srcarr[i];
			i++;
		}
	}
	else if ((long long)dst > (long long)src)
	{
		while (len > 0)
		{
			len--;
			dstarr[len] = srcarr[len];
		}
	}
	return (dst);
}

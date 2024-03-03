/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:19:21 by seonggek          #+#    #+#             */
/*   Updated: 2023/10/10 14:53:21 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	tofind;
	unsigned char	*arr;
	size_t			i;

	i = 0;
	arr = (unsigned char *)s;
	tofind = (unsigned char)c;
	while (i < n)
	{
		if (arr[i] == tofind)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}

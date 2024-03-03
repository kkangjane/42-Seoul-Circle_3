/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:48:55 by seonggek          #+#    #+#             */
/*   Updated: 2023/10/10 14:53:14 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			point;
	char			ch;

	point = ft_strlen(s);
	ch = (char)c;
	if (ch == '\0')
		return ((char *)&s[point]);
	while (point > 0)
	{
		point--;
		if (s[point] == ch)
			return ((char *)&s[point]);
	}
	return (0);
}

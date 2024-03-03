/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:29:51 by seonggek          #+#    #+#             */
/*   Updated: 2023/10/10 14:53:30 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	search_len;
	size_t	i;

	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	search_len = len - len_needle + 1;
	while (*haystack != 0 && search_len > 0)
	{
		i = 0;
		if (*haystack == needle[i])
		{
			if (ft_strncmp(haystack, needle, len_needle) == 0)
				return ((char *)haystack);
		}
		haystack++;
		search_len--;
	}
	return (0);
}

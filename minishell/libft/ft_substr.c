/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:57:08 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:43:08 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (0);
	while (start > 0 && *s)
	{
		s++;
		start--;
	}
	len_s = ft_strlen(s);
	if (len_s < len)
		len = len_s;
	sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (0);
	i = 0;
	while (i < len && s[i])
	{
		sub_str[i] = s[i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

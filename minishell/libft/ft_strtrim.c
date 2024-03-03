/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:14:13 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:43:06 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strin(char s1, char const *set)
{
	size_t	len_set;

	if (!set)
		return (0);
	len_set = ft_strlen(set);
	while (len_set > 0)
	{
		len_set--;
		if (s1 == set[len_set])
			return (1);
	}
	return (0);
}

static size_t	cal_del_len(char const *s1, char const *set)
{
	size_t	i;
	size_t	trimed_len;
	size_t	len;

	i = 0;
	trimed_len = 0;
	len = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strin(s1[i], set) == 1)
	{
		trimed_len++;
		i++;
	}
	i = len;
	while (i >= 1 && ft_strin(s1[i - 1], set) == 1)
	{
		trimed_len++;
		i--;
	}
	if (trimed_len > len)
		return (len);
	return (trimed_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimed_len;
	char	*trimed_str;
	size_t	len;
	size_t	i;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	trimed_len = len - cal_del_len(s1, set);
	trimed_str = (char *)malloc(sizeof(char) * (trimed_len + 1));
	if (!trimed_str)
		return (0);
	while (*s1 && ft_strin(*s1, set))
	{
		s1++;
	}
	i = 0;
	while (s1[i] && i < trimed_len)
	{
		trimed_str[i] = s1[i];
		i++;
	}
	trimed_str[i] = '\0';
	return (trimed_str);
}

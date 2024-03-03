/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:07:03 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/07 15:53:32 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ex_strlen(const char *s)
{
	int	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*(s + cnt))
		cnt++;
	return (cnt);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*joinedstr;

	len_s1 = ft_ex_strlen(s1);
	len_s2 = ft_ex_strlen(s2);
	joinedstr = (char *)malloc(sizeof(char) * (1 + len_s1 + len_s2));
	if (!joinedstr)
		return (0);
	i = 0;
	while (i < len_s1)
	{
		joinedstr[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		joinedstr[i] = s2[i - len_s1];
		i++;
	}
	joinedstr[i] = '\0';
	return (joinedstr);
}

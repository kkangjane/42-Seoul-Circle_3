/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:28:18 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:43:03 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*mapi;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	mapi = (char *)malloc(sizeof(char) * (len + 1));
	if (!mapi)
		return (0);
	while (i < len)
	{
		mapi[i] = f((unsigned int)i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}

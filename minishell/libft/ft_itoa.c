/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:05:35 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:40 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cal_size(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*num;

	size = cal_size(n);
	num = (char *)malloc(sizeof(char) * (size + 1));
	if (!num)
		return (0);
	num[size] = '\0';
	if (n == 0)
		num[0] = '0';
	if (n < 0)
	{
		num[0] = '-';
		num[--size] = '0' - (n % 10);
		n /= -10;
	}
	while (n != 0)
	{
		num[--size] = '0' + (n % 10);
		n /= 10;
	}
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:45:06 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/18 14:12:29 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow_check(int nb, int sign, char c)
{
	if (nb > 214748364 || (nb == 214748364 && (c - '0' > 7)))
		return (2147483647);
	if (nb < -214748364 || (nb == -214748364 && (c - '0' > 8)))
		return (-2147483648);
	return (nb * 10 + (c - '0') * sign);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;
	int	check;

	nb = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	check = 1;
	while (*str >= '0' && *str <= '9')
	{
		if (check == 10)
			return (overflow_check(nb, sign, *str));
		nb = 10 * nb + (*str - '0') * sign;
		str++;
		check++;
	}
	return (nb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:12:46 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/19 12:43:59 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_includes/moo_basic.h"

long long	ft_atol(const char *str)
{
	long long	nb;
	int			sign;

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
	while (*str >= '0' && *str <= '9')
	{
		nb = 10 * nb + (*str - '0') * sign;
		str++;
	}
	return (nb);
}

int	free_str(char *s1, char *s2, char *s3, int ret)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (ret);
}

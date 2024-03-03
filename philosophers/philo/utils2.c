/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:00:41 by jae-kang          #+#    #+#             */
/*   Updated: 2024/03/01 16:33:22 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_print_err(char *msg, int ret)
{
	printf("%s\n", msg);
	return (ret);
}

int	ft_atoi(const char *s)
{
	size_t		i;
	long long	num;
	char		*string;

	i = 0;
	num = 0;
	string = (char *) s;
	while (string[i] <= '9' && string[i] >= '0')
		num = num * 10 + (string[i++] - '0');
	if (string[i] != 0)
		return (-1);
	if (i > 10 || (i == 10 && num > 2147483647))
		return (-1);
	return (num);
}

int	ph_display(t_info *info, t_philo *philo, int flag)
{
	if (ph_check_die(info))
		return (-1);
	pthread_mutex_lock(&info->m_display);
	if (flag == M_ERR)
	{
		printf("mutex error..?\n");
		pthread_mutex_unlock(&info->m_display);
		return (1);
	}
	printf("%lld %d ", (ph_time() - info->start) / 1000, philo->idx + 1);
	if (flag == FORK)
		printf("has taken a fork\n");
	else if (flag == EAT)
		printf("is eating\n");
	else if (flag == SLEEP)
		printf("is sleeping\n");
	else if (flag == THINK)
		printf("is thinking\n");
	pthread_mutex_unlock(&info->m_display);
	return (0);
}

void	*ph_everyone_finish(t_info *info)
{
	if (ph_check_die(info) == 1)
		return (0);
	pthread_mutex_lock(&info->m_die);
	info->die_flag = 1;
	pthread_mutex_unlock(&info->m_die);
	return (0);
}

void	*ph_display_die(t_info *info, t_philo *philo)
{
	long long	time;

	time = (ph_time() - info->start) / 1000;
	pthread_mutex_lock(&info->m_display);
	info->die_flag = 1;
	pthread_mutex_unlock(&info->m_die);
	printf("%lld %d \033[0;31mdied\n", time, philo->idx + 1);
	pthread_mutex_unlock(&info->m_display);
	return (0);
}

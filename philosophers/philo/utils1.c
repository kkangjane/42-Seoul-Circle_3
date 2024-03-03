/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:53:13 by kangjaehyun       #+#    #+#             */
/*   Updated: 2024/03/01 13:27:37 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ph_time(void)
{
	long long		time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000000 + t.tv_usec;
	return (time);
}

int	ph_check_die(t_info *info)
{
	pthread_mutex_lock(&info->m_die);
	if (info->die_flag)
	{
		pthread_mutex_unlock(&info->m_die);
		return (1);
	}
	pthread_mutex_unlock(&info->m_die);
	return (0);
}

int	ph_check_finish(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < info->num_of_philo)
	{
		philo = &info->philos[i];
		pthread_mutex_lock(&philo->m_cnt);
		if (philo->eat_cnt < philo->info->must_eat)
		{
			pthread_mutex_unlock(&philo->m_cnt);
			return (0);
		}
		pthread_mutex_unlock(&philo->m_cnt);
	}
	return (1);
}

int	ph_sleep(long long time, int usleep_size, t_info *info)
{
	long long	start;

	start = ph_time();
	while (start + time >= ph_time())
	{
		if (ph_check_die(info))
			return (-1);
		usleep(usleep_size);
	}
	return (0);
}

int	ph_finish(t_info *info, t_philo *philo, int ret)
{
	int	i;

	free_except_philo(info);
	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&philo[i].m_cnt);
	free(philo);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:25:00 by kangjaehyun       #+#    #+#             */
/*   Updated: 2024/02/19 14:41:33 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *arg)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *) arg;
	info = philo->info;
	pthread_mutex_lock(&info->m_die);
	philo->last_eat = ph_time();
	pthread_mutex_unlock(&info->m_die);
	if (philo->idx % 2 == 0 && info->num_of_philo > 1)
		ph_sleep(0.8 * info->time_to_eat, 100, info);
	while (1)
	{
		if (grep_fork(info, philo))
			break ;
		if (eating(info, philo))
			break ;
		down_fork(info, philo);
		if (sleeping(info, philo))
			break ;
		if (ph_display(info, philo, THINK) == -1)
			break ;
	}
	return (0);
}

void	*die_monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *) arg;
	while (ph_check_die(info) == 0)
	{
		i = -1;
		while (++i < info->num_of_philo)
		{
			pthread_mutex_lock(&info->m_die);
			if (info->philos[i].last_eat + info->time_to_die < ph_time())
				return (ph_display_die(info, &info->philos[i]));
			pthread_mutex_unlock(&info->m_die);
		}
	}
	return (0);
}

void	*cnt_monitor(void *arg)
{
	int		i;
	t_info	*info;

	info = (t_info *) arg;
	if (info->must_eat < 1)
		return (0);
	while (1)
	{
		i = -1;
		while (++i < info->num_of_philo)
		{
			if (ph_check_die(info))
				return (0);
			if (ph_check_finish(info))
				return (ph_everyone_finish(info));
		}
	}
}

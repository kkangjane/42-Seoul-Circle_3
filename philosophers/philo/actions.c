/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:27:56 by jae-kang          #+#    #+#             */
/*   Updated: 2024/02/26 12:19:30 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grep_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(info->m_forks[philo->left_fork]);
	if (info->fork_status[philo->left_fork])
		return (ph_display(info, philo, M_ERR));
	info->fork_status[philo->left_fork] = 1;
	if (ph_display(info, philo, FORK) == -1)
		return (1);
	pthread_mutex_lock(info->m_forks[philo->right_fork]);
	if (info->fork_status[philo->right_fork])
	{
		info->fork_status[philo->left_fork] = 0;
		pthread_mutex_unlock(info->m_forks[philo->left_fork]);
		return (ph_display(info, philo, M_ERR));
	}
	info->fork_status[philo->right_fork] = 1;
	if (ph_display(info, philo, FORK) == -1)
		return (1);
	return (0);
}

int	eating(t_info *info, t_philo *philo)
{
	if (ph_check_die(info))
		return (down_fork(info, philo));
	if (ph_display(info, philo, EAT) == -1)
		return (down_fork(info, philo));
	pthread_mutex_lock(&info->m_die);
	philo->last_eat = ph_time();
	pthread_mutex_unlock(&info->m_die);
	if (ph_sleep(info->time_to_eat, 100, info) == -1)
		return (down_fork(info, philo));
	if (info->must_eat > 0)
	{
		pthread_mutex_lock(&philo->m_cnt);
		philo->eat_cnt += 1;
		pthread_mutex_unlock(&philo->m_cnt);
	}
	return (0);
}

int	down_fork(t_info *info, t_philo *philo)
{
	info->fork_status[philo->right_fork] = 0;
	pthread_mutex_unlock(info->m_forks[philo->right_fork]);
	info->fork_status[philo->left_fork] = 0;
	pthread_mutex_unlock(info->m_forks[philo->left_fork]);
	return (1);
}

int	sleeping(t_info *info, t_philo *philo)
{
	if (ph_display(info, philo, SLEEP) == -1)
		return (1);
	if (ph_sleep(info->time_to_sleep, 100, info) == -1)
		return (1);
	return (0);
}

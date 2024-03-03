/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:47:50 by kangjaehyun       #+#    #+#             */
/*   Updated: 2024/02/26 14:21:04 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_init2(t_info *info);
static int	ph_init3(t_info *info, t_philo *philo);

int	ph_parsing(int argc, char *argv[], t_info *info)
{
	info->num_of_philo = ft_atoi(argv[1]);
	if (info->num_of_philo < 1)
		return (1);
	info->time_to_die = ft_atoi(argv[2]) * 1000;
	if (info->time_to_die < 0)
		return (1);
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	if (info->time_to_eat < 1)
		return (1);
	info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (info->time_to_sleep < 1)
		return (1);
	info->must_eat = -1;
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat < 0)
			return (1);
	}
	info->die_flag = 0;
	return (0);
}

int	ph_init(t_info *info)
{
	unsigned long	mpsize;

	if (pthread_mutex_init(&info->m_display, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->m_die, NULL) != 0)
	{
		pthread_mutex_destroy(&info->m_display);
		return (1);
	}
	mpsize = sizeof(pthread_mutex_t *);
	info->m_forks = (pthread_mutex_t **) malloc(mpsize * info->num_of_philo);
	if (info->m_forks == 0)
	{
		pthread_mutex_destroy(&info->m_die);
		pthread_mutex_destroy(&info->m_display);
		return (1);
	}
	if (ph_init2(info))
		return (1);
	info->philos = (t_philo *) malloc(sizeof(t_philo) * info->num_of_philo);
	if (info->philos == 0)
		return (free_except_philo(info));
	return (ph_init3(info, info->philos));
}

static int	ph_init2(t_info *info)
{
	unsigned long	msize;
	int				i;

	i = -1;
	msize = sizeof(pthread_mutex_t);
	while (++i < info->num_of_philo)
	{
		info->m_forks[i] = (pthread_mutex_t *) malloc(msize);
		if (pthread_mutex_init(info->m_forks[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(info->m_forks[i]);
				free(info->m_forks[i]);
			}
			free(info->m_forks);
			pthread_mutex_destroy(&info->m_die);
			pthread_mutex_destroy(&info->m_display);
			return (1);
		}
	}
	return (0);
}

static int	ph_init3(t_info *info, t_philo *philo)
{
	int	i;

	i = sizeof(info->num_of_philo);
	info->fork_status = (int *) malloc(i * sizeof(int));
	if (!info->fork_status)
		return (free_except_philo(info));
	i = -1;
	while (++i < info->num_of_philo)
	{
		info->fork_status[i] = 0;
		philo[i].idx = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % info->num_of_philo;
		philo[i].eat_cnt = 0;
		philo[i].finish_flag = 0;
		philo[i].info = info;
		if (pthread_mutex_init(&philo[i].m_cnt, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philo[i].m_cnt);
			return (free_except_philo(info));
		}
	}
	return (0);
}

int	free_except_philo(t_info *info)
{
	int	i;

	pthread_mutex_destroy(&info->m_die);
	pthread_mutex_destroy(&info->m_display);
	i = -1;
	while (++i < info->num_of_philo)
	{
		pthread_mutex_unlock(info->m_forks[i]);
		pthread_mutex_destroy(info->m_forks[i]);
		free(info->m_forks[i]);
	}
	free(info->m_forks);
	if (info->fork_status)
		free(info->fork_status);
	return (1);
}

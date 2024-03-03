/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:45:21 by jae-kang          #+#    #+#             */
/*   Updated: 2024/02/26 12:32:16 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_special_case(t_info *info);
static void	update_time(t_info *info);
static int	finish_thread(t_info *info);

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
		return (ph_print_err("the number of args is wrong", 1));
	if (ph_parsing(argc, argv, &info))
		return (ph_print_err("arguments are wrong", 1));
	if (ph_special_case(&info) > 0)
		return (0);
	if (ph_init(&info))
		return (1);
	update_time(&info);
	if (ph_start(&info, info.philos))
	{
		printf("error while making & using threads\n");
		return (ph_finish(&info, info.philos, 1));
	}
	return (ph_finish(&info, info.philos, 0));
}

int	ph_start(t_info *info, t_philo *philo)
{
	int	i;

	if (pthread_create(&info->die_tid, NULL, &die_monitor, info) != 0)
		return (1);
	if (pthread_create(&info->cnt_tid, NULL, &cnt_monitor, info) != 0)
	{
		pthread_detach(info->die_tid);
		return (1);
	}
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, &func_philo, &philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(philo[i].tid);
			pthread_detach(info->die_tid);
			pthread_detach(info->cnt_tid);
			return (1);
		}
	}
	return (finish_thread(info));
}

static int	finish_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		if (pthread_join(info->philos[i++].tid, NULL) != 0)
			printf("thread %d join error\n", (int)(info->philos[i - 1].tid));
	if (pthread_join(info->die_tid, NULL) != 0)
		printf("thread %d join error\n", (int)(info->die_tid));
	if (pthread_join(info->cnt_tid, NULL) != 0)
		printf("thread %d join error\n", (int)(info->cnt_tid));
	return (0);
}

static int	ph_special_case(t_info *info)
{
	long long	start;

	if (info->must_eat == 0)
		return (printf("\033[0;36meveyone is full\n"));
	if (info->time_to_die == 0)
		return (printf("1 \033[0;31mdied\n"));
	if (info->num_of_philo == 1)
	{
		start = ph_time();
		printf("0 1 has taken a fork\n");
		while (start + info->time_to_die >= ph_time())
			usleep(100);
		return (printf("%lld 1 \033[0;31mdied\n", info->time_to_die / 1000));
	}
	return (0);
}

static void	update_time(t_info *info)
{
	int	i;

	info->start = ph_time();
	i = 0;
	while (i < info->num_of_philo)
		info->philos[i++].last_eat = ph_time();
}

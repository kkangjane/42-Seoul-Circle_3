/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:45:35 by jae-kang          #+#    #+#             */
/*   Updated: 2024/02/26 14:21:13 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define DIE	1
# define FORK	2
# define EAT	3
# define SLEEP	4
# define THINK	5
# define M_ERR	6

struct	s_info;
struct	s_philo;

typedef struct s_philo
{
	struct s_info	*info;
	pthread_t		tid;
	pthread_mutex_t	m_cnt;

	int				idx;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	int				finish_flag;
	long long		last_eat;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	long long		start;
	int				die_flag;
	int				*fork_status;

	pthread_mutex_t	**m_forks;
	pthread_mutex_t	m_display;
	pthread_mutex_t	m_die;
	pthread_t		die_tid;
	pthread_t		cnt_tid;

	t_philo			*philos;
}	t_info;

/* thread.c */
int			ph_start(t_info *info, t_philo *philo);
void		*func_philo(void *arg);
void		*die_monitor(void *arg);
void		*cnt_monitor(void *arg);

/* actions.c */
int			grep_fork(t_info *info, t_philo *philo);
int			eating(t_info *info, t_philo *philo);
int			down_fork(t_info *info, t_philo *philo);
int			sleeping(t_info *info, t_philo *philo);

/* utils.c */
int			ph_sleep(long long time, int sleep_size, t_info *info);
int			ph_check_finish(t_info *info);
int			ph_check_die(t_info *info);
int			ph_finish(t_info *info, t_philo *philo, int ret);
long long	ph_time(void);

/* utils2.c */
int			ph_print_err(char *msg, int ret);
int			ft_atoi(const char *s);
int			ph_display(t_info *info, t_philo *philo, int flag);
void		*ph_display_die(t_info *info, t_philo *philo);
void		*ph_everyone_finish(t_info *info);

/* init.c */
int			ph_parsing(int argc, char *argv[], t_info *info);
int			ph_init(t_info *info);
int			free_except_philo(t_info *info);

#endif
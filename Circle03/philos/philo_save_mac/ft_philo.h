/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 15:40:29 by junghan           #+#    #+#             */
/*   Updated: 2021/07/08 16:52:14 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos {
	pthread_t		philo;
	unsigned long	starving_time;
	int				eat_time;
	int				die;
	int				full;
	int				left_hand;
	int				right_hand;
	int				id;
}				t_philos;

typedef struct s_info {
	int				num_of_philos;
	int				num_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	int				limit;
	int				die_flag;
	int				check_odd;
	int				check_even;
	unsigned long	std_time;
}				t_info;

t_info		g_info;

int				ft_atoi(char *str);
int				set_malloc(t_philos **philos, int ret, int *num);
int				kill_philos(int num, t_philos *philos);
int				have_dining(t_philos *philos);
int				check_valid(char **av, int limit);
void			init_philo(t_philos *philos, int i);

int				eat_to_survive(t_philos *philos);
int				sleep_after_eat(t_philos *philos, int check);
int				think_before_eat(t_philos *philos, int check);

unsigned long	prst_mili_sec(void);
void			for_pause(int time);

int				pick_up_fork(t_philos *philo);
int				set_free_hand(t_philos *philo);
int				two_hand_operation(t_philos *philo, unsigned long present);
void			one_hand_operation(t_philos *philo, int check, \
				unsigned long present);
#endif

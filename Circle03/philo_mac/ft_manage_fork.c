/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:41:48 by junghan           #+#    #+#             */
/*   Updated: 2021/07/08 16:50:29 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	scheduling(t_philos *philo, int *left, int *right)
{
	while (philo->id % 2 == 0 && g_info.check_odd > 0)
		usleep(50);
	if (philo->id % 2 == 1 && g_info.check_odd > 0)
		g_info.check_odd--;
	if (philo->id % 2 == 1)
	{
		*left = pthread_mutex_lock(&g_info.forks[(philo->id - 1)]);
		printf("[%lu]	|	philo[%d]	|	picked up left		|\n", \
				(prst_mili_sec() - g_info.std_time), philo->id);
		*right = pthread_mutex_lock(&g_info.forks[(philo->id \
					% g_info.num_of_forks)]);
		printf("[%lu]	|	philo[%d]	|	picked up right		|\n", \
				(prst_mili_sec() - g_info.std_time), philo->id);
	}
	else if (philo->id % 2 == 0)
	{
		*right = pthread_mutex_lock(&g_info.forks[(philo->id \
					% g_info.num_of_forks)]);
		printf("[%lu]	|	philo[%d]	|	picked up right		|\n", \
				(prst_mili_sec() - g_info.std_time), philo->id);
		*left = pthread_mutex_lock(&g_info.forks[(philo->id - 1)]);
		printf("[%lu]	|	philo[%d]	|	picked up left		|\n", \
				(prst_mili_sec() - g_info.std_time), philo->id);
	}
	return ;
}

int	pick_up_fork(t_philos *philo)
{
	int	left;
	int	right;

	scheduling(philo, &left, &right);
	if (left == 0)
		philo->left_hand = 1;
	if (right == 0)
		philo->right_hand = 1;
	if (philo->left_hand == 1 && philo->right_hand == 1)
	{
		philo->eat_time++;
		return (0);
	}
	else if (philo->left_hand == 1)
		return (1);
	else if (philo->right_hand == 1)
		return (2);
	return (3);
}

void	one_hand_operation(t_philos *philo, int check, unsigned long present)
{
	if (check == 1)
	{
		pthread_mutex_unlock(&g_info.forks[philo->id - 1]);
		philo->left_hand = 0;
		printf("[%lu]	|	philo[%d]	|	picked down left	|\n", \
				(present - g_info.std_time), philo->id);
	}
	else if (check == 2)
	{
		pthread_mutex_unlock(&g_info.forks[philo->id % g_info.num_of_forks]);
		philo->right_hand = 0;
		printf("[%lu]	|	philo[%d]	|	picked down right	|\n", \
				(present - g_info.std_time), philo->id);
	}
}

int	set_free_hand(t_philos *philo)
{
	unsigned long	present;

	present = prst_mili_sec();
	if ((present - philo->starving_time) > g_info.time_to_die)
	{
		philo->die = 1;
		pthread_mutex_unlock(&g_info.forks[philo->id - 1]);
		pthread_mutex_unlock(&g_info.forks[philo->id % \
				g_info.num_of_forks]);
		return (-1);
	}
	philo->starving_time = present;
	printf("[%lu]	|	philo[%d]	|	picked down left	|\n", \
			(present - g_info.std_time), philo->id);
	printf("[%lu]	|	philo[%d]	|	picked down right	|\n", \
			(present - g_info.std_time), philo->id);
	philo->left_hand = 0;
	philo->right_hand = 0;
	pthread_mutex_unlock(&g_info.forks[philo->id - 1]);
	pthread_mutex_unlock(&g_info.forks[philo->id % g_info.num_of_forks]);
	return (0);
}

int	two_hand_operation(t_philos *philo, unsigned long present)
{
	int	ret;

	ret = 3;
	printf("[%lu]	|	philo[%d]	|	eating...[%d]		|\n", \
			(present - g_info.std_time), philo->id, philo->eat_time);
	if (g_info.die_flag == 0 || (present - philo->starving_time) \
			> g_info.time_to_die)
	{
		philo->die = 1;
		pthread_mutex_unlock(&g_info.forks[philo->id - 1]);
		pthread_mutex_unlock(&g_info.forks[philo->id % \
				g_info.num_of_forks]);
		return (-1);
	}
	for_pause(g_info.time_to_eat);
	ret = set_free_hand(philo);
	if (ret == -1)
	{
		philo->die = 1;
		return (-1);
	}
	return (0);
}

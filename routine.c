/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarylak <mbarylak@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:23:51 by mbarylak          #+#    #+#             */
/*   Updated: 2022/08/11 19:34:07 by mbarylak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *p)
{
	t_input	*in;

	in = p->in;
	pthread_mutex_lock(&(in->forks[p->left_fork]));
	print_action(in, p->id, "has taken left fork");
	pthread_mutex_lock(&(in->forks[p->right_fork]));
	print_action(in, p->id, "has taken right fork");
	pthread_mutex_lock(&(in->eating));
	print_action(in, p->id, "is eating");
	p->last_meal = get_time();
	p->ate += 1;
	pthread_mutex_unlock(&(in->eating));
	pause_time(in->e_time, in);
	pthread_mutex_unlock(&(in->forks[p->left_fork]));
	pthread_mutex_unlock(&(in->forks[p->right_fork]));
}

void	*routine(void *p)
{
	t_philo	*philo;
	t_input	*in;

	philo = (t_philo *)p;
	in = philo->in;
	if (philo->id % 2 != 0)
		usleep(1500);
	while (!in->death)
	{
		philo_eat(philo);
		if (in->all_ate)
			break ;
		print_action(in, philo->id, "is sleeping");
		pause_time(in->s_time, in);
		print_action(in, philo->id, "is thinking");
	}
	return (NULL);
}

void	*lone_r(void *p)
{
	t_philo	*philo;
	t_input	*in;

	philo = (t_philo *) p;
	in = philo->in;
	print_action(in, philo->id, "has taken left fork");
	pause_time(in->d_time, in);
	print_action(in, philo->id, "died");
	in->death = 1;
	return (NULL);
}

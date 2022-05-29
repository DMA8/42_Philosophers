/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:48:02 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 01:39:18 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>

static void	take_fork(t_philo *philo)
{
	sem_wait(philo->overall_data->sem_forks);
	msg(philo->overall_data, philo->philo_number, "has taken the left fork");
	sem_wait(philo->overall_data->sem_forks);
	msg(philo->overall_data, philo->philo_number, "has taken the right fork");
	msg(philo->overall_data, philo->philo_number, "is eating");
	sem_wait(philo->sem_eat);
	sem_post(philo->overall_data->sem_meal);
	philo->last_supper = get_time();
	my_usleep(philo->overall_data->time_to_eat);
	sem_post(philo->sem_eat);
}

static void	*routine(t_philo *ph)
{
	while (1)
	{
		take_fork(ph);
		sem_post(ph->overall_data->sem_forks);
		sem_post(ph->overall_data->sem_forks);
		msg(ph->overall_data, ph->philo_number, "is sleeping");
		my_usleep(ph->overall_data->time_to_sleep);
		msg(ph->overall_data, ph->philo_number, "is thinking");
		usleep(100);
	}
	return (NULL);
}

static void	*monitor_death(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->sem_eat);
		if (get_time() - ph->last_supper >= ph->overall_data->time_to_die)
		{
			msg(ph->overall_data, ph->philo_number, "is dying");
			exit(1);
		}
		sem_post(ph->sem_eat);
		usleep(100);
	}
	return (NULL);
}

static void		*monitor_meal(void *inp)
{
	t_overall	*all;
	int			eat_c;
	int			i;
	
	all = (t_overall *)inp;
	eat_c = 0;
	while (eat_c < all->n_suppers)
	{
		i = 0;
		while (i <= all->n_philos)
		{
			sem_wait(all->sem_meal);
			i++;
		}
		eat_c++;
	}
	sem_wait(all->sem_voice);
	i = 0;
	while (i < all->n_philos)
		kill(all->philo[i++]->pid_philo, SIGKILL);
	return (NULL);
}

void		start_philo(t_overall *all)
{
	int	i;

	i = 0;
	if (all->n_suppers)
		pthread_create(&all->monitor_meal, NULL, monitor_meal, all);
	while (i < all->n_philos)
	{
		all->philo[i]->pid_philo = fork();
		all->philo[i]->last_supper = get_time();
		if (all->philo[i]->pid_philo == 0)
		{
			pthread_create(&all->philo[i]->death_monitor, NULL, monitor_death,
							all->philo[i]);
			routine(all->philo[i]);
			exit(1);
		}
		i++;
		usleep(100);
	}
	kill_processes(all);
}

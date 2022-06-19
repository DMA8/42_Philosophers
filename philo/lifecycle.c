/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:52:02 by syolando          #+#    #+#             */
/*   Updated: 2022/06/18 22:43:10 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

// check_death is only thing main routine does when all philo is started.
// set gameover if somebody is down
static void check_death(t_overall *data)
{
	int i;
	time_t time;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->voice);
		time = get_time();
		while (i < data->n_philos)
		{
			if (time - data->philo[i].last_supper >= data->time_to_die)
			{
				print_action(&data->philo[i], "died");
				data->game_over = 1;
				break;
			}
			i++;
		}
		if (data->game_over == 1)
		{
			pthread_mutex_unlock(&data->voice);
			return;
		}
		pthread_mutex_unlock(&data->voice);
	}
}

// check_done_eating iterates through all phulos and check if they ate enough
static int check_done_eating(t_overall *data)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->philo[i].num_supper < data->n_suppers_goal)
			return (0);
		i++;
	}
	data->game_over = 1;
	return (1);
}

// act prints time and routine type. Returns if gameover is set.
static int act(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->overall_data->voice);
	if (philo->overall_data->game_over)
	{
		pthread_mutex_unlock(&philo->overall_data->voice);
		return (1);
	}
	if (action == EAT)
	{
		print_action(philo, "is eating");
		philo->last_supper = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(philo, "is sleeping");
		philo->num_supper++;
		if (philo->num_supper == philo->overall_data->n_suppers_goal)
			check_done_eating(philo->overall_data);
	}
	else if (action == THINK)
		print_action(philo, "is thinking");
	pthread_mutex_unlock(&philo->overall_data->voice);
	return (0);
}

// routine is the lifecycle of philosophers
static void *routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->number % 2 == 0)												  // we force everysecond philo to sleep. In order others take both forks
		my_sleep(philo->overall_data->time_to_eat / 2L, philo->overall_data); // sleep the half of time_to_eat 2L - long type
	while (!philo->game_over)
	{
		pthread_mutex_lock(philo->left_fork); // TAKE LEFT FORK
		philo->game_over = act(philo, TAKE_FORK);
		if (philo->left_fork == philo->right_fork) // ???? If THEREIS ONLY ONE PHILO?
			break;
		pthread_mutex_lock(philo->right_fork);							   // TAKE RIGHT FORK
		philo->game_over = act(philo, TAKE_FORK);						   // PRINT TAKEFORK
		philo->game_over = act(philo, EAT);								   // EATING
		my_sleep(philo->overall_data->time_to_eat, philo->overall_data);   // EATING
		philo->game_over = act(philo, SLEEP);							   // PRINT SLEEPING
		pthread_mutex_unlock(philo->left_fork);							   // RELEASE LEFT FORK
		pthread_mutex_unlock(philo->right_fork);						   // RELEASE RIGHT FORK
		my_sleep(philo->overall_data->time_to_sleep, philo->overall_data); // HERE WE GO TO SLEEP
		philo->game_over = act(philo, THINK);							   // PRINT THINKING
	}
	if (philo->left_fork == philo->right_fork) // HOW ARE INITED FORKS?
		pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

// launch_philos starts philos in routines and watch if smbd down
int launch_philos(t_overall *all)
{
	int i;

	i = 0;
	all->start_time = get_time(); // starttime
	while (i < all->n_philos)	  // launch all philos
	{
		all->philo[i].last_supper = all->start_time;	// set start time as last_supper
		if (pthread_create(&all->philo[i].thread, NULL, // creating thread. Launch routine with passing ptr to philo from mainStruct
						   &routine, &all->philo[i]))
		{
			write(2, "error while pthread_create\n", 26); // cleaning up everything if fail pthreadCreate
			pthread_mutex_lock(&all->voice);
			all->game_over = 1; // setGameover
			pthread_mutex_unlock(&all->voice);
			return (0);
		}
		i++;
	}
	check_death(all); // checking death. So that's what main routine doing
	return (1);
}

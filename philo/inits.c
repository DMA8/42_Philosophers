/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:59:56 by syolando          #+#    #+#             */
/*   Updated: 2022/06/18 22:43:10 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static void init_overall_numbers(t_overall *all, char **argv)
{
	all->n_philos = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->n_suppers_goal = ft_atoi(argv[5]);
	else
		all->n_suppers_goal = 0;
}

static void free_bad_mutex_init(t_overall *all, int created_mutexes)
{
	int i;

	i = 0;
	while (i < created_mutexes)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	free(all->philo);
	free(all->forks);
}

static int init_mutexes(t_overall *all)
{
	int i;

	i = 0;
	while (i < all->n_philos)
	{
		if (pthread_mutex_init(&all->forks[i], NULL)) // initing mutexes
		{
			free_bad_mutex_init(all, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void init_philos(t_overall *all)
{
	int i;

	i = 0;
	memset(all->philo, 0, sizeof(t_philo) * all->n_philos); // set all fields in t_philo in 0
	while (i < all->n_philos)
	{
		all->philo[i].overall_data = all;		  // insert link to each routine to general struct
		all->philo[i].number = i + 1;			  // set number starting from 0
		all->philo[i].left_fork = &all->forks[i]; // left fork belongs to THE PHILO
		if (i == all->n_philos - 1)				  // if philo is last then right fork is fork of the first philo
			all->philo[i].right_fork = &all->forks[0];
		else
			all->philo[i].right_fork = &all->forks[i + 1];
		i++;
	}
}

int init_overall(t_overall *all, char **argv)
{
	memset(all, 0, sizeof(t_overall)); // set everything in 0
	init_overall_numbers(all, argv);
	all->philo = malloc(sizeof(t_philo) * all->n_philos); // set array on heap nPhilos
	if (!all->philo)
		return (0);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->n_philos); // set array in heap mutexes (forks)
	if (!all->forks)
	{
		free(all->philo);
		return (0);
	}
	if (!init_mutexes(all))
		return (0);
	init_philos(all);
	return (1);
}

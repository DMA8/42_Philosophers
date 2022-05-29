/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:07:34 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 01:45:06 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

static t_philo	**philo_init(t_overall *all)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * all->n_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < all->n_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->philo_number = i;
		philo[i]->overall_data = all;
		sem_unlink("eatcounter");
		philo[i]->sem_eat = sem_open("eatcounter", O_CREAT, 0644, 1);
		if (!philo[i]->sem_eat)
			return (NULL);
		i++;
	}
	return (philo);
}

static int	sems_init(t_overall *all)
{
	sem_unlink("forking");
	all->sem_forks = sem_open("forking", O_CREAT, 0644, all->n_philos);
	if (!all->sem_forks)
		return (0);
	sem_unlink("writing");
	all->sem_voice = sem_open("writing", O_CREAT, 0644, all->n_philos);
	if (!all->sem_voice)
		return (0);
	all->sem_meal = sem_open("meal", O_CREAT, 0644, all->n_philos);
	if (!all->sem_voice)
		return (0);
	return (1);
}

t_overall	*init_overall(char **argv, int argc)
{
	t_overall *all;
	
	all = malloc(sizeof(t_overall));
	if (!all)
		return (0);
	memset(all, 0, sizeof(t_overall));
	all->n_philos = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->n_suppers = ft_atoi(argv[5]);
	if (!sems_init(all))
		return (NULL);
	all->start_time = get_time();
	all->philo = philo_init(all);
	if (!all->philo)
		return (NULL);
	return (all);
}

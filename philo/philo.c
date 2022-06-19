/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:39:43 by syolando          #+#    #+#             */
/*   Updated: 2022/06/19 21:13:05 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static void	free_all(t_overall *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			write(2, "fail\n", 6);
		i++;
	}
	free(data->philo);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			write(2, "fail\n", 6);
		i++;
	}
	free(data->forks);
	if (pthread_mutex_destroy(&data->voice))
		write(2, "fail\n", 6);
}

int	main(int argc, char **argv)
{
	t_overall	all;
	
	if (!validate_inputs(argc, argv))
	{
		write(2, "bad input\n", 10);
		return (1);
	}
	if (!init_overall(&all, argv))
	{
		write(2, "init failure\n", 13);
		return (1);
	}
	if (!launch_philos(&all))
	{
		write(2, "couldn't start threads\n", 23);
		return (1);
	}
	free_all(&all);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:32:46 by syolando          #+#    #+#             */
/*   Updated: 2022/06/19 21:02:58 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void init_philo(t_overall *data)
{
	char *name;

	name = gen_sem_name(data->philo.number);
	data->philo.last_supper = data->start_time;
	data->philo.rights = sem_open(name, O_CREAT | O_EXCL, 0644, data->n_philos);
	if (data->philo.rights == SEM_FAILED)
		write(2, "test\n", 5);
	sem_unlink(name);
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	free(name);
	if (pthread_create(&data->philo.monitor, NULL, &death_checker, data))
	{
		print_error("pthread: ", NULL, NULL, errno);
		sem_post(data->stop);
	}
	pthread_detach(data->philo.monitor);
}

static int init_sempahore(t_overall *data)
{
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->n_philos);
	data->speak = sem_open("speak", O_CREAT | O_EXCL, 0644, 1);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	if (data->n_suppers_goal)
		data->repletion = sem_open("repletion", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED || data->speak == SEM_FAILED || data->stop == SEM_FAILED || (data->n_suppers_goal && data->repletion == SEM_FAILED))
	{
		print_error("sem_open: ", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int init_thread(t_overall *data)
{
	if (data->n_suppers_goal)
	{
		if (pthread_create(&data->monitor, NULL, &repletion_checker, data))
		{
			print_error("pthread: ", NULL, NULL, errno);
			return (EXIT_FAILURE);
		}
		pthread_detach(data->monitor);
	}
	return (EXIT_SUCCESS);
}

int init_data(t_overall *data, char **argv)
{
	memset(data, 0, sizeof(t_overall));
	ft_atoi_is_overflow(argv[1], (int *)&data->n_philos);
	ft_atoi_is_overflow(argv[2], (int *)&data->time_to_die);
	ft_atoi_is_overflow(argv[3], (int *)&data->time_to_eat);
	ft_atoi_is_overflow(argv[4], (int *)&data->time_to_sleep);
	if (argv[5])
		ft_atoi_is_overflow(argv[5], (int *)&data->n_suppers_goal);
	data->pid_philo = malloc(sizeof(pid_t) * data->n_philos);
	if (!data->pid_philo)
	{
		print_error("malloc: ", NULL, NULL, ENOMEM);
		return (EXIT_FAILURE);
	}
	memset(data->pid_philo, 0, sizeof(pid_t) * data->n_philos);
	if (init_sempahore(data) == EXIT_FAILURE || init_thread(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

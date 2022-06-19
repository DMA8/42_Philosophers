/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:37:12 by syolando          #+#    #+#             */
/*   Updated: 2022/06/19 21:04:47 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *death_checker(void *arg)
{
	t_overall *all;

	all = arg;
	while (1)
	{
		sem_wait(all->philo.rights);
		if (get_time() - all->philo.last_supper >= all->time_to_die)
		{
			sem_wait(all->speak);
			print_action(all, &all->philo, "died");
			sem_post(all->stop);
			exit(0);
		}
		sem_post(all->philo.rights);
	}
	return (NULL);
}

void *repletion_checker(void *arg)
{
	t_overall *data;
	size_t i;

	data = arg;
	i = 0;
	sem_wait(data->speak);
	while (i < data->n_philos)
	{
		sem_post(data->speak);
		sem_wait(data->repletion);
		sem_wait(data->speak);
		i++;
	}
	sem_post(data->stop);
	return (NULL);
}

void act(t_overall *data, int action)
{
	sem_wait(data->speak);
	sem_wait(data->philo.rights);
	if (action == EAT)
	{
		print_action(data, &data->philo, "is eating");
		data->philo.last_supper = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(data, &data->philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(data, &data->philo, "is sleeping");
		data->philo.num_supper++;
		if (data->philo.num_supper == data->n_suppers_goal)
			sem_post(data->repletion);
	}
	else if (action == THINK)
		print_action(data, &data->philo, "is thinking");
	sem_post(data->philo.rights);
	sem_post(data->speak);
}

static void *routine(t_overall *data)
{
	if (data->philo.number > data->n_philos / 2L)
		my_sleep(data->time_to_eat / 2L, data);
	while (1)
	{
		sem_wait(data->forks);
		act(data, TAKE_FORK);
		sem_wait(data->forks);
		act(data, TAKE_FORK);
		act(data, EAT);
		my_sleep(data->time_to_eat, data);
		act(data, SLEEP);
		sem_post(data->forks);
		sem_post(data->forks);
		my_sleep(data->time_to_sleep, data);
		act(data, THINK);
	}
	return (NULL);
}

int start_philosopher(t_overall *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	while (i < (int)data->n_philos)
	{
		data->philo.number = i + 1;	 // не нужно хранить все индексы. Так как этот индекс уйдет каждый раз уникальным в дочерние процессы (философы)
		data->pid_philo[i] = fork(); // создаем дочерний процесс. Если fork не удался - закрываемся
		if (data->pid_philo[i] == -1)
		{
			print_error("fork: ", NULL, NULL, errno);
			while (--i >= 0)
				kill(data->pid_philo[i], SIGKILL); //убиваем процессы
			return (EXIT_FAILURE);
		}
		else if (data->pid_philo[i] == 0) // если в дочернем в процессе
		{
			init_philo(data); //
			routine(data);
		}
		i++;
	}
	sem_wait(data->stop);
	return (EXIT_SUCCESS);
}

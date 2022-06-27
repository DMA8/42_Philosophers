/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:33:22 by syolando          #+#    #+#             */
/*   Updated: 2022/06/28 02:56:38 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;
	int		tmp;

	if (argc < 5 || argc > 6)
	{
		print_error("Usage: ", NULL, USAGE_MSG, -1);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]) || ft_atoi_is_overflow(argv[i], &tmp)
			|| tmp == 0)
		{
			print_error(NULL, argv[i], NULL, EINVAL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	kill_philosophers(t_overall *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
	}
}

static void	free_data(t_overall *data)
{
	free(data->pid_philo);
	if (sem_close(data->forks))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (sem_close(data->speak))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (sem_close(data->stop))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (data->n_suppers_goal && sem_close(data->repletion))
		print_error("sem_close: ", NULL, NULL, EINVAL);
}

int	main(int argc, char **argv)
{
	t_overall	data;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	if (start_philosopher(&data) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	kill_philosophers(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}

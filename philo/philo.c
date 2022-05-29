/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:39:43 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 00:39:28 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

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
		// добавить отчистку all
		write(2, "couldn't start threads\n", 23);
		return (1);
	}
}
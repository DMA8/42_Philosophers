/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:39:43 by syolando          #+#    #+#             */
/*   Updated: 2022/05/15 23:05:21 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
// nforkr = nPhilo

void	*routine()
{
	sleep(10);
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
}